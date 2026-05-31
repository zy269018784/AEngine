#include <iostream>
#include "FFmpeg/FormatContext.h"
#include "GStreamer/gs.h"
int main(int argc, char **argv)
{
    FormatContext fc;
    std::cout << "hello codec" << std::endl;
    HelloGStreamer();
    return 0;
}