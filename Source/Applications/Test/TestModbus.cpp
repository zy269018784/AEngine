#ifdef PROJECT_USE_MODBUS
    #include <modbus/modbus-rtu.h>
    #include <modbus/modbus-tcp.h>
#endif
#include  <iostream>
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

int ModbusTCPServerMain() {
    modbus_t *mb;
    mb = modbus_new_tcp("127.0.0.1", 1502);
    while (1) {
        int s = modbus_tcp_listen(mb, 1);
        modbus_tcp_accept(mb, &s);
        std::cout << "accept ok" << std::endl;
    }
    modbus_free(mb);
    return 0;
}

int ModbusTCPClientMain()
{
    int ErrorCode = 0;
    modbus_t *mb;
    mb = modbus_new_tcp("127.0.0.1", 1502);
    ErrorCode = modbus_connect(mb);
    if (ErrorCode)
    {
        std::cout  << "modbus_connect falied " << modbus_strerror(errno) << std::endl;
        return -1;
    }
    modbus_close(mb);
    modbus_free(mb);
    return 0;
}

int ModbusTCPMain() {
    std::cout << "hello, modbus tcp" << std::endl;
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
    return 0;
}

int ModbusRTUMain() {
    std::cout << "hello, modbus rtu" << std::endl;
    return 0;
}