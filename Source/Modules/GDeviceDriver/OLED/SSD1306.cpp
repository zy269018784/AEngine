#include "SSD1306.h"

SSD1306::SSD1306(GObject *Parent)
    : GObject(Parent)
{

}

void SSD1306::WriteCommand(uint8_t Cmd)
{

}

void SSD1306::WriteCommand(uint8_t Cmd, uint8_t Data)
{

}

void SSD1306::Initialize()
{
    TurnOff();
    //OLED_WRITE_COMMAND(0x00);
    //OLED_WRITE_COMMAND(0x10);
    SetDisplayStartLine(0x0);
    /*
     * 亮度拉满
     */
    SetContrastControl(0xff);
    EnableSegmentRemap();
    EnableCOMRemap();
    SetMultiplexRatio(64);
    SetDisplayOffset(0x00);
    SetDisplayClockDivideRatio_SetOscillatorFrequency(0x80);
    SetPrechargePeriod(0xf1);
    SetCOMPinsHardwareConfiguration(0x12);
    SetVCOMHDeselectLevel(0x40);
    SetPageAddressingMode();
    EnableChargePump();

    /*
    * must disabled
    */
    DisableEntireDisplay();// Disable Entire Display On (0xa4/0xa5)
    DisableInverse();// Disable Inverse Display On (0xa6/a7)
    TurnOn();
}

void SSD1306::SetPage(uint8_t Page)
{
    uint8_t Cmd = 0xb0 + Page;
    WriteCommand(Cmd);
}



void SSD1306::SetPageAddress(uint8_t Start, uint8_t End)
{
    uint8_t Cmd = 0x22;
    WriteCommand(Cmd);
    WriteCommand(Start);
    WriteCommand(End);
}

void SSD1306::SetColumnAddress(uint8_t Start, uint8_t End)
{
    uint8_t Cmd = 0x21;
    WriteCommand(Cmd);
    WriteCommand(Start);
    WriteCommand(End);
}

void SSD1306::SetHorizontalAddressingMode()
{
    uint8_t Cmd  = 0x20;
    uint8_t Mode = 0x00;
    WriteCommand(Cmd);
    WriteCommand(Mode);
}

void SSD1306::SetVerticalAddressingMode()
{
    uint8_t Cmd  = 0x20;
    uint8_t Mode = 0x01;
    WriteCommand(Cmd);
    WriteCommand(Mode);
}

void SSD1306::SetPageAddressingMode()
{
    uint8_t Cmd  = 0x20;
    uint8_t Mode = 0x02;
    WriteCommand(Cmd);
    WriteCommand(Mode);
}

void SSD1306::SetColumnStartAddress(uint8_t X)
{
    if (X > 127)
        X = 0;

    uint8_t Cmd = 0x0;
    /*
        set the lower nibble of the 8-bit column start address
    */
    Cmd = 0x00 + (X & 0x0F);
    WriteCommand(Cmd);

    /*
        set the higher nibble of the 8-bit column start address
    */
    Cmd = 0x10 + (((X & 0xf0) >> 4));
    WriteCommand(Cmd);
}

void SSD1306::SetDisplayStartLine(uint8_t Line)
{
    uint8_t Cmd = 0x40 + Line;
    WriteCommand(Cmd);
}

void SSD1306::SetDisplayOffset(uint8_t Offset)
{
    uint8_t Cmd = 0xd3;
    WriteCommand(Cmd);
    WriteCommand(Offset);
}

void SSD1306::SetContrastControl(uint8_t Data)
{
    uint8_t Cmd = 0x81;
    WriteCommand(Cmd);
    WriteCommand(Data);
}

void SSD1306::SetMultiplexRatio(uint8_t Ratio)
{
    uint8_t Cmd = 0xa8;
    Ratio -= 0x1;
    WriteCommand(Cmd);
    WriteCommand(Ratio);
}

void SSD1306::SetDisplayClockDivideRatio_SetOscillatorFrequency(uint8_t Data)
{
    uint8_t Cmd = 0xd5;
    WriteCommand(Cmd);
    WriteCommand(Data);
}

void SSD1306::SetPrechargePeriod(uint8_t Data)
{
    uint8_t Cmd = 0xd9;
    WriteCommand(Cmd);
    WriteCommand(Data);
}

void SSD1306::SetVCOMHDeselectLevel(uint8_t Data)
{
    uint8_t Cmd = 0xdb;
    WriteCommand(Cmd);
    WriteCommand(Data);
}

void SSD1306::SetCOMPinsHardwareConfiguration(uint8_t Data)
{
    uint8_t Cmd = 0xda;
    WriteCommand(Cmd);
    WriteCommand(Data);
}

void SSD1306::EnableInverse()
{
    uint8_t Cmd = 0xa7;
    WriteCommand(Cmd);
}

void SSD1306::DisableInverse()
{
    uint8_t Cmd = 0xa6;
    WriteCommand(Cmd);
}

void SSD1306::EnableCOMRemap()
{
    uint8_t Cmd = 0xc8;
    WriteCommand(Cmd);
}

void SSD1306::DisableComRemap()
{
    uint8_t Cmd = 0xc0;
    WriteCommand(Cmd);
}


void SSD1306::EnableSegmentRemap()
{
    uint8_t Cmd = 0xa1;
    WriteCommand(Cmd);
}

void SSD1306::DisableSegmentRemap()
{
    uint8_t Cmd = 0xa0;
    WriteCommand(Cmd);
}

void SSD1306::EnableChargePump()
{
    uint8_t Cmd = 0x8d;
    uint8_t Data = 0x14;
    WriteCommand(Cmd);
    WriteCommand(Data);
}

void SSD1306::DisableChargePump()
{
    uint8_t Cmd = 0x8d;
    uint8_t Data = 0x10;
    WriteCommand(Cmd);
    WriteCommand(Data);
}

void SSD1306::EnableEntireDisplay()
{
    uint8_t Cmd = 0xa5;
    WriteCommand(Cmd);
}

void SSD1306::DisableEntireDisplay()
{
    uint8_t Cmd = 0xa4;
    WriteCommand(Cmd);
}


void SSD1306::TurnOn()
{
    uint8_t Cmd = 0xaf;
    WriteCommand(Cmd);
}

void SSD1306::TurnOff()
{
    uint8_t Cmd = 0xae;
    WriteCommand(Cmd);
}





