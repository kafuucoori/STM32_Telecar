#include<includes.h>
/*********************************************************************************************************
*                                          ȫ�ֱ���
*********************************************************************************************************/

/*********************************************************************************************************
*                                          ��������
*********************************************************************************************************/

void RCC_Configuration(void);	/* ��ʼ��ϵͳʱ�� */
void GPIO_Configuration(void);	/* IO�ڵ�����*/
void USART1_Configuration(void);	/* �������� */
void USART2_Configuration(void);	/* �������� */
void TIM3_Configuration1(u16 arr,u16 psc);	/* PWM���� */
void TIM3_Configuration2(u16 arr,u16 psc);	/* PWM���� */
void TIM3_Configuration3(u16 arr,u16 psc);	/* PWM���� */
void TIM3_Configuration4(u16 arr,u16 psc);	/* PWM���� */
void TIM4_Configuration1(u16 arr,u16 psc);
void TIM4_Configuration2(u16 arr,u16 psc);
void NVIC_Configuration(void);	/* ���ȼ����� */

void  BSP_Init (void)
{
	RCC_Configuration();	/* ��ʼ��ϵͳʱ�� */
	GPIO_Configuration();	/* IO������ */
	USART1_Configuration();	/* ���� */
	USART2_Configuration();	/* ���� */
	NVIC_Configuration();	/* ���ȼ� */
}
/*********************************************************************************************************
* ��    �� ��RCC_Configuration
* �������� : ��ʼ��ϵͳʱ��
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void RCC_Configuration(void)
{
	SystemInit(); 

	/*APB1 36MHz ����timerʱ�ᱶƵΪ72mhz����������Щ�ڴ�ʱ���Ͽ�����ȥ�鿴*/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 |RCC_APB1Periph_USART2, ENABLE);
	
	/*APB2 72MHz ����timerʱ�ᱶƵΪ144mhz����������Щ�ڴ�ʱ���Ͽ�����ȥ�鿴*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC
						| RCC_APB2Periph_AFIO| RCC_APB2Periph_USART1,ENABLE );
}

/*********************************************************************************************************
* ��    �� ��GPIO_Configuration
* �������� : ��ʼ��IO������
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
******************* **************************************************************************************/ 
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	    /* LED�Ƶ����� */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //ͨ���������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;			 //ͨ���������ģʽ
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;			 //���ģʽ����ٶ�50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOA, GPIO_Pin_11 | GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_11 | GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOC, GPIO_Pin_11 | GPIO_Pin_12);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_12 | GPIO_Pin_13);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;               //���
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_ResetBits(GPIOB, GPIO_Pin_14 | GPIO_Pin_15);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //BEEP-->PB.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
	GPIO_Init(GPIOA, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB.8
	GPIO_SetBits(GPIOA,GPIO_Pin_0);//���0���رշ��������
}
/*********************************************************************************************************
* ��    �� ��USART1_Configuration
* �������� : ��ʼ������1
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void USART1_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Configure USART1 Rx (PA.10) as input floating */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //��������ģʽ	   
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  //�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;						//����115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//����λ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//ֹͣλ1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;				//��У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//�շ�ģʽ
	/* Configure USART1 */
	
	USART_Init(USART1, &USART_InitStructure);							//���ô��ڲ�������
	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);                    //ʹ�ܽ����ж�
	/* Enable the USART1 */
	USART_Cmd(USART1, ENABLE);	                  //ʹ�ܴ���
}

/*********************************************************************************************************
* ��    �� ��USART2_Configuration
* �������� : ��ʼ������2
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void USART2_Configuration(void)
{
	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	/* Configure USART1 Rx (PA.10) as input floating */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;		  //��������ģʽ	   
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	/* Configure USART1 Tx (PA.09) as alternate function push-pull */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;			  //�����������
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate = 9600;						//����115200bps
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;		//����λ8λ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;			//ֹͣλ1λ
	USART_InitStructure.USART_Parity = USART_Parity_No;				//��У��λ
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;   //��Ӳ������
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;					//�շ�ģʽ
	/* Configure USART1 */
	
	USART_Init(USART2, &USART_InitStructure);							//���ô��ڲ�������
	/* Enable USART1 Receive and Transmit interrupts */
	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);                    //ʹ�ܽ����ж�
	/* Enable the USART1 */
	USART_Cmd(USART2, ENABLE);	                  //ʹ�ܴ���
}

/*********************************************************************************************************
* ��    �� ��TIM3_Configuration
* �������� : ��ʼ����ʱ��  PWM
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void TIM3_Configuration1(u16 arr,u16 psc)		//��������������ʱ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//��Ƶ	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//ʱ�ӷָ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//����Ϊ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// ��ʼֵ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwmģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ��ͨ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//�ߵ�ƽ
	
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);	                  
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);			//ʹ�ܻ���ʧ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* �ж�ʹ�� */
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);	/* ʹ�� */
	
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

void TIM3_Configuration2(u16 arr,u16 psc)		//��������������ʱ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//��Ƶ	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//ʱ�ӷָ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//����Ϊ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// ��ʼֵ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwmģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ��ͨ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//�ߵ�ƽ
	
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);	                  
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);			//ʹ�ܻ���ʧ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* �ж�ʹ�� */
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);	/* ʹ�� */
	
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

void TIM3_Configuration3(u16 arr,u16 psc)		//��������������ʱ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//��Ƶ	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//ʱ�ӷָ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//����Ϊ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// ��ʼֵ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwmģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ��ͨ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//�ߵ�ƽ
	
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);	                  
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);			//ʹ�ܻ���ʧ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* �ж�ʹ�� */
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);	/* ʹ�� */
	
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);
}

void TIM3_Configuration4(u16 arr,u16 psc)		//��������������ʱ��
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//��Ƶ	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//ʱ�ӷָ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//����Ϊ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// ��ʼֵ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwmģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ��ͨ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//�ߵ�ƽ
	
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);	                  
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);			//ʹ�ܻ���ʧ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* �ж�ʹ�� */
	/* TIM3 enable counter */
	TIM_Cmd(TIM3, ENABLE);	/* ʹ�� */
	
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);
}
/*******************************************************************************
* Function Name  : TIM4_Configuration
* Description    : ��ʱ��
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
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//��Ƶ	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//ʱ�ӷָ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//����Ϊ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// ��ʼֵ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwmģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ��ͨ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//�ߵ�ƽ
	
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);	                  
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);			//ʹ�ܻ���ʧ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* �ж�ʹ�� */
	/* TIM3 enable counter */
	TIM_Cmd(TIM4, ENABLE);	/* ʹ�� */
	
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);
}

void TIM4_Configuration2(u16 arr,u16 psc)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;	                   
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;		 //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	        	
	/* Time base configuration */
	TIM_TimeBaseStructure.TIM_Period = arr;					//arr  ��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ
	TIM_TimeBaseStructure.TIM_Prescaler = psc;	 			 	//��Ƶ	psc
	TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CounterMode_Up;		//ʱ�ӷָ���ϼ���ģʽ
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;	 	//����Ϊ���ϼ���ģʽ
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);

	/* PWM1 Mode configuration: Channel1*/
//	TIM_OCInitStructure.TIM_Pulse = 5000;						// ��ʼֵ
	
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;			   //pwmģʽ2
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;	//ʹ��ͨ��
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;	//�ߵ�ƽ
	
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);	                  
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);			//ʹ�ܻ���ʧ��TIMx��CCR3�ϵ�Ԥװ�ؼĴ���

	
//	TIM_ARRPreloadConfig(TIM3, ENABLE);  /* �ж�ʹ�� */
	/* TIM3 enable counter */
	TIM_Cmd(TIM4, ENABLE);	/* ʹ�� */
	
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);
}
/*********************************************************************************************************
* ��    �� ��NVIC_Configuration
* �������� : ��ʼ���ж����ȼ�
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
*********************************************************************************************************/
void NVIC_Configuration(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	            //ֻ���޸�һ��
	
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;	   	//�����ж� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //�����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ��
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	   	//�����ж� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //�����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ��
	NVIC_Init(&NVIC_InitStructure);

}










