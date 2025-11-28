#include <Modules/Bus/Modbus/ModbusServer.h>
#ifdef PROJECT_USE_QT
    #include <QDebug>
#endif
int TestModbusServer(int argc, char *argv[]) {
    ModbusServer Server;
#ifdef PROJECT_USE_QT


    QModbusDataUnitMap reg;
    reg.insert(QModbusDataUnit::Coils, { QModbusDataUnit::Coils, 0, 10 });
    reg.insert(QModbusDataUnit::DiscreteInputs, { QModbusDataUnit::DiscreteInputs, 0, 10 });
    reg.insert(QModbusDataUnit::InputRegisters, { QModbusDataUnit::InputRegisters, 0, 10 });
    reg.insert(QModbusDataUnit::HoldingRegisters, { QModbusDataUnit::HoldingRegisters, 0, 10 });
    Server.Handle.setMap(reg);

    QModbusDataUnit Data1(QModbusDataUnit::InputRegisters, 0, 10);
    for (int i = 0; i < 10; i++)
        Data1.setValue(i, i);
    qDebug() << Data1.valueCount() << Data1.values();
    Server.Handle.setData(Data1);

    QModbusDataUnit Data2(QModbusDataUnit::InputRegisters, 0, 10);
    for (int i = 0; i < 10; i++)
        Data2.setValue(i, i + 10);
    qDebug() << Data2.valueCount() << Data2.values();
    Server.Handle.setData(Data2);

    QModbusDataUnit Data3(QModbusDataUnit::HoldingRegisters, 0, 10);
    for (int i = 0; i < 10; i++)
        Data3.setValue(i, i + 20);
    qDebug() << Data3.valueCount() << Data3.values();
    Server.Handle.setData(Data3);


    QModbusDataUnit Data4(QModbusDataUnit::HoldingRegisters, 1, 5);
    Server.Handle.data(&Data4);
    qDebug() << Data4.valueCount() << Data4.values();

#endif
    return 0;
}