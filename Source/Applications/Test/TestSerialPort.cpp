#include <iostream>
#include <vector>
#ifdef PROJECT_USE_CSerialPort
    #include <CSerialPort/SerialPort.h>
    #include <CSerialPort/SerialPortInfo.h>
#endif
#include <CSerialPort/SerialPort.h>
using namespace itas109;

int SerialPortMain(int argc, char **argv)
{
    CSerialPort sp;
    std::cout << "serial port main" << std::endl;
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
#endif
    return 0;
}