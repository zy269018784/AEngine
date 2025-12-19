1. 配置步骤
	1.1. 使能时钟
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_CAN1, ENABLE);
		
	1.2.  配置引脚为复用推挽输出
		为什么要复用推挽输出, 因为can和gpio A公用引脚.
   
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);   
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;		
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 	 
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;		//PA12	   
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 	
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	
		GPIO_Init(GPIOA, &GPIO_InitStructure);

	2. 寄存器
		CAN_MCR
		CAN_MSR
			RX: CAN接收电平
			SAMP: 上次采样值	
			RXM: 接收模式
			TXM: 发送模式
			SLAKI: 睡眠确认中断
			WKUI: 唤醒中断挂号
			ERRI: 出错中断挂号
			SLAK: 睡眠模式确认
			INAK: 初始化确认
		CAN_TSR
			TME[0-2]:   发送邮箱空
			LOW0[0-2]:  邮箱最低优先级标志
			ABRQ[0-2]:  邮箱中止发送
			TERR[0-2]:  邮箱发送失败
			TXOK[0-2]:  邮箱发送成功   
			ALST[0-2]:  邮箱仲裁丢失
			RQCP[0-2]:  邮箱请求完成   
		CAN_RF0R
		CAN_RF1R
		CAN_IER
			SLKIE：睡眠中断使能
			WKUIE: 唤醒中断使能
			ERRIE: 错误中断使能
			LECIE: 上次错误号中断使能
			BOFIE: 离线中断使能
			EPVIE: 错误被动中断使能
			EWGIE: 错误警告中断使能
			FOVIE1: FIFO 1溢出中断使能
			FFIE1: FIFO 1满中断使能
			FMPIE1: FIFO 1消息挂号中断使能
			FOVIE0: FIFO 0溢出中断使能
			FFIE0: FIFO 0满中断使能
			FMPIE0: FIFO 0消息挂号中断使能
			TMEIE: 发送邮箱空中断使能
		CAN_ESR
		CAN_BTR
			SILM: 静默模式
			LBKM: 环回模式
			TS1[3:0]: 时间段1
			TS2[3:0]: 时间段2
			BRP[9:0]: 波特率分频器
			SJW[1:0]: 重新同步跳跃宽度
		CAN_TIxR
		CAN_TDTxR
		CAN_TDLxR
		CAN_TDHxR
		CAN_RIxR
		CAN_RDTxR
		CAN_RDLxR
		CAN_RDHxR
		CAN_FMR
		CAN_FM1R
		CAN_FFA1R
		CAN_FA1R
		CAN_FiRx

		3. CAN邮箱
			3个发送邮箱和2个接受邮箱
			接收邮箱:
				3级深度FIFO
         
2. 
StdId
ExtId
IDE
RTR
DLC







