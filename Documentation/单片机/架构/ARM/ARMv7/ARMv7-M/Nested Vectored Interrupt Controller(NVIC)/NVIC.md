The Armv7-M NVIC architecture supports up to 496 interrupts.

寄存器:
    Interrupt Set-Enable Registers(NVIC_ISER)
    Interrupt Clear-Enable Registers(NVIC_ICER)
    Interrupt Set-Pending Registers(NVIC_ISPR)
    Interrupt Clear-Pending Registers(NVIC_ICPR)
    Interrupt Active Bit Registers(NVIC_IABR)
    Interrupt Priority Registers(NVIC_IPR)


中断状态:
    触发     CPU开始执行ISR    ISR执行完毕
    │           │               │
    ▼           ▼               ▼
    Pending ──► Active ───────► Inactive











