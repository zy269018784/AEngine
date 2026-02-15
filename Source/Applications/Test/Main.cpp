#include  <iostream>
int ModbusMain();
int MQTTMain();
int Live555Main(int argc, char** argv);
int SimpleBLEMain(int argc, char** argv);
int SerialPortMain(int argc, char **argv);
int ModelMain(int argc, char **argv);
//int TestD3D12(int argc, char **argv);
int TestD3D12RHI(int argc, char **argv);
//int BluezMain(int argc, char **argv);
int SFMLMain(int argc, char **argv);
int RHIExample();
int TestD3D12(int argc, char **argv);
int TestD3D11(int argc, char **argv);
int TestD3D10(int argc, char **argv);
int TestD3D9(int argc, char **argv);
int TestSpirvCross(int argc, char **argv);
int main(int argc, char** argv)
{
    //return RHIExample();
    return TestD3D12RHI(argc, argv);
    return TestSpirvCross(argc, argv);

    return TestD3D9(argc, argv);

    return RHIExample();
    return SFMLMain(argc, argv);
  //  return BluezMain(argc, argv);
    return SimpleBLEMain(argc, argv);
    return TestD3D12RHI(argc, argv);
    //return TestD3D12(argc, argv);
    return ModelMain(argc, argv);
    return SerialPortMain(argc, argv);

    return Live555Main(argc, argv);
    return ModbusMain();
    return 0;
}
