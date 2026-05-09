// SerialCom.cpp
#if PROJECT_USE_CSerialPort
#include "SerialCom.h"
#include <iostream>
#include <cstring>

SerialCom::SerialCom() : m_running(false) {
    // 设置为异步操作模式（默认）
    //m_serialPort.setOperateMode(itas109::AsynchronousOperate);
    m_serialPort.setOperateMode(itas109::SynchronousOperate);
}

SerialCom::~SerialCom() {
    close();
}

bool SerialCom::open(const std::string& portName, int baudrate) {
    if (isOpen()) {
        close();
    }

    // 转换波特率
    itas109::BaudRate br;
    switch (baudrate) {
        case 9600:   br = itas109::BaudRate9600; break;
        case 19200:  br = itas109::BaudRate19200; break;
        case 38400:  br = itas109::BaudRate38400; break;
        case 57600:  br = itas109::BaudRate57600; break;
        case 115200: br = itas109::BaudRate115200; break;
        default:     br = itas109::BaudRate115200; break;
    }

    // 初始化串口参数
    m_serialPort.init(
        portName.c_str(),
        br,                      // 波特率
        itas109::ParityNone,     // 无校验
        itas109::DataBits8,      // 8数据位
        itas109::StopOne,        // 1停止位
        itas109::FlowNone,       // 无流控
        4096                     // 接收缓冲区大小
    );

    // 打开串口
    m_serialPort.open();

    if (!m_serialPort.isOpen()) {
        if (m_errorCallback) {
            m_errorCallback("Failed to open serial port: " + portName);
        }
        return false;
    }

    // 设置读取间隔超时（0表示立即返回）
    m_serialPort.setReadIntervalTimeout(0);
    // 设置缓冲区满通知阈值（80%）
    m_serialPort.setByteReadBufferFullNotify(3276);

    // 启动读取线程
    m_running = true;
    m_readThread = std::thread(&SerialCom::readThreadFunc, this);

    if (m_errorCallback) {
        m_errorCallback("Serial port opened: " + portName + " at " + std::to_string(baudrate) + " baud");
    }

    return true;
}

void SerialCom::close() {
    m_running = false;
    if (m_readThread.joinable()) {
        m_readThread.join();
    }

    if (m_serialPort.isOpen()) {
        m_serialPort.close();
    }
}

bool SerialCom::isOpen()  {
    return m_serialPort.isOpen();
}

bool SerialCom::sendData(const std::vector<uint8_t>& data) {
    return sendData(data.data(), data.size());
}

bool SerialCom::sendData(const std::string& data) {
    return sendData(reinterpret_cast<const uint8_t*>(data.c_str()), data.length());
}

bool SerialCom::sendData(const uint8_t* data, size_t len) {
    if (!isOpen()) {
        return false;
    }

    int written = m_serialPort.writeData(const_cast<char*>(reinterpret_cast<const char*>(data)), len);
    return written == static_cast<int>(len);
}

bool SerialCom::sendByte(uint8_t byte) {
    return sendData(&byte, 1);
}

void SerialCom::setReceiveCallback(std::function<void(const std::vector<uint8_t>&)> callback) {
    m_receiveCallback = callback;
}

void SerialCom::setErrorCallback(std::function<void(const std::string&)> callback) {
    m_errorCallback = callback;
}

int SerialCom::getAvailableDataLength() {
    if (!isOpen()) {
        return 0;
    }
    return m_serialPort.getReadBufferSize();
}

void SerialCom::readThreadFunc() {
    const int BUFFER_SIZE = 1024;
    char buffer[BUFFER_SIZE];

    while (m_running) {
        if (!isOpen()) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            continue;
        }

        // 检查是否有数据可读
        int available = getAvailableDataLength();
        if (available > 0) {
            int bytesRead = m_serialPort.readData(buffer, std::min(available, BUFFER_SIZE));
            std::cout << "bytesRead " << bytesRead << std::endl;
            if (bytesRead > 0 && m_receiveCallback) {
                std::vector<uint8_t> data(buffer, buffer + bytesRead);
                m_receiveCallback(data);
            } else if (bytesRead < 0 && m_errorCallback) {
                m_errorCallback("Read error: " + std::to_string(bytesRead));
            }
        }

        // 避免CPU空转
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}


// main.cpp
#include "SerialCom.h"
#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>

// 将字节数组转换为十六进制字符串
std::string bytesToHex(const std::vector<uint8_t>& data) {
    std::stringstream ss;
    ss << std::hex << std::setfill('0');
    for (uint8_t byte : data) {
        ss << "0x" << std::setw(2) << static_cast<int>(byte) << " ";
    }
    return ss.str();
}

// 发送HEX格式数据
void sendHexData(SerialCom& com, const std::string& hexStr) {
    std::vector<uint8_t> data;
    // 解析十六进制字符串（格式如 "01 02 03" 或 "0x01 0x02"）
    std::stringstream ss(hexStr);
    std::string token;
    while (ss >> token) {
        // 去除 "0x" 前缀
        if (token.substr(0, 2) == "0x" || token.substr(0, 2) == "0X") {
            token = token.substr(2);
        }
        uint8_t byte = static_cast<uint8_t>(std::stoi(token, nullptr, 16));
        data.push_back(byte);
    }
    com.sendData(data);
}

int TestSerialCom() {
    SerialCom com;

    // 设置接收回调
    com.setReceiveCallback([](const std::vector<uint8_t>& data) {
        std::cout << "Received " << data.size() << " bytes: ";

        // 尝试作为ASCII字符串输出
        bool isPrintable = true;
        for (uint8_t byte : data) {
            if (byte < 32 || byte > 126) {
                isPrintable = false;
                break;
            }
        }

        if (isPrintable && data.size() > 0) {
            // 可打印字符，作为字符串输出
            std::string str(data.begin(), data.end());
            std::cout << "\"" << str << "\"";
        } else {
            // 否则输出十六进制
            std::cout << bytesToHex(data);
        }
        std::cout << std::endl;
    });

    // 设置错误回调
    com.setErrorCallback([](const std::string& error) {
        std::cerr << "[ERROR] " << error << std::endl;
    });

    // 打开串口（根据实际情况修改端口名）
    // Windows: "COM3", Linux: "/dev/ttyUSB0"
    std::string portName;
    std::cout << "Enter serial port name (e.g., COM3 or /dev/ttyUSB0): ";
    std::getline(std::cin, portName);

    if (!com.open(portName, 9600)) {
        std::cerr << "Failed to open serial port!" << std::endl;
        return 1;
    }

    std::cout << "Serial port opened successfully!" << std::endl;
    std::cout << "Commands:" << std::endl;
    std::cout << "  send <text>      - Send text data" << std::endl;
    std::cout << "  hex <hex bytes>  - Send hex data (e.g., hex 01 02 03)" << std::endl;
    std::cout << "  exit             - Exit program" << std::endl;
    std::cout << std::endl;

    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line == "exit") {
            break;
        } else if (line.substr(0, 4) == "send") {
            std::string data = line.substr(5);
            if (!data.empty()) {
                if (com.sendData(data)) {
                    std::cout << "Sent: " << data << std::endl;
                } else {
                    std::cout << "Send failed!" << std::endl;
                }
            }
        } else if (line.substr(0, 3) == "hex") {
            std::string hexData = line.substr(4);
            if (!hexData.empty()) {
                sendHexData(com, hexData);
                std::cout << "Sent hex: " << hexData << std::endl;
            }
        } else if (!line.empty()) {
            std::cout << "Unknown command. Use 'send', 'hex', or 'exit'" << std::endl;
        }
    }

    com.close();
    std::cout << "Serial port closed." << std::endl;

    return 0;
}
#endif