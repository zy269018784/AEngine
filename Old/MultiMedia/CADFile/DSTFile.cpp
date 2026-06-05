#include "DSTFile.h"
#include <fstream>
bool DSTFile::Write(const std::string name)
{
    int a = 123;

    std::ofstream outFile(name);
    outFile << "LA:HEDERA 1        " << std::endl;
    outFile << "ST:   1553" << std::endl;
    outFile << "CO:  2" << std::endl;
    outFile << "+X:   77" << std::endl;
    outFile << "-X:   77" << std::endl;
    outFile << "+Y:  225" << std::endl;
    outFile << "-Y:  225" << std::endl;
    outFile << "AX:+    0" << std::endl;
    outFile << "AY:+    0" << std::endl;
    outFile << "MX:+    0" << std::endl;
    outFile << "MY:+    0" << std::endl;

    outFile.write((char *)&a, 4);
    outFile.close();

    std::ofstream binFile(name, std::ios::binary | std::ios::app);
   // binFile.write((char *)&a, 4);
    binFile.close();
    return true;
}
