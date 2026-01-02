#ifdef PROJECT_USE_MODBUS
    #include <modbus/modbus-rtu.h>
    #include <modbus/modbus-tcp.h>
#endif
#ifdef PROJECT_USE_QT
    #include <QModbusServer>
#endif
#include <thread>
#include <iostream>
int ModbusTCPMain();
int ModbusTCPServerMain();
int ModbusTCPClientMain();
int ModbusRTUMain();
int ModbusMain()
{
    return ModbusTCPServerMain();
    return ModbusTCPClientMain();
    return 0;
}

int ModbusTCPServerMain()
{
    int ErrorCode = 0;

#ifdef PROJECT_USE_MODBUS
    modbus_t *mb;
    mb = modbus_new_tcp("127.0.0.1", 1502);
    modbus_mapping_t *mb_mapping = modbus_mapping_new_start_address(
            0,   // 线圈起始地址
            100, // 线圈数量
            0,   // 离散输入起始地址
            100, // 离散输入数量
            0,   // 保持寄存器起始地址
            100, // 保持寄存器数量
            0,   // 输入寄存器起始地址
            100  // 输入寄存器数量
        );

    if (mb_mapping == NULL) {
        fprintf(stderr, "Failed to allocate mapping: %s\n", modbus_strerror(errno));
        modbus_free(mb);
        return -1;
    }

    //while (1) {
        int s = modbus_tcp_listen(mb, 1);
        ErrorCode = modbus_tcp_accept(mb, &s);
        if (-1 == ErrorCode)
        {
            std::cout  << "modbus_tcp_accept falied " << modbus_strerror(errno) << std::endl;
            return -1;
        }
        std::cout << "accept ok" << std::endl;

   // }

    std::this_thread::sleep_for(std::chrono::seconds(100));
    modbus_free(mb);
#endif
    return 0;
}

int ModbusTCPClientMain()
{
    int ErrorCode = 0;
#ifdef PROJECT_USE_MODBUS
    modbus_t *mb;
    mb = modbus_new_tcp("127.0.0.1", 1502);
    ErrorCode = modbus_connect(mb);
    if (ErrorCode)
    {
        std::cout  << "modbus_connect falied " << modbus_strerror(errno) << std::endl;
        return -1;
    }

    uint16_t tab_reg[32];

    ErrorCode = modbus_read_registers(mb, 0, 1, tab_reg);
    if (ErrorCode)
    {
        std::cout  << "modbus_read_registers falied " << modbus_strerror(errno) << std::endl;
        return -1;
    }
    std::cout  << tab_reg[0] << std::endl;

    modbus_close(mb);
    modbus_free(mb);
#endif
    return 0;
}

int ModbusTCPMain() {
    std::cout << "hello, modbus tcp" << std::endl;
#ifdef PROJECT_USE_MODBUS
    modbus_t *mb;


    uint16_t tab_reg[32];

    mb = modbus_new_tcp("127.0.0.1", 1502);

    int ErrorCode = 0;

    ErrorCode = modbus_connect(mb);
    if (ErrorCode)
    {
        std::cout  << "modbus_connect falied " << modbus_strerror(errno) << std::endl;
        return -1;
    }

    //for (int i = 0; i < 5; i++)
    ErrorCode = modbus_write_register(mb, 0, 0);
    if (ErrorCode)
    {
        std::cout  << "modbus_write_register falied " << modbus_strerror(errno)  << std::endl;
        return -1;
    }

    ErrorCode = modbus_read_registers(mb, 0, 1, tab_reg);
    if (ErrorCode)
    {
        std::cout  << "modbus_read_registers falied " << modbus_strerror(errno) << std::endl;
        return -1;
    }
    std::cout  << "read  " << ErrorCode << "registers" << std::endl;

    for (int i = 0; i < 5; i++)
        std::cout << tab_reg[i] << " " ;

    modbus_close(mb);
    modbus_free(mb);
#endif
    return 0;
}

int ModbusRTUMain() {
    std::cout << "hello, modbus rtu" << std::endl;
    return 0;
}
