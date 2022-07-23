#include<includes.h>
/*********************************************************************************************************
*                                          全局变量
*********************************************************************************************************/

/*********************************************************************************************************
*                                          函数声明
*********************************************************************************************************/

void RCC_Configuration(void);	/* 初始化系统时钟 */
void GPIO_Configuration(void);	/* IO口的配置*/
void USART1_Configuration(void);	/* 串口配置 */
void USART2_Configuration(void);	/* 串口配置 */
void TIM3_Configuration1(u16 arr,u16 psc);	/* PWM配置 */
void TIM3_Configuration2(u16 arr,u16 psc);	/* PWM配置 */
void TIM3_Configuration3(u16 arr,u16 psc);	/* PWM配置 */
void TIM3_Configuration4(u16 arr,u16 psc);	/* PWM配置 */
void TIM4_Configuration1(u16 arr,u16 psc);
void TIM4_Configuration2(u16 arr,u16 psc);
void NVIC_Configuration(void);	/* 优先级配置 */

void  BSP_Init (void)
{
	RCC_Configuration();	/* 初始化系统时钟 */
	GPIO_Configuration();	/* IO口配置 */
	USART1_Configuration();	/* 串口 */
	USART2_Configuration();	/* 串口 */
	NVIC_Configuration();	/* 优先级 */
}
/*********************************************************************************************************
* 名    称 ：RCC_Configuration
* 功能描述 : 初始化系统时钟
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void RCC_Configuration(void)
{
	SystemInit(); 

	/*APB1 36MHz 配置timer时会倍频为72mhz，具体有哪些在此时钟上可跳进去查看*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 |RCC_APB1Periph_USART2, ENABLE);
	
	/*APB2 72MHz 配置timer时会倍频为144mhz，具体有哪些在此时钟上可跳进去查看*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC
						| RCC_APB2Periph_AFIO| RCC_APB2Periph_USART1,ENABLE );
}

/*********************************************************************************************************
* 名    称 ：GPIO_Configuration
* 功能描述 : 初始化IO口配置
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
******************* **************************************************************************************/ 
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	    /* LED灯的配置 */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //通用推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //通用推挽输出模式
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //输出模式最大速度50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //电机
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //电机
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC, GPIO_Pin_11 | GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //电机
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //电机
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //BEEP-->PB.8 端口配置
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //速度为50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	 //根据参数初始化GPIOB.8
	GPIO_SetBits(GPIOA,GPIO_Pin_0);//输出0，关闭蜂鸣器输出
}
/*********************************************************************************************************
* 名    称 ：USART1_Configuration
* 功能描述 : 初始化串口1
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void USART1_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Configure USART1 Rx (PA.10) as input floating */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //浮空输入模式	   
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  //复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;						//速率115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//收发模式
	/* Configure USART1 */
	
	USART_Init(USART1, &USART_InitStructure);							//配置串口参数函数
	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                    //使能接收中断
	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);	                  //使能串口
}

/*********************************************************************************************************
* 名    称 ：USART2_Configuration
* 功能描述 : 初始化串口2
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void USART2_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Configure USART1 Rx (PA.10) as input floating */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //浮空输入模式	   
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  //复用推挽输出
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;						//速率115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//数据位8位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//停止位1位
	USART_InitStructure.USART_Parity = USART_Parity_No;				//无校验位
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //无硬件流控
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//收发模式
	/* Configure USART1 */
	
	USART_Init(USART2, &USART_InitStructure);							//配置串口参数函数
	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                    //使能接收中断
	/* Enable the USART1 */
	USART_Cmd(USART2, ENABLE);	                  //使能串口
}

/*********************************************************************************************************
* 名    称 ：TIM3_Configuration
* 功能描述 : 初始化定时器  PWM
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void TIM3_Configuration1(u16 arr,u16 psc)		//计数次数，计数时间
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//分频	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//时钟分割，向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//设置为向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// 初始值
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwm模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能通道
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//高电平
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	                  
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);			//使能或者失能TIMx在CCR3上的预装载寄存器

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* 中断使能 */
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);	/* 使能 */
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

void TIM3_Configuration2(u16 arr,u16 psc)		//计数次数，计数时间
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//分频	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//时钟分割，向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//设置为向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// 初始值
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwm模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能通道
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//高电平
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	                  
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);			//使能或者失能TIMx在CCR3上的预装载寄存器

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* 中断使能 */
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);	/* 使能 */
	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

void TIM3_Configuration3(u16 arr,u16 psc)		//计数次数，计数时间
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//分频	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//时钟分割，向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//设置为向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// 初始值
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwm模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能通道
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//高电平
	
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);	                  
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);			//使能或者失能TIMx在CCR3上的预装载寄存器

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* 中断使能 */
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);	/* 使能 */
	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

void TIM3_Configuration4(u16 arr,u16 psc)		//计数次数，计数时间
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//分频	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//时钟分割，向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//设置为向上计数模式
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// 初始值
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwm模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能通道
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//高电平
	
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	                  
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);			//使能或者失能TIMx在CCR3上的预装载寄存器

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* 中断使能 */
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);	/* 使能 */
	
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
/*******************************************************************************
* Function Name  : TIM4_Configuration
* Description    : 定时器
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM4_Configuration1(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//分频	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//时钟分割，向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//设置为向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// 初始值
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwm模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能通道
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//高电平
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);	                  
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);			//使能或者失能TIMx在CCR3上的预装载寄存器

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* 中断使能 */
	/* TIM3 enable counter */
	TIM_Cmd(TIM4, ENABLE);	/* 使能 */
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

void TIM4_Configuration2(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //复用推挽输出
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  设置在下一个更新事件装入活动的自动重装载寄存器周期的值
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//分频	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//时钟分割，向上计数模式
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//设置为向上计数模式
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// 初始值
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwm模式2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//使能通道
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//高电平
	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);	                  
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);			//使能或者失能TIMx在CCR3上的预装载寄存器

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* 中断使能 */
	/* TIM3 enable counter */
	TIM_Cmd(TIM4, ENABLE);	/* 使能 */
	
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
}
/*********************************************************************************************************
* 名    称 ：NVIC_Configuration
* 功能描述 : 初始化中断优先级
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	            //只需修改一次
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	   	//串口中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //子优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	   	//串口中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //子优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能
	NVIC_Init(&NVIC_InitStructure);

}










