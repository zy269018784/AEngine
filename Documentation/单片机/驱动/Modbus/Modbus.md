Modbus RTU:
    可以基于RS232/RS422/RS485/以太网/Bluetooth/光纤

格式:
    RTU
    TCP
    UDP

寄存器分类:
    线圈(1 bit)(read-writre)
    离散输入寄存器(1 bit)(read-only)
    输入(16 bit)(read-only)
    保持(read-writre)

0x01  读线圈
0x02  读离散输入寄存器
0x03  读保持寄存器
0x04  读输入寄存器
0x05  写单个线圈
0x06  写单个保持寄存器
0x0E  写多个线圈
0x0F  写多个保持寄存器

主站
从站
从站地址
RTU帧格式:
    从站地址 功能码        数据          校验码 
    1 byte  1 byte      n byte        2 byte

TCP帧格式:
    MBAP    功能码        数据           
    7 byte  1 byte      n byte     

MBAP:
    事务处理标识符         1 byte
    协议标识符            2 byte 
    长度                 2 byte
    单位标识符             1 byte

RTU读线圈请求:
    从站地址 功能码        数据          校验码



https://www.bilibili.com/video/BV1CoGrzBESu?spm_id_from=333.788.videopod.episodes&vd_source=d391257128edec6b3351234b98a9965c&p=3




Server:
    modbus_new_tcp
    modbus_tcp_listen
    modbus_tcp_accept
    modbus_free

client:
    modbus_new_tcp
    modbus_connect
    modbus_close
    modbus_free

