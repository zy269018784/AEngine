// SerialCom.h
#ifndef SERIAL_COM_H
#define SERIAL_COM_H

#include <CSerialPort/SerialPort.h>
#include <string>
#include <functional>
#include <vector>
#include <atomic>
#include <thread>

using namespace itas109;

class SerialCom {
public:
    SerialCom();
    ~SerialCom();

    // 打开串口
    bool open(const std::string& portName, int baudrate = 115200);

    // 关闭串口
    void close();

    // 检查是否已打开
    bool isOpen();

    // 发送数据
    bool sendData(const std::vector<uint8_t>& data);
    bool sendData(const std::string& data);
    bool sendData(const uint8_t* data, size_t len);

    // 发送字节
    bool sendByte(uint8_t byte);

    // 设置接收回调函数
    void setReceiveCallback(std::function<void(const std::vector<uint8_t>&)> callback);

    // 设置错误回调
    void setErrorCallback(std::function<void(const std::string&)> callback);

    // 获取可用数据长度
    int getAvailableDataLength();

private:
    CSerialPort m_serialPort;
    std::function<void(const std::vector<uint8_t>&)> m_receiveCallback;
    std::function<void(const std::string&)> m_errorCallback;

    // 接收数据线程
    std::thread m_readThread;
    std::atomic<bool> m_running;

    // 接收线程函数
    void readThreadFunc();
};

#endif // SERIAL_COM_H