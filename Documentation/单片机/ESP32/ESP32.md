1.  IDF下载
https://dl.espressif.com/dl/esp-idf/?idf=4.4

https://docs.espressif.com/projects/esp-idf/zh_CN/stable/esp32/api-reference/peripherals/index.html

2. 打开例子工程
C:\Espressif\frameworks\esp-idf-v5.2.6\examples\get-started\hello_world


3.下载程序到开发板
idf.py -p PORT flash


4. RTread

5. LVGL


6. 
Modes of Operation

Application Startup Flow:
	1. First Stage Bootloader in ROM loads second-stage bootloader image to RAM (IRAM & DRAM) from flash
	offset 0x1000.
	2. Second Stage Bootloader loads partition table and main app image from flash. Main app incorporates both
	RAM segments and read-only segments mapped via flash cache.
	3. Application Startup executes. At this point, the second CPU and RTOS scheduler are started, which then run
	the main_task, leading to the execution of app_main.
	
7. API