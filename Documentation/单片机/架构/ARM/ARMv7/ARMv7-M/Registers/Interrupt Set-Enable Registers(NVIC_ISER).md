Interrupt Set-Enable Registers(NVIC_ISER)
    共有16个NVIC_ISER寄存器, 用NVIC_ISERn表示, n范围[0, 15].
    NVIC_ISERn  使能中断[32 * n, 32 * n + 31].

    NVIC_ISER0   使能中断[ 0,  31].
    NVIC_ISER1   使能中断[32 *  1,  32 *  1 + 31].
    ...
    NVIC_ISER14  使能中断[32 * 14,  32 * 14 + 31].
    NVIC_ISER15  使能中断[32 * 15,  32 * 15 + 15].
    共496个中断

