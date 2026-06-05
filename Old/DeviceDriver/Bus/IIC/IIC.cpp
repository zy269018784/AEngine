#include "IIC.h"
#include <iostream>

void IIC::Delay(int ms)
{
    std::cout << "Delay(" << ms << ");" << std::endl;
}
/*
 *
 */
void IIC::Start()
{
    SCL_High();
    SDA_High();
    Delay(1);
    SDA_Low();
}

/*
 * 结束信号
 */
void IIC::Stop()
{
    SCL_High();
    SDA_Low();
    Delay(1);
    SDA_High();
}

void IIC::MasterSendACK()
{

}

void IIC::MasterWaitACK()
{
    /*
     * 1. 将SCL拉低, 准备释放SDA
     */
    SCL_Low();

    /*
     * 2. 释放SDA
     */
    ReleaseSDA();

    /*
     * 3. SCL上升沿, 从机会把SDA从高阻态拉低
     */
    SCL_High();

    /*
     * 4. 读取ACK
     */
    if (1 == SDA_READ()) {
        // 收到ACK
    } else {
        // 没收到ACK
    }

    /*
     * 5. 进入下一个时钟周期
     */
    SCL_Low();
}

/*
 * ACK
 */
void IIC::SlaveSendACK()
{
    /*
     * 1. 等待SCL变高(第9个时钟上升沿)
     */
    while (SCL_READ() == 0);

    /*
     * 2. 检测到上升沿立马拉低SDA
     */
    SDA_Low();

    /*
     * 3. 在整个SCL高电平期间保持低电平
     */
    while (SCL_READ() == 1);

    /*
     * 4. SCL变低后释放SDA
     * */
    ReleaseSDA();
}

void IIC::NACK()
{

}

void IIC::WriteByte(std::uint8_t Byte)
{
    int i;
    /* 8个时钟 */
    for (i = 0; i < 8; i++)
    {
        // SCL为0时, 发送方发送数据到SDA.
        SCL_Low();
        if (Byte & 0x80)
            SDA_High();
        else
            SDA_Low();
        Delay(0x1);
        // SCL为1时, 接收方从SDA读取数据.
        SCL_High();
        Delay(0x1);
        Byte <<= 1;
    }
    /* 第9个时钟开始 */
    SCL_Low();
    /* 释放SDA, 进入高阻态.
     * 此时从机会检测到SDA释放, 从机会把SDA变0.
     *
     * */
    ReleaseSDA();
    /* 第9个时钟结束 */
    SCL_High();
    Delay(0x1);
    /* 第10个时钟开始 */
    SCL_Low();
}

void IIC::Address7BitsWrite()
{

}

void IIC::Address7BitsRead()
{

}

void IIC::Address7Bits()
{

}

void IIC::Address10Bits()
{

}
/*
 * SDL为1时, SDA数据可以改变.
 * SDL为0时, SDA数据有效.
 */
void IIC::SCL()
{

}

void IIC::SDA()
{

}

void IIC::SCL_High()
{
    std::cout << "SCL_High;" << std::endl;
}

void IIC::SDA_High()
{
    std::cout << "SDA_High;" << std::endl;
}

void IIC::SCL_Low()
{
    std::cout << "SCL_Low;" << std::endl;
}

void IIC::SDA_Low()
{
    std::cout << "SDA_Low;" << std::endl;
}

/*
 * SDA进去高阻态
 * 输出高电平 = 实际上就是高阻态
 */
void IIC::ReleaseSDA()
{
    SDA_High();
}

int IIC::SCL_READ()
{
    return 0;
}

int IIC::SDA_READ()
{
    return 0;
}
