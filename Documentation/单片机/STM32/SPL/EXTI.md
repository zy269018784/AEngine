void EXTI_Init(EXTI_InitTypeDef* EXTI_InitStruct)
void EXTI_StructInit(EXTI_InitTypeDef* EXTI_InitStruct)
void EXTI_GenerateSWInterrupt(uint32_t EXTI_Line)
FlagStatus EXTI_GetFlagStatus(uint32_t EXTI_Line)
void EXTI_ClearFlag(uint32_t EXTI_Line)
ITStatus EXTI_GetITStatus(uint32_t EXTI_Line)
void EXTI_ClearITPendingBit(uint32_t EXTI_Line)
void GPIO_EXTILineConfig(uint8_t GPIO_PortSource, uint8_t GPIO_PinSource)

例子: 把GPIOA0, GPIOE2, GPIOE3, GPIOE4配置成外部中断
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource2);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource3);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource4);
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, GPIO_PinSource0);

    EXTI_InitTypeDef  EXTI_InitStructure;

	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line2 | EXTI_Line3 | EXTI_Line4; 
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_Init(&EXTI_InitStructure);