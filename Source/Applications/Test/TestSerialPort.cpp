#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#ifdef PROJECT_USE_CSerialPort
    #include <CSerialPort/SerialPort.h>
    #include <CSerialPort/SerialPortInfo.h>
#endif
#include <stdio.h>
using namespace itas109;

std::string char2hexstr(const char *str, int len)
{
    static const char hexTable[17] = "0123456789ABCDEF";

    std::string result;
    for (int i = 0; i < len; ++i)
    {
        result += "0x";
        result += hexTable[(unsigned char)str[i] / 16];
        result += hexTable[(unsigned char)str[i] % 16];
        result += " ";
    }
    return result;
}

int countRead = 0;


class MyListener : public CSerialPortListener, public CSerialPortHotPlugListener
{
public:
    MyListener(CSerialPort *sp)
        : p_sp(sp){};

    void onReadEvent(const char *portName, unsigned int readBufferLen)
    {
        //std::cout << "onReadEvent " << portName << std::endl;
       // return;
        if (readBufferLen > 0)
        {
            char *data = new char[readBufferLen + 1]; // '\0'

            if (data)
            {
                // read
                int recLen = p_sp->readData(data, readBufferLen);

                if (recLen > 0)
                {
                    data[recLen] = '\0';
                    std::cout  << data << std::endl;
                    //printf("%s - Count: %d, Length: %d, Str: %s, Hex: %s\n", portName, ++countRead, recLen, data, char2hexstr(data, recLen).c_str());

                    // return receive data
                    //p_sp->writeData(data, recLen);
                }

                delete[] data;
                data = NULL;
            }
        }
    };

    void onHotPlugEvent(const char *portName, int isAdd)
    {
        printf("portName: %s, isAdded: %d\n", portName, isAdd);
    }

private:
    CSerialPort *p_sp;
};

int SerialPortMain(int argc, char **argv)
{
    CSerialPort sp;
    std::cout << "serial port main" << std::endl;
    MyListener listener(&sp);
    // connect for read
    sp.connectReadEvent(&listener);
    // connect for hot plug
    sp.connectHotPlugEvent(&listener);
#if 1
    std::vector<SerialPortInfo> m_availablePortsList = CSerialPortInfo::availablePortInfos();


    int availablePortCount = (int)m_availablePortsList.size();

    for (int i = 1; i <= availablePortCount; ++i)
    {
        SerialPortInfo serialPortInfo = m_availablePortsList[i - 1];
        std::cout     << serialPortInfo.portName << " "
                    << serialPortInfo.description << " "
                    <<  serialPortInfo.hardwareId << std::endl;
    }
    const char *portName = m_availablePortsList[1].portName;
    sp.init(portName,              // windows:COM1 Linux:/dev/ttyS0
            itas109::BaudRate9600, // baudrate
            itas109::ParityNone,   // parity
            itas109::DataBits8,    // data bit
            itas109::StopOne,      // stop bit
            itas109::FlowNone,     // flow
            4096                   // read buffer size
    );
    sp.open();
    if (sp.isOpen())
    {
        std::cout << "is opened "  << std::endl;
    }
    sp.setReadIntervalTimeout(0);         // read interval timeout 0ms
    sp.setByteReadBufferFullNotify(3276); // 4096*0.8 // buffer full notify
    char buffer[1024];
    int n = 0;
   // std::cout << "read " << n << std::endl;
    //buffer[n] = '\0';
    //std::cout << buffer << std::endl;
    while(1)
    {
       // n = sp.readData(buffer, 1024);
        //std::cout << "read " << n << std::endl;
        sp.writeData("hello", 6);
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
    sp.close();
#endif
    return 0;
}