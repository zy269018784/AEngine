1. J-Flash（SEGGER，最常用）

打开 J-Flash → File → Open Data File 打开 HEX 或 BIN
打开 BIN 时需填写起始地址
File → Save Data File As 选择目标格式

# HEX 转 BIN
STM32_Programmer_CLI -c port=SWD -i file.hex -o file.bin

# BIN 转 HEX（需指定地址）
STM32_Programmer_CLI -c port=SWD -i file.bin 0x08000000 -o file.hex

# HEX 转 BIN
objcopy -I ihex -O binary input.hex output.bin

# BIN 转 HEX
objcopy -I binary -O ihex input.bin output.hex