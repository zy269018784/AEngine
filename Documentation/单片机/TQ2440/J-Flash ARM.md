1. File/Project Open/TQ2440.jflash
2. Target/Connect
报错:
- ERROR: Flash Id error. Expected 0x12249, found: 0x7F2249
- ERROR: Failed to connect
解决:
依次打开J-Flash ARM→Options/Project settings/flash/选择“Automatically detect flash memory”，确定，然后重新打开下载即可