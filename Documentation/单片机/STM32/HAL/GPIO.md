void HAL_GPIO_Init(GPIO_TypeDef  *GPIOx, GPIO_InitTypeDef *GPIO_Init)
void HAL_GPIO_DeInit(GPIO_TypeDef  *GPIOx, uint32_t GPIO_Pin)
void HAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, GPIO_PinState PinState)
GPIO_PinState HAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
HAL_StatusTypeDef HAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin)
void HAL_GPIO_EXTI_IRQHandler(uint16_t GPIO_Pin)
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)

#define  GPIO_MODE_INPUT                        0x00000000u   /*!< Input Floating Mode                   */
#define  GPIO_MODE_OUTPUT_PP                    0x00000001u   /*!< Output Push Pull Mode                 */
#define  GPIO_MODE_OUTPUT_OD                    0x00000011u   /*!< Output Open Drain Mode                */
#define  GPIO_MODE_AF_PP                        0x00000002u   /*!< Alternate Function Push Pull Mode     */
#define  GPIO_MODE_AF_OD                        0x00000012u   /*!< Alternate Function Open Drain Mode    */
#define  GPIO_MODE_AF_INPUT                     GPIO_MODE_INPUT          /*!< Alternate Function Input Mode         */


例子:
    HAL_GPIO_WritePin(LED1_GPIO_Port, LED1_Pin, GPIO_PIN_SET);
    
    /*Configure GPIO pin : LED1_Pin */
    GPIO_InitStruct.Pin = LED1_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(LED1_GPIO_Port, &GPIO_InitStruct);

API:

| 函数                       | 描述 |
|--------------------------|----|
| HAL_GPIO_Init            |    |
| HAL_GPIO_WritePin        |    |
| HAL_GPIO_ReadPin         |    |
| HAL_GPIO_TogglePin       |    |
| HAL_GPIO_LockPin         |    |
| HAL_GPIO_EXTI_IRQHandler |    |
| HAL_GPIO_EXTI_Callback   |    |

| 模式                 | 描述     |
|--------------------|--------|
| GPIO_MODE_INPUT    | 浮空输入   |
| GPIO_MODE_OUTPUT_PP | 推挽输出   |
| GPIO_MODE_OUTPUT_OD | 开漏输出   |
| GPIO_MODE_AF_PP    | 复用推挽输出 |
| GPIO_MODE_AF_OD    | 复用开漏输出 |
| GPIO_MODE_ANALOG | 模拟输入   |

| 上下拉           | 描述   |
|---------------|------|
| GPIO_NOPULL   | 不上下拉 |
| GPIO_PULLUP   | 上拉   |
| GPIO_PULLDOWN | 下拉   |

| 速度                     | 描述 |
|------------------------|----|
| GPIO_SPEED_FREQ_LOW    | 低速 |
| GPIO_SPEED_FREQ_MEDIUM | 中速 |
| GPIO_SPEED_FREQ_HIGH   | 高速 |

| 配置                     | 描述   |
|------------------------|------|
| GPIO_MODE_INPUT + GPIO_NOPULL    | 浮空输入 |
| GPIO_MODE_INPUT + GPIO_PULLUP | 上拉输入 |
| GPIO_MODE_INPUT + GPIO_PULLDOWN   | 下拉输入 |
| GPIO_MODE_ANALOG   | 模拟输入 |
| GPIO_MODE_OUTPUT_PP   | 推挽输出     |
| GPIO_MODE_OUTPUT_OD   | 开漏输出     |
| GPIO_MODE_AF_PP   | 复用推挽输出    |
| GPIO_MODE_AF_OD   | 复用开漏输出    |
