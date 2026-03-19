HAL_StatusTypeDef HAL_EXTI_SetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig)
HAL_StatusTypeDef HAL_EXTI_GetConfigLine(EXTI_HandleTypeDef *hexti, EXTI_ConfigTypeDef *pExtiConfig)
HAL_StatusTypeDef HAL_EXTI_ClearConfigLine(EXTI_HandleTypeDef *hexti)
HAL_StatusTypeDef HAL_EXTI_RegisterCallback(EXTI_HandleTypeDef *hexti, EXTI_CallbackIDTypeDef CallbackID, void (*pPendingCbfn)(void))
HAL_StatusTypeDef HAL_EXTI_GetHandle(EXTI_HandleTypeDef *hexti, uint32_t ExtiLine)
void HAL_EXTI_IRQHandler(EXTI_HandleTypeDef *hexti)
uint32_t HAL_EXTI_GetPending(EXTI_HandleTypeDef *hexti, uint32_t Edge)
void HAL_EXTI_ClearPending(EXTI_HandleTypeDef *hexti, uint32_t Edge)
void HAL_EXTI_GenerateSWI(EXTI_HandleTypeDef *hexti)

typedef struct
{
    uint32_t Line;      /*!< The Exti line to be configured. This parameter can be a value of @ref EXTI_Line */
    uint32_t Mode;      /*!< The Exit Mode to be configured for a core. This parameter can be a combination of @ref EXTI_Mode */
    uint32_t Trigger;   /*!< The Exti Trigger to be configured. This parameter can be a value of @ref EXTI_Trigger */
    uint32_t GPIOSel;   /*!< The Exti GPIO multiplexer selection to be configured. This parameter is only possible for line 0 to 15. It can be a value of @ref EXTI_GPIOSel */
} EXTI_ConfigTypeDef;

#define EXTI_LINE_0                        (EXTI_GPIO     | 0x00u)    /*!< External interrupt line 0 */
#define EXTI_LINE_1                        (EXTI_GPIO     | 0x01u)    /*!< External interrupt line 1 */
#define EXTI_LINE_2                        (EXTI_GPIO     | 0x02u)    /*!< External interrupt line 2 */
#define EXTI_LINE_3                        (EXTI_GPIO     | 0x03u)    /*!< External interrupt line 3 */
#define EXTI_LINE_4                        (EXTI_GPIO     | 0x04u)    /*!< External interrupt line 4 */
#define EXTI_LINE_5                        (EXTI_GPIO     | 0x05u)    /*!< External interrupt line 5 */
#define EXTI_LINE_6                        (EXTI_GPIO     | 0x06u)    /*!< External interrupt line 6 */
#define EXTI_LINE_7                        (EXTI_GPIO     | 0x07u)    /*!< External interrupt line 7 */
#define EXTI_LINE_8                        (EXTI_GPIO     | 0x08u)    /*!< External interrupt line 8 */
#define EXTI_LINE_9                        (EXTI_GPIO     | 0x09u)    /*!< External interrupt line 9 */
#define EXTI_LINE_10                       (EXTI_GPIO     | 0x0Au)    /*!< External interrupt line 10 */
#define EXTI_LINE_11                       (EXTI_GPIO     | 0x0Bu)    /*!< External interrupt line 11 */
#define EXTI_LINE_12                       (EXTI_GPIO     | 0x0Cu)    /*!< External interrupt line 12 */
#define EXTI_LINE_13                       (EXTI_GPIO     | 0x0Du)    /*!< External interrupt line 13 */
#define EXTI_LINE_14                       (EXTI_GPIO     | 0x0Eu)    /*!< External interrupt line 14 */
#define EXTI_LINE_15                       (EXTI_GPIO     | 0x0Fu)    /*!< External interrupt line 15 */
#define EXTI_LINE_16                       (EXTI_CONFIG   | 0x10u)    /*!< External interrupt line 16 Connected to the PVD Output */
#define EXTI_LINE_17                       (EXTI_CONFIG   | 0x11u)    /*!< External interrupt line 17 Connected to the RTC Alarm event */


#define EXTI_TRIGGER_NONE                   0x00000000u
#define EXTI_TRIGGER_RISING                 0x00000001u
#define EXTI_TRIGGER_FALLING                0x00000002u
#define EXTI_TRIGGER_RISING_FALLING         (EXTI_TRIGGER_RISING | EXTI_TRIGGER_FALLING)

#define EXTI_MODE_NONE                      0x00000000u
#define EXTI_MODE_INTERRUPT                 0x00000001u
#define EXTI_MODE_EVENT                     0x00000002u

例子: 把GPIOA0, GPIOE2, GPIOE3, GPIOE4配置成外部中断
    EXTI_ConfigTypeDef EXTI_InitStructure;
    EXTI_InitStructure.Line         = EXTI_LINE_0;
    EXTI_InitStructure.Mode         = EXTI_MODE_INTERRUPT;
    EXTI_InitStructure.Trigger      = EXTI_TRIGGER_RISING;
    EXTI_InitStructure.GPIOSel      = EXTI_GPIOA;
    HAL_EXTI_SetConfigLine(&, &EXTI_InitStructure);

    EXTI_InitStructure.Line         = EXTI_LINE_2 | EXTI_LINE_3 | EXTI_LINE_4;
    EXTI_InitStructure.Mode         = EXTI_MODE_INTERRUPT;
    EXTI_InitStructure.Trigger      = EXTI_TRIGGER_FALLING;
    EXTI_InitStructure.GPIOSel      = EXTI_GPIOE;
   HAL_EXTI_SetConfigLine(&, &EXTI_InitStructure);

    EXTI_InitStructure.Line         = EXTI_LINE_2;
    EXTI_InitStructure.Mode         = EXTI_MODE_INTERRUPT;
    EXTI_InitStructure.Trigger      = EXTI_TRIGGER_FALLING;
    EXTI_InitStructure.GPIOSel      = EXTI_GPIOE;
    HAL_EXTI_SetConfigLine(&, &EXTI_InitStructure);

    EXTI_InitStructure.Line         = EXTI_LINE_3;
    EXTI_InitStructure.Mode         = EXTI_MODE_INTERRUPT;
    EXTI_InitStructure.Trigger      = EXTI_TRIGGER_FALLING;
    EXTI_InitStructure.GPIOSel      = EXTI_GPIOE;
    HAL_EXTI_SetConfigLine(&, &EXTI_InitStructure);

    EXTI_InitStructure.Line         = EXTI_LINE_4;
    EXTI_InitStructure.Mode         = EXTI_MODE_INTERRUPT;
    EXTI_InitStructure.Trigger      = EXTI_TRIGGER_FALLING;
    EXTI_InitStructure.GPIOSel      = EXTI_GPIOE;
    HAL_EXTI_SetConfigLine(&, &EXTI_InitStructure);