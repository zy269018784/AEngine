1. 抢占式内核
    configUSE_PREEMPTION

2. tick中断频率
    configTICK_RATE_HZ

3. configSYSTICK_CLOCK_HZ
    Optional parameter for ARM Cortex-M ports only.
    By default ARM Cortex-M ports generate the RTOS tick interrupt from the Cortex-M SysTick timer.
    Most Cortex-M MCUs run the SysTick timer at the same frequency as the MCU itself - when that is the case
    configSYSTICK_CLOCK_HZ is not needed and should be left undefined.
    If the SysTick timer is clocked at a different frequency to the MCU core then set configCPU_CLOCK_HZ
    to the MCU clock frequency, as normal, and configSYSTICK_CLOCK_HZ to the SysTick clock frequency.

4. 最大优先级
    configMAX_PRIORITIES

configUSE_TICKLESS_IDLE
configUSE_16_BIT_TICKS
configMAX_SYSCALL_INTERRUPT_PRIORITY
configMINIMAL_STACK_SIZE
configMAX_PRIORITIES
configUSE_IDLE_HOOK
configUSE_TICK_HOOK

configTOTAL_HEAP_SIZE