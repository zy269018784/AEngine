#pragma once
#include <cstdint>
/*
 *  128x64
 *  分为8个page, 每个page大小128x8
 *  支持行和列的remapping
 */
class SSD1306
{
public:
    void WriteCommand(uint8_t Cmd);
    void SetPage(uint8_t Page);
    void SetPageAddress(uint8_t Start, uint8_t End);
    void SetColumnAddress(uint8_t Start, uint8_t End);
    void SetHorizontalAddressingMode();
    void SetVerticalAddressingMode();
    void SetPageAddressingMode();
    /*
        X: [0, 127]
    */
    void SetColumnStartAddress(uint8_t X);
    /*
     * Line: [0, 63]
     */
    void SetDisplayStartLine(uint8_t Line);
    void SetDisplayOffset(uint8_t Offset);
    void EnableInverse();
    void DisableInverse();
    void EnableCOMRemap();
    void DisableComRemap();
    void EnableSegmentRemap();
    void DisableSegmentRemap();
    void EnableChargePump();
    void DisableChargePump();
    void TurnOn();
    void TurnOff();

private:

};