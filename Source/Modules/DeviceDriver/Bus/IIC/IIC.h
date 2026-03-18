#pragma once
#include <cstdint>

class IIC
{
public:
    /*
     * 开始信号:
     *      SCL保持1
     *      SDA由 1 -> 0
     */
    void Start();
    /*
     * 结束信号
     *      SCL保持1
     *      SDA由 0 -> 1
     */
    void Stop();
    void MasterSendACK();
    void MasterWaitACK();
    void SlaveSendACK();
    void NACK();
    void WriteByte(std::uint8_t Byte);
    void Address7BitsWrite();
    void Address7BitsRead();
    void Address7Bits();
    void Address10Bits();
    /*
     * SCL为1时, 接收方从SDA读取数据.
     * SCL为0时, 发送方发送数据到SDA.
     */
    void SCL();
    void SDA();
    void SCL_High();
    void SDA_High();
    void SCL_Low();
    void SDA_Low();
    void ReleaseSDA();
    int SCL_READ();
    int SDA_READ();

    void Delay(int ms);
};