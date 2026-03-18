#include "../../Modules/DeviceDriver/Bus/IIC/IIC.h"
#include <iostream>
int TestIIC(int argc, char **argv)
{
    IIC bus;
   // bus.Start();
    bus.WriteByte(0x34);
    //bus.Stop();

    return 0;
}