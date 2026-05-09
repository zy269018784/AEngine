#pragma once

/* Base Priority Mask Register */

/* Priority Mask Register */

/* Fault Mask Register */

/* SysTick Control and Status Register */
#define SYST_CSR             ( *( ( volatile uint32_t * ) 0xe000e010 ) )
/* SysTick Control and Status Register Bits */
#define SYSTICK_COUNTFLAG_BIT       ( 1UL << 16UL )
#define SYSTICK_CLKSOURCE_BIT       ( 1UL << 2UL )
#define SYSTICK_TICKINT_BIT         ( 1UL << 1UL )
#define SYSTICK_ENABLE_BIT          ( 1UL << 0UL )

/* SysTick Reload Value Register */
#define SYST_RVR             ( *( ( volatile uint32_t * ) 0xe000e014 ) )
#define SYST_RVR_RELOAD_MASK  0x00FFFFFF

/* SysTick Current Value Register */
#define SYST_CVR             ( *( ( volatile uint32_t * ) 0xe000e018 ) )

/* SysTick Calibration value Register */
#define SYST_CALIB           ( *( ( volatile uint32_t * ) 0xe000ed1c ) )

/* Interrupt Set-Enable Registers */
#define NVIC_ISER0           ( *( ( volatile uint32_t * ) 0xe000e100 ) )
#define NVIC_ISER1           ( *( ( volatile uint32_t * ) 0xe000e104 ) )
#define NVIC_ISER2           ( *( ( volatile uint32_t * ) 0xe000e108 ) )
#define NVIC_ISER3           ( *( ( volatile uint32_t * ) 0xe000e10c ) )
#define NVIC_ISER4           ( *( ( volatile uint32_t * ) 0xe000e110 ) )
#define NVIC_ISER5           ( *( ( volatile uint32_t * ) 0xe000e114 ) )
#define NVIC_ISER6           ( *( ( volatile uint32_t * ) 0xe000e118 ) )
#define NVIC_ISER7           ( *( ( volatile uint32_t * ) 0xe000e11c ) )
#define NVIC_ISER8           ( *( ( volatile uint32_t * ) 0xe000e120 ) )
#define NVIC_ISER9           ( *( ( volatile uint32_t * ) 0xe000e124 ) )
#define NVIC_ISER10          ( *( ( volatile uint32_t * ) 0xe000e128 ) )
#define NVIC_ISER11          ( *( ( volatile uint32_t * ) 0xe000e12c ) )
#define NVIC_ISER12          ( *( ( volatile uint32_t * ) 0xe000e130 ) )
#define NVIC_ISER13          ( *( ( volatile uint32_t * ) 0xe000e134 ) )
#define NVIC_ISER14          ( *( ( volatile uint32_t * ) 0xe000e138 ) )
#define NVIC_ISER15          ( *( ( volatile uint32_t * ) 0xe000e13c ) )

/* Interrupt Clear-Enable Registers */
#define NVIC_ICER0           ( *( ( volatile uint32_t * ) 0xe000e180 ) )
#define NVIC_ICER1           ( *( ( volatile uint32_t * ) 0xe000e184 ) )
#define NVIC_ICER2           ( *( ( volatile uint32_t * ) 0xe000e188 ) )
#define NVIC_ICER3           ( *( ( volatile uint32_t * ) 0xe000e18c ) )
#define NVIC_ICER4           ( *( ( volatile uint32_t * ) 0xe000e190 ) )
#define NVIC_ICER5           ( *( ( volatile uint32_t * ) 0xe000e194 ) )
#define NVIC_ICER6           ( *( ( volatile uint32_t * ) 0xe000e198 ) )
#define NVIC_ICER7           ( *( ( volatile uint32_t * ) 0xe000e19c ) )
#define NVIC_ICER8           ( *( ( volatile uint32_t * ) 0xe000e1a0 ) )
#define NVIC_ICER9           ( *( ( volatile uint32_t * ) 0xe000e1a4 ) )
#define NVIC_ICER10          ( *( ( volatile uint32_t * ) 0xe000e1a8 ) )
#define NVIC_ICER11          ( *( ( volatile uint32_t * ) 0xe000e1ac ) )
#define NVIC_ICER12          ( *( ( volatile uint32_t * ) 0xe000e1b0 ) )
#define NVIC_ICER13          ( *( ( volatile uint32_t * ) 0xe000e1b4 ) )
#define NVIC_ICER14          ( *( ( volatile uint32_t * ) 0xe000e1b8 ) )
#define NVIC_ICER15          ( *( ( volatile uint32_t * ) 0xe000e1bc ) )

/* Interrupt Set-Pending Registers */
#define NVIC_ISPR0           ( *( ( volatile uint32_t * ) 0xe000e200 ) )
#define NVIC_ISPR1           ( *( ( volatile uint32_t * ) 0xe000e204 ) )
#define NVIC_ISPR2           ( *( ( volatile uint32_t * ) 0xe000e208 ) )
#define NVIC_ISPR3           ( *( ( volatile uint32_t * ) 0xe000e20c ) )
#define NVIC_ISPR4           ( *( ( volatile uint32_t * ) 0xe000e210 ) )
#define NVIC_ISPR5           ( *( ( volatile uint32_t * ) 0xe000e214 ) )
#define NVIC_ISPR6           ( *( ( volatile uint32_t * ) 0xe000e218 ) )
#define NVIC_ISPR7           ( *( ( volatile uint32_t * ) 0xe000e21c ) )
#define NVIC_ISPR8           ( *( ( volatile uint32_t * ) 0xe000e220 ) )
#define NVIC_ISPR9           ( *( ( volatile uint32_t * ) 0xe000e224 ) )
#define NVIC_ISPR10          ( *( ( volatile uint32_t * ) 0xe000e228 ) )
#define NVIC_ISPR11          ( *( ( volatile uint32_t * ) 0xe000e22c ) )
#define NVIC_ISPR12          ( *( ( volatile uint32_t * ) 0xe000e230 ) )
#define NVIC_ISPR13          ( *( ( volatile uint32_t * ) 0xe000e234 ) )
#define NVIC_ISPR14          ( *( ( volatile uint32_t * ) 0xe000e238 ) )
#define NVIC_ISPR15          ( *( ( volatile uint32_t * ) 0xe000e23c ) )

// 中断挂起清除寄存器 (Clear-Pending)
#define NVIC_ICPR0           ( *( ( volatile uint32_t * ) 0xe000e280 ) )
#define NVIC_ICPR1           ( *( ( volatile uint32_t * ) 0xe000e284 ) )
#define NVIC_ICPR2           ( *( ( volatile uint32_t * ) 0xe000e288 ) )
#define NVIC_ICPR3           ( *( ( volatile uint32_t * ) 0xe000e28c ) )
#define NVIC_ICPR4           ( *( ( volatile uint32_t * ) 0xe000e290 ) )
#define NVIC_ICPR5           ( *( ( volatile uint32_t * ) 0xe000e294 ) )
#define NVIC_ICPR6           ( *( ( volatile uint32_t * ) 0xe000e298 ) )
#define NVIC_ICPR7           ( *( ( volatile uint32_t * ) 0xe000e29c ) )
#define NVIC_ICPR8           ( *( ( volatile uint32_t * ) 0xe000e2a0 ) )
#define NVIC_ICPR9           ( *( ( volatile uint32_t * ) 0xe000e2a4 ) )
#define NVIC_ICPR10          ( *( ( volatile uint32_t * ) 0xe000e2a8 ) )
#define NVIC_ICPR11          ( *( ( volatile uint32_t * ) 0xe000e2ac ) )
#define NVIC_ICPR12          ( *( ( volatile uint32_t * ) 0xe000e2b0 ) )
#define NVIC_ICPR13          ( *( ( volatile uint32_t * ) 0xe000e2b4 ) )
#define NVIC_ICPR14          ( *( ( volatile uint32_t * ) 0xe000e2b8 ) )
#define NVIC_ICPR15          ( *( ( volatile uint32_t * ) 0xe000e2bc ) )

/* Interrupt Clear-Pending Registers */
#define NVIC_IABR0           ( *( ( volatile uint32_t * ) 0xe000e300 ) )
#define NVIC_IABR1           ( *( ( volatile uint32_t * ) 0xe000e304 ) )
#define NVIC_IABR2           ( *( ( volatile uint32_t * ) 0xe000e308 ) )
#define NVIC_IABR3           ( *( ( volatile uint32_t * ) 0xe000e30c ) )
#define NVIC_IABR4           ( *( ( volatile uint32_t * ) 0xe000e310 ) )
#define NVIC_IABR5           ( *( ( volatile uint32_t * ) 0xe000e314 ) )
#define NVIC_IABR6           ( *( ( volatile uint32_t * ) 0xe000e318 ) )
#define NVIC_IABR7           ( *( ( volatile uint32_t * ) 0xe000e31c ) )
#define NVIC_IABR8           ( *( ( volatile uint32_t * ) 0xe000e320 ) )
#define NVIC_IABR9           ( *( ( volatile uint32_t * ) 0xe000e324 ) )
#define NVIC_IABR10          ( *( ( volatile uint32_t * ) 0xe000e328 ) )
#define NVIC_IABR11          ( *( ( volatile uint32_t * ) 0xe000e32c ) )
#define NVIC_IABR12          ( *( ( volatile uint32_t * ) 0xe000e330 ) )
#define NVIC_IABR13          ( *( ( volatile uint32_t * ) 0xe000e334 ) )
#define NVIC_IABR14          ( *( ( volatile uint32_t * ) 0xe000e338 ) )
#define NVIC_IABR15          ( *( ( volatile uint32_t * ) 0xe000e33c ) )

/* Interrupt Control and State Register */
#define ICSR                 ( *( ( volatile uint32_t * ) 0xe000ed04 ) )
#define PENDSVSET_BIT        ( 1UL << 28UL )
#define PENDSVCLR_BIT        ( 1UL << 27UL )
#define PENDSTSET_BIT        ( 1UL << 26UL )
#define PENDSTCLR_BIT        ( 1UL << 25UL )
#define ISRPREEMPT_BIT       ( 1UL << 23UL )
#define ISRPENDING_BIT       ( 1UL << 22UL )
#define VECTPENDING_MASK     ( 0x3FFUL << 12UL )
#define VECTPENDING_SHIFT    ( 12UL )
#define RETTOBASE_BIT        ( 1UL << 11UL )
#define VECTACTIVE_MASK      ( 0x3FFUL << 0UL )
#define VECTACTIVE_SHIFT     ( 0UL )


/* System Handler Priority Register 1 */
#define SHPR1                ( *( ( volatile uint32_t * ) 0xe000ed18 ) )

/* System Handler Priority Register 2 */
#define SHPR2                ( *( ( volatile uint32_t * ) 0xe000ed1c ) )

/* System Handler Priority Register 3 */
#define SHPR3                ( *( ( volatile uint32_t * ) 0xe000ed20 ) )

/* System Handler Control and State Register */
#define SHCSR                ( *( ( volatile uint32_t * ) 0xe000ed24 ) )

/* System Handler Control and State Register */
#define SHCSR                ( *( ( volatile uint32_t * ) 0xe000ed24 ) )
#define SHCSR_BIT_USGFAULTENA          ( 1UL << 18UL )  // Enable UsageFault exception
#define SHCSR_BIT_BUSFAULTENA          ( 1UL << 17UL )  // Enable BusFault exception
#define SHCSR_BIT_MEMFAULTENA          ( 1UL << 16UL )  // Enable MemManage exception
#define SHCSR_BIT_SVCALLPENDED         ( 1UL << 15UL )  // SVCall pending
#define SHCSR_BIT_BUSFAULTPENDED       ( 1UL << 14UL )  // BusFault pending
#define SHCSR_BIT_MEMFAULTPENDED       ( 1UL << 13UL )  // MemManage pending
#define SHCSR_BIT_USGFAULTPENDED       ( 1UL << 12UL )  // UsageFault pending
#define SHCSR_BIT_SYSTICKACT           ( 1UL << 11UL )  // SysTick active
#define SHCSR_BIT_PENDSVACT            ( 1UL << 10UL )  // PendSV active
#define SHCSR_BIT_MONITORACT           ( 1UL << 8UL )   // Debug monitor active
#define SHCSR_BIT_SVCALLACT            ( 1UL << 7UL )   // SVCall active
#define SHCSR_BIT_USGFAULTACT          ( 1UL << 3UL )   // UsageFault active
#define SHCSR_BIT_BUSFAULTACT          ( 1UL << 1UL )   // BusFault active
#define SHCSR_BIT_MEMFAULTACT          ( 1UL << 0UL )   // MemManage active