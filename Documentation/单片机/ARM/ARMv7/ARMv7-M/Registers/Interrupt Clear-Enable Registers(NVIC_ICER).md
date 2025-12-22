Interrupt Clear-Enable Registers(NVIC_ICER)
    共有16个NVIC_ICER寄存器, 用NVIC_ICERn表示, n范围[0, 15].
    NVIC_ICERn  禁止中断[32 * n, 32 * n + 31].
    
        NVIC_ICER0   禁止中断[ 0,  31].
        NVIC_ICER1   禁止中断[32,  31].
        ...
        NVIC_ICER14  禁止中断[32 * 14,  32 * 14 + 31].
        NVIC_ICER15  禁止中断[32 * 15,  32 * 14 + 15].
        共480个中断





