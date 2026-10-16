UART_InitTypeDef


| Word Length         | 描述   |
|---------------------|------|
| UART_WORDLENGTH_8B |  |
| UART_WORDLENGTH_9B |    |

| Stop Bits         | 描述   |
|---------------------|------|
| UART_STOPBITS_1 |  |
| UART_STOPBITS_2 |    |

| Parity         | 描述   |
|---------------------|------|
| UART_PARITY_NONE |  |
| UART_PARITY_EVEN |    |
| UART_PARITY_ODD |    |

| Mode         | 描述   |
|---------------------|------|
| UART_MODE_RX |  |
| UART_MODE_TX |    |
| UART_MODE_TX_RX |    |

| Clock         | 描述   |
|---------------------|------|
| UART_CLOCK_DISABLE |  |
| UART_CLOCK_ENABLE |    |


| Hardware Flow Control         | 描述   |
|---------------------|------|
| UART_HWCONTROL_NONE |  |
| UART_HWCONTROL_RTS |    |
| UART_HWCONTROL_CTS |    |
| UART_HWCONTROL_RTS_CTS |    |

| 宏                      | 描述                                                                   |
|------------------------|----------------------------------------------------------------------|
| __HAL_UART_CLEAR_FLAG  | 清除Flag (UART_FLAG_CTS, UART_FLAG_LBD,  UART_FLAG_TC, UART_FLAG_RXNE) |
| __HAL_UART_CLEAR_PEFLAG |                                                                      |
| __HAL_UART_CLEAR_FEFLAG |                                                                      |
| __HAL_UART_CLEAR_NEFLAG |                                                                      |
| __HAL_UART_CLEAR_OREFLAG |                                                                      |
| __HAL_UART_CLEAR_IDLEFLAG |                                                                      |
| __HAL_UART_ENABLE_IT   | 使能中断                                                                 |
| __HAL_UART_DISABLE_IT  | 关闭中断                                                                 |

| API | 描述 |
| --- | --- |
| HAL_UART_Init | 初始化 UART |
| HAL_UART_DeInit | 反初始化 UART |
| HAL_UART_Transmit | 阻塞方式发送数据 |
| HAL_UART_Receive | 阻塞方式接收数据 |
| HAL_UART_Transmit_IT | 中断方式发送数据 |
| HAL_UART_Receive_IT | 中断方式接收数据 |
| HAL_UART_Transmit_DMA | DMA 方式发送数据 |
| HAL_UART_Receive_DMA | DMA 方式接收数据 |
| HAL_UART_DMAPause | 暂停 UART DMA 传输 |
| HAL_UART_DMAResume | 恢复 UART DMA 传输 |
| HAL_UART_DMAStop | 停止 UART DMA 传输 |
