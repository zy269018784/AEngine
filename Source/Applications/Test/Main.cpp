#include  <iostream>
int ModbusMain();
int MQTTMain();
int Live555Main(int argc, char** argv);
int SimpleBLEMain(int argc, char** argv);
int main(int argc, char** argv)
{
    return SimpleBLEMain(argc, argv);
    return Live555Main(argc, argv);
    return ModbusMain();
    return 0;
}
