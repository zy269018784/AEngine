#pragma once

/*
Exceptions:
    Reset
    NMI
    HardFault
    MemManage
    BusFault
    UsageFault
    DebugMonitor
    SVCall
    Interrupts
    2 system-level interrupts
        PendSV
        SysTick
    496 external interrupts
 */

/* Exception Number */
#define EXCEPTION_NUM_RESET                ( 1UL )
#define EXCEPTION_NUM_NMI                  ( 2UL )
#define EXCEPTION_NUM_HARD_FAULT           ( 3UL )
#define EXCEPTION_NUM_MEM_MANAGE           ( 4UL )
#define EXCEPTION_NUM_BUS_FAULT            ( 5UL )
#define EXCEPTION_NUM_USAGE_FAULT          ( 6UL )
#define EXCEPTION_NUM_RESERVED_7           ( 7UL )
#define EXCEPTION_NUM_RESERVED_8           ( 8UL )
#define EXCEPTION_NUM_RESERVED_9           ( 9UL )
#define EXCEPTION_NUM_RESERVED_10          ( 10UL )
#define EXCEPTION_NUM_SVCALL               ( 11UL )
#define EXCEPTION_NUM_DEBUG_MONITOR        ( 12UL )
#define EXCEPTION_NUM_RESERVED_13          ( 13UL )
#define EXCEPTION_NUM_PENDSV               ( 14UL )
#define EXCEPTION_NUM_SYSTICK              ( 15UL )
#define EXCEPTION_NUM_EXT_INT_0            ( 16UL )
#define EXCEPTION_NUM_EXT_INT(n)           ( 16UL + (n) )

/* Exception Priority */
#define EXCEPTION_PRIO_RESET               ( -3 )
#define EXCEPTION_PRIO_NMI                 ( -2 )
#define EXCEPTION_PRIO_HARD_FAULT          ( -1 )

/*
 * 配置Exception Priority
 * SHPR1设置MemManage, BusFault, UsageFault优先级.
 * SHPR2设置SVCall优先级.
 * SHPR3设置PendSV, SysTick优先级.
 */




















