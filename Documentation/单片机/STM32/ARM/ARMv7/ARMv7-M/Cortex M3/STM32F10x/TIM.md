TIM1 和TIM8 重复计数寄存器(TIMx_RCR)
TIM1 和TIM8 刹车和死区寄存器(TIMx_BDTR)

控制寄存器 1(TIMx_CR1)
控制寄存器 2(TIMx_CR2)
从模式控制寄存器(TIMx_SMCR)
DMA/中断使能寄存器(TIMx_DIER)
状态寄存器(TIMx_SR)
事件产生寄存器(TIMx_EGR)
捕获/比较模式寄存器 1(TIMx_CCMR1)
捕获/比较模式寄存器 2(TIMx_CCMR2)
捕获/比较使能寄存器(TIMx_CCER)
计数器(TIMx_CNT)
预分频器(TIMx_PSC)
自动重装载寄存器(TIMx_ARR)
捕获/比较寄存器 1(TIMx_CCR1)
捕获/比较寄存器 2(TIMx_CCR2)
捕获/比较寄存器 3(TIMx_CCR3)
捕获/比较寄存器 4(TIMx_CCR4)
DMA控制寄存器(TIMx_DCR)
连续模式的DMA地址(TIMx_DMAR)

Core:
	时钟分频因子 (Clock division)
	计时模式(Counter Mode）            计数器向上计数/计数器向下计数
	自动重装载的值 (Prescaler value)
	预分频器的值 (Prescaler value)
	重复计数器的值 (Repetition counter value)
	
SPL API:
	TIM_DeInit
	TIM_TimeBaseInit
	TIM_OC1Init
	TIM_OC2Init
	TIM_OC3Init
	TIM_OC4Init
	TIM_ICInit
	TIM_PWMIConfig
	TIM_BDTRConfig	
	TIM_TimeBaseStructInit
	TIM_OCStructInit
	TIM_ICStructInit
	TIM_BDTRStructInit
	TIM_Cmd
	TIM_CtrlPWMOutputs
	TIM_ITConfig
	TIM_GenerateEvent
	TIM_DMAConfig
	TIM_DMACmd
	TIM_InternalClockConfig
	TIM_ITRxExternalClockConfig
	TIM_TIxExternalClockConfig
	TIM_ETRClockMode1Config
	TIM_ETRClockMode2Config
	TIM_ETRConfig
	TIM_PrescalerConfig
	TIM_CounterModeConfig	
	TIM_SelectInputTrigger
	TIM_EncoderInterfaceConfig
	TIM_ForcedOC1Config
	TIM_ForcedOC2Config
	TIM_ForcedOC3Config
	TIM_ForcedOC4Config
	TIM_ARRPreloadConfig
	TIM_SelectCOM
	TIM_SelectCCDMA
	TIM_CCPreloadControl
	TIM_OC1PreloadConfig
	TIM_OC2PreloadConfig
	TIM_OC3PreloadConfig
	TIM_OC4PreloadConfig
	TIM_OC1FastConfig
	TIM_OC2FastConfig
	TIM_OC3FastConfig
	TIM_OC4FastConfig
	TIM_ClearOC1Ref
	TIM_ClearOC2Ref
	TIM_ClearOC3Ref
	TIM_ClearOC4Ref
	TIM_OC1PolarityConfig
	TIM_OC2PolarityConfig
	TIM_OC3PolarityConfig
	TIM_OC4PolarityConfig
	TIM_OC1NPolarityConfig
	TIM_OC2NPolarityConfig
	TIM_OC3NPolarityConfig
	TIM_CCxCmd
	TIM_CCxNCmd
	TIM_SelectOCxM
	TIM_UpdateDisableConfig
	TIM_UpdateRequestConfig
	TIM_SelectHallSensor
	TIM_SelectOnePulseMode
	TIM_SelectOutputTrigger
	TIM_SelectSlaveMode
	TIM_SelectMasterSlaveMode
	TIM_SetCounter
	TIM_SetAutoreload
	TIM_SetCompare1
	TIM_SetCompare2
	TIM_SetCompare3
	TIM_SetCompare4
	TIM_SetIC1Prescaler
	TIM_SetIC2Prescaler
	TIM_SetIC3Prescaler
	TIM_SetIC4Prescaler
	TIM_SetClockDivision
	TIM_GetCapture1
	TIM_GetCapture2
	TIM_GetCapture3
	TIM_GetCapture4
	TIM_GetCounter
	TIM_GetPrescaler
	TIM_GetFlagStatus
	TIM_ClearFlag
	TIM_GetITStatus
	TIM_ClearITPendingBit
	TI1_Config
	TI2_Config
	TI3_Config
	TI4_Config
	
	
	
	
	
	
	
	
	