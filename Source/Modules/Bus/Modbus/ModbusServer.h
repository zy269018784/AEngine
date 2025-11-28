#pragma once
#ifdef PROJECT_USE_QT
    #include <QModbusTcpServer>
#endif

class ModbusServer
{
public:
    ModbusServer();
    ~ModbusServer();
public:
#ifdef PROJECT_USE_QT
    QModbusTcpServer Handle;
#endif

};
