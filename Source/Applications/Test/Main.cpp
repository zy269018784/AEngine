#include  <iostream>
#include <ApplicationProgramStatusRegister.h>
int ModbusMain();
int MQTTMain();
int Live555Main(int argc, char** argv);
int SimpleBLEMain(int argc, char** argv);
int SerialPortMain(int argc, char **argv);
int ModelMain(int argc, char **argv);
//int TestD3D12(int argc, char **argv);
int TestD3D12RHI(int argc, char **argv);
int TestVulkanRayTracingPipeline(int argc, char **argv);
int TestD3D12Texture2D(int argc, char **argv);
int TestD3D11Texture2D(int argc, char **argv);
int TestD3D12Cubemap(int argc, char **argv);
int TestD3D10Texture2D(int argc, char **argv);
int TestD3D9Texture2D(int argc, char **argv);
int TestD3D12Texture2DArray(int argc, char **argv);
int TestD3D11Texture2DArray(int argc, char **argv);
/*
 * RHI
 */
int TestD3D11RHITexture2D(int argc, char **argv);
int TestD3D11RHITexture2DArray(int argc, char **argv);
int TestD3D12RHITexture2D(int argc, char **argv);
int TestD3D12RHITexture2DArray(int argc, char **argv);

//int BluezMain(int argc, char **argv);
int SFMLMain(int argc, char **argv);
int RHIExample();
int TestD3D12(int argc, char **argv);
int TestD3D11(int argc, char **argv);
int TestD3D10(int argc, char **argv);
int TestD3D9(int argc, char **argv);
int TestSpirvCross(int argc, char **argv);
int TestIIC(int argc, char **argv);
int main(int argc, char** argv)
{
    void helloAPSR();
    return 0;
    //return TestIIC(argc, argv);
    return TestD3D12Cubemap(argc, argv);
    return TestD3D12RHITexture2DArray(argc, argv);
    return TestD3D12RHITexture2D(argc, argv);
    return TestD3D11RHITexture2DArray(argc, argv);
    return TestD3D11RHITexture2D(argc, argv);
    //return TestVulkanRayTracingPipeline(argc, argv);
    return TestD3D11Texture2D(argc, argv);
    return TestD3D12Texture2D(argc, argv);
    return TestD3D9Texture2D(argc, argv);
    return TestD3D10Texture2D(argc, argv);

    return TestD3D11Texture2DArray(argc, argv);
    return TestD3D12Texture2DArray(argc, argv);

    return RHIExample();
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
