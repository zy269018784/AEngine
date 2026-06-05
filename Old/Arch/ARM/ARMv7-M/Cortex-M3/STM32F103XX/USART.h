#pragma once

/* 定义外设基地址 (Peripheral Base Addresses) */
#define PERIPH_BASE           0x40000000UL
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000UL)

/* 定义各USART/UART的基地址 (Base Addresses) */
#define USART1_BASE           (APB2PERIPH_BASE + 0x00003800UL)  /* 0x40013800 - 0x40013BFF */
#define USART2_BASE           (APB1PERIPH_BASE + 0x00004400UL)  /* 0x40004400 - 0x400047FF */
#define USART3_BASE           (APB1PERIPH_BASE + 0x00004800UL)  /* 0x40004800 - 0x40004BFF */
#define UART4_BASE            (APB1PERIPH_BASE + 0x00004C00UL)  /* 0x40004C00 - 0x40004FFF */
#define UART5_BASE            (APB1PERIPH_BASE + 0x00005000UL)  /* 0x40005000 - 0x400053FF */

/* 定义寄存器地址 (Register Addresses) */
/* USART1 寄存器 (挂载在 APB2 总线上) */
#define USART1_SR             ( *( ( volatile uint32_t * ) ( USART1_BASE + 0x00UL ) ) )
#define USART1_DR             ( *( ( volatile uint32_t * ) ( USART1_BASE + 0x04UL ) ) )
#define USART1_BRR            ( *( ( volatile uint32_t * ) ( USART1_BASE + 0x08UL ) ) )
#define USART1_CR1            ( *( ( volatile uint32_t * ) ( USART1_BASE + 0x0CUL ) ) )
#define USART1_CR2            ( *( ( volatile uint32_t * ) ( USART1_BASE + 0x10UL ) ) )
#define USART1_CR3            ( *( ( volatile uint32_t * ) ( USART1_BASE + 0x14UL ) ) )
#define USART1_GTPR           ( *( ( volatile uint32_t * ) ( USART1_BASE + 0x18UL ) ) )

/* USART2 寄存器 (挂载在 APB1 总线上) */
#define USART2_SR             ( *( ( volatile uint32_t * ) ( USART2_BASE + 0x00UL ) ) )
#define USART2_DR             ( *( ( volatile uint32_t * ) ( USART2_BASE + 0x04UL ) ) )
#define USART2_BRR            ( *( ( volatile uint32_t * ) ( USART2_BASE + 0x08UL ) ) )
#define USART2_CR1            ( *( ( volatile uint32_t * ) ( USART2_BASE + 0x0CUL ) ) )
#define USART2_CR2            ( *( ( volatile uint32_t * ) ( USART2_BASE + 0x10UL ) ) )
#define USART2_CR3            ( *( ( volatile uint32_t * ) ( USART2_BASE + 0x14UL ) ) )
#define USART2_GTPR           ( *( ( volatile uint32_t * ) ( USART2_BASE + 0x18UL ) ) )

/* USART3 寄存器 (挂载在 APB1 总线上) */
#define USART3_SR             ( *( ( volatile uint32_t * ) ( USART3_BASE + 0x00UL ) ) )
#define USART3_DR             ( *( ( volatile uint32_t * ) ( USART3_BASE + 0x04UL ) ) )
#define USART3_BRR            ( *( ( volatile uint32_t * ) ( USART3_BASE + 0x08UL ) ) )
#define USART3_CR1            ( *( ( volatile uint32_t * ) ( USART3_BASE + 0x0CUL ) ) )
#define USART3_CR2            ( *( ( volatile uint32_t * ) ( USART3_BASE + 0x10UL ) ) )
#define USART3_CR3            ( *( ( volatile uint32_t * ) ( USART3_BASE + 0x14UL ) ) )
#define USART3_GTPR           ( *( ( volatile uint32_t * ) ( USART3_BASE + 0x18UL ) ) )

/* UART4 寄存器 (挂载在 APB1 总线上，注意：无同步模式，因此部分寄存器行为与USART略有不同) */
#define UART4_SR              ( *( ( volatile uint32_t * ) ( UART4_BASE + 0x00UL ) ) )
#define UART4_DR              ( *( ( volatile uint32_t * ) ( UART4_BASE + 0x04UL ) ) )
#define UART4_BRR             ( *( ( volatile uint32_t * ) ( UART4_BASE + 0x08UL ) ) )
#define UART4_CR1             ( *( ( volatile uint32_t * ) ( UART4_BASE + 0x0CUL ) ) )
#define UART4_CR2             ( *( ( volatile uint32_t * ) ( UART4_BASE + 0x10UL ) ) )
#define UART4_CR3             ( *( ( volatile uint32_t * ) ( UART4_BASE + 0x14UL ) ) )
#define UART4_GTPR            ( *( ( volatile uint32_t * ) ( UART4_BASE + 0x18UL ) ) )

/* UART5 寄存器 (挂载在 APB1 总线上) */
#define UART5_SR              ( *( ( volatile uint32_t * ) ( UART5_BASE + 0x00UL ) ) )
#define UART5_DR              ( *( ( volatile uint32_t * ) ( UART5_BASE + 0x04UL ) ) )
#define UART5_BRR             ( *( ( volatile uint32_t * ) ( UART5_BASE + 0x08UL ) ) )
#define UART5_CR1             ( *( ( volatile uint32_t * ) ( UART5_BASE + 0x0CUL ) ) )
#define UART5_CR2             ( *( ( volatile uint32_t * ) ( UART5_BASE + 0x10UL ) ) )
#define UART5_CR3             ( *( ( volatile uint32_t * ) ( UART5_BASE + 0x14UL ) ) )
#define UART5_GTPR            ( *( ( volatile uint32_t * ) ( UART5_BASE + 0x18UL ) ) )

/* USART1_SR 寄存器位定义 */
#define USART_SR_PE_BIT                ( 1UL << 0UL )   /* Parity Error */
#define USART_SR_FE_BIT                ( 1UL << 1UL )   /* Framing Error */
#define USART_SR_NF_BIT                ( 1UL << 2UL )   /* Noise Flag */
#define USART_SR_ORE_BIT               ( 1UL << 3UL )   /* OverRun Error */
#define USART_SR_IDLE_BIT              ( 1UL << 4UL )   /* IDLE line detected */
#define USART_SR_RXNE_BIT              ( 1UL << 5UL )   /* Read Data Register Not Empty */
#define USART_SR_TC_BIT                ( 1UL << 6UL )   /* Transmission Complete */
#define USART_SR_TXE_BIT               ( 1UL << 7UL )   /* Transmit Data Register Empty */
#define USART_SR_LBD_BIT               ( 1UL << 8UL )   /* LIN Break Detection */
#define USART_SR_CTS_BIT               ( 1UL << 9UL )   /* CTS flag (Clear To Send) */

/* USART_CR1 寄存器位定义 */
#define USART_CR1_UE_BIT               ( 1UL << 13UL )  /* USART Enable */
#define USART_CR1_M_BIT                ( 1UL << 12UL )  /* Word length: 0 = 8 data bits, 1 = 9 data bits */
#define USART_CR1_WAKE_BIT             ( 1UL << 11UL )  /* Wakeup method: 0 = Idle Line, 1 = Address Mark */
#define USART_CR1_PCE_BIT              ( 1UL << 10UL )  /* Parity Control Enable */
#define USART_CR1_PS_BIT               ( 1UL << 9UL )   /* Parity Selection: 0 = Even, 1 = Odd */
#define USART_CR1_PEIE_BIT             ( 1UL << 8UL )   /* Parity Error Interrupt Enable */
#define USART_CR1_TXEIE_BIT            ( 1UL << 7UL )   /* TX Empty Interrupt Enable */
#define USART_CR1_TCIE_BIT             ( 1UL << 6UL )   /* Transmission Complete Interrupt Enable */
#define USART_CR1_RXNEIE_BIT           ( 1UL << 5UL )   /* RX Not Empty Interrupt Enable */
#define USART_CR1_IDLEIE_BIT           ( 1UL << 4UL )   /* IDLE Line Interrupt Enable */
#define USART_CR1_TE_BIT               ( 1UL << 3UL )   /* Transmitter Enable */
#define USART_CR1_RE_BIT               ( 1UL << 2UL )   /* Receiver Enable */
#define USART_CR1_RWU_BIT              ( 1UL << 1UL )   /* Receiver Wakeup */
#define USART_CR1_SBK_BIT              ( 1UL << 0UL )   /* Send Break */

/* USART_CR2 寄存器位定义 */
#define USART_CR2_ADD_BIT0              ( 1UL << 0UL )   /* Address bit 0 */
#define USART_CR2_ADD_BIT1              ( 1UL << 1UL )   /* Address bit 1 */
#define USART_CR2_ADD_BIT2              ( 1UL << 2UL )   /* Address bit 2 */
#define USART_CR2_ADD_BIT3              ( 1UL << 3UL )   /* Address bit 3 */
#define USART_CR2_ADD_MASK              ( 0xFUL << 0UL ) /* Address mask (bits 0-3) */
#define USART_CR2_LBDL_BIT              ( 1UL << 5UL )   /* LIN Break Detection Length: 0=10bit, 1=11bit */
#define USART_CR2_LBDIE_BIT             ( 1UL << 6UL )   /* LIN Break Detection Interrupt Enable */
#define USART_CR2_LBCL_BIT              ( 1UL << 8UL )   /* Last Bit Clock Pulse (同步模式) */
#define USART_CR2_CPHA_BIT              ( 1UL << 9UL )   /* Clock Phase (同步模式) */
#define USART_CR2_CPOL_BIT              ( 1UL << 10UL )  /* Clock Polarity (同步模式) */
#define USART_CR2_CLKEN_BIT             ( 1UL << 11UL )  /* Clock Enable (同步模式使能) */
#define USART_CR2_STOP_BIT0             ( 1UL << 12UL )  /* Stop bits bit 0 */
#define USART_CR2_STOP_BIT1             ( 1UL << 13UL )  /* Stop bits bit 1 */
#define USART_CR2_STOP_MASK             ( 0x3UL << 12UL )/* Stop bits mask */
#define USART_CR2_STOP_1BIT             ( 0x0UL << 12UL )/* 1 stop bit */
#define USART_CR2_STOP_0_5BIT           ( 0x1UL << 12UL )/* 0.5 stop bit (SmartCard mode) */
#define USART_CR2_STOP_2BIT             ( 0x2UL << 12UL )/* 2 stop bits */
#define USART_CR2_STOP_1_5BIT           ( 0x3UL << 12UL )/* 1.5 stop bits (SmartCard mode) */
#define USART_CR2_LINEN_BIT             ( 1UL << 14UL )  /* LIN Mode Enable */

/* USART_CR3 寄存器位定义 */
#define USART_CR3_EIE_BIT               ( 1UL << 0UL )   /* Error Interrupt Enable (FE/ORE/NE) */
#define USART_CR3_IREN_BIT              ( 1UL << 1UL )   /* Infrared Mode Enable (IrDA) */
#define USART_CR3_IRLP_BIT              ( 1UL << 2UL )   /* Infrared Low Power (IrDA低功耗模式) */
#define USART_CR3_HDSEL_BIT             ( 1UL << 3UL )   /* Half-Duplex Selection (半双工选择) */
#define USART_CR3_NACK_BIT              ( 1UL << 4UL )   /* SmartCard NACK Enable */
#define USART_CR3_SCEN_BIT              ( 1UL << 5UL )   /* SmartCard Mode Enable */
#define USART_CR3_DMAR_BIT              ( 1UL << 6UL )   /* DMA Receiver Enable (DMA接收使能) */
#define USART_CR3_DMAT_BIT              ( 1UL << 7UL )   /* DMA Transmitter Enable (DMA发送使能) */
#define USART_CR3_RTSE_BIT              ( 1UL << 8UL )   /* RTS Enable (硬件流控RTS使能) */
#define USART_CR3_CTSE_BIT              ( 1UL << 9UL )   /* CTS Enable (硬件流控CTS使能) */
#define USART_CR3_CTSIE_BIT             ( 1UL << 10UL )  /* CTS Interrupt Enable (CTS中断使能) */
#define USART_CR3_ONEBIT_BIT            ( 1UL << 11UL )  /* One Sample Bit Method (单采样模式) */
#define USART_CR3_OVRDIS_BIT            ( 1UL << 12UL )  /* Overrun Disable (溢出禁用) */
#define USART_CR3_DDRE_BIT              ( 1UL << 13UL )  /* DMA Disable on Reception Error */
#define USART_CR3_DEM_BIT               ( 1UL << 14UL )  /* Driver Enable Mode */
#define USART_CR3_DEP_BIT               ( 1UL << 15UL )  /* Driver Enable Polarity */