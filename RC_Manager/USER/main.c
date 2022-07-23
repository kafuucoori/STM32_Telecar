#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "lcd.h"
#include "usart.h"	 
#include "24cxx.h"
#include "w25qxx.h"
#include "touch.h"
#include "joypad.h" 
#include "remote.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
//���� A2 A3
/************************************************
 ALIENTEKս��STM32������ʵ��27
 ������ ʵ�� 
 ����֧�֣�www.openedv.com
 �Ա����̣�http://eboard.taobao.com 
 ��ע΢�Ź���ƽ̨΢�źţ�"����ԭ��"����ѻ�ȡSTM32���ϡ�
 ������������ӿƼ����޹�˾  
 ���ߣ�����ԭ�� @ALIENTEK
************************************************/
const u8* kbd_tbl1[6]={"1","2","3","4","5","6"};
const u8* kbd_tbl2[6]={"1","2","3","4","5","6"};
u8** kbd_tbl;
u8* kbd_fn_tbl[2];
u8 key_FC;
u8 key_RX;

void touch_load_keyboard(u16 x,u16 y,u8 **kbtbl)
{
	u16 i;
	POINT_COLOR=GREEN;
	kbd_tbl=kbtbl;
	LCD_Fill(x+100,y,x+400,y+300,BROWN); 
	LCD_Fill(x+100,y+400,x+200,y+500,BRRED); 
	LCD_Fill(x+300,y+400,x+400,y+500,BRRED); 
	LCD_Fill(x+100,y+300,x+200,y+400,GRED); 
	LCD_Fill(x+200,y+300,x+300,y+400,GRAY); 
	LCD_Fill(x+300,y+300,x+400,y+400,GRED); 
	LCD_DrawRectangle(x+100,y,x+200,y+100);
	LCD_DrawRectangle(x+100,y,x+300,y+100);
	LCD_DrawRectangle(x+100,y,x+400,y+100);
	LCD_DrawRectangle(x+100,y+100,x+200,y+200);
	LCD_DrawRectangle(x+100,y+100,x+300,y+200);
	LCD_DrawRectangle(x+100,y+100,x+400,y+200);
	LCD_DrawRectangle(x+100,y+200,x+200,y+300);
	LCD_DrawRectangle(x+100,y+200,x+300,y+300);
	LCD_DrawRectangle(x+100,y+200,x+400,y+300);
	POINT_COLOR=BLUE;
	for(i=0;i<14;i++)
	{
		if(i==0 )LCD_ShowChar(x+245,y+ 45,'M',24,80); 
		if(i==1 )LCD_ShowChar(x+145,y+145,'L',24,80);
		if(i==2 )LCD_ShowChar(x+245,y+145,'S',24,80);
		if(i==3 )LCD_ShowChar(x+345,y+145,'R',24,80); 		
		if(i==4 )LCD_ShowChar(x+245,y+245,'B',24,80); 
		if(i==5 )LCD_ShowChar(x+145,y+445,'<',24,80);
		if(i==6 )LCD_ShowChar(x+345,y+445,'>',24,80);
		if(i==7 )LCD_ShowChar(x+145,y+ 45,'U',24,80);
		if(i==8 )LCD_ShowChar(x+345,y+ 45,'D',24,80);
		if(i==9 )LCD_ShowChar(x+145,y+245,'Z',24,80);
		if(i==10)LCD_ShowChar(x+345,y+245,'Y',24,80);
		if(i==11)LCD_ShowString(130,y+345,200,16,16,"BEEP");//���
		if(i==12)LCD_ShowString(230,y+345,200,16,16,"FIRE");//���
		if(i==13)LCD_ShowString(330,y+345,200,16,16,"REDX");//���
	}  		 					   
}

//���ݴ���������
void Control(void)
{
	vu8 key=0;	
	int flag=0;
	float pitch,roll,yaw; 		//ŷ����
	u8 t=0;
	u8 i=0;	  	    
 	u16 lastpos[5][2];		//��¼���һ�ε����� 
	while(1)
	{		
		tp_dev.scan(0);
		
		key=KEY_Scan(0);	//�õ���ֵ
		
		if(key==KEY2_PRES)
		{
			flag++;
			
			if(flag==4)
			{
				flag=0;
			}		
		}	
		
		if(flag==0)//��Ļң��
		{
			LCD_ShowString(230,675,200,16,16,"MOD1");
		}
		if(flag==1)//�ֱ�ң��
		{
			LCD_ShowString(230,675,200,16,16,"MOD2");
		}
		if(flag==2)//����ң��
		{
			LCD_ShowString(230,675,200,16,16,"MOD3");
		}
		if(flag==3)//������ң��
		{
			LCD_ShowString(230,675,200,16,16,"MOD4");
		}
		
		for(t=0;t<CT_MAX_TOUCH;t++)
		{
			if((tp_dev.sta)&(1<<t))
			{
				if(tp_dev.x[t]<lcddev.width&&tp_dev.y[t]<lcddev.height)
				{
					if(lastpos[t][0]==0XFFFF)
					{
						lastpos[t][0] = tp_dev.x[t];
						lastpos[t][1] = tp_dev.y[t];
					}
					lastpos[t][0]=tp_dev.x[t];
					lastpos[t][1]=tp_dev.y[t];
					
					if(tp_dev.x[t]>200 && tp_dev.x[t]<300 && tp_dev.y[t]>500  && tp_dev.y[t]<600)
					{
						LCD_ShowString(230,645,200,16,16,"FIRE ");//���
						USART_SendData(USART2,'e');
					}
	
					if(tp_dev.x[t]>300 && tp_dev.x[t]<400 && tp_dev.y[t]>400  && tp_dev.y[t]<500)
					{
						LCD_ShowString(230,645,200,16,16," TR  ");//���
						USART_SendData(USART2,'d');
					}
					
					if(tp_dev.x[t]>100 && tp_dev.x[t]<200 && tp_dev.y[t]>400  && tp_dev.y[t]<500)
					{
						LCD_ShowString(230,645,200,16,16," TL  ");//���
						USART_SendData(USART2,'c');
					}
					
					if(tp_dev.x[t]>300 && tp_dev.x[t]<400 && tp_dev.y[t]>200  && tp_dev.y[t]<300)
					{
						LCD_ShowString(230,645,200,16,16,"DOWN ");//���
						USART_SendData(USART2,'b');
					}
					
					if(tp_dev.x[t]>100 && tp_dev.x[t]<200 && tp_dev.y[t]>200  && tp_dev.y[t]<300)
					{
						LCD_ShowString(230,645,200,16,16," UP  ");//���
						USART_SendData(USART2,'a');
					}
					
					if(tp_dev.x[t]>300 && tp_dev.x[t]<400 && tp_dev.y[t]>500  && tp_dev.y[t]<600)
					{
						LCD_ShowString(230,645,200,16,16,"REDX  ");//���
						USART_SendData(USART2,'9');
					}										
					
					if(tp_dev.x[t]>100 && tp_dev.x[t]<200 && tp_dev.y[t]>500  && tp_dev.y[t]<600)
					{
						LCD_ShowString(230,645,200,16,16,"BEEP  ");//���
						USART_SendData(USART2,'8');
					}					
					
					if(tp_dev.x[t]>200 && tp_dev.x[t]<300 && tp_dev.y[t]>300  && tp_dev.y[t]<400)
					{
						LCD_ShowString(230,645,200,16,16,"STOP  ");//���
						USART_SendData(USART2,'7');
					}
					
					if(tp_dev.x[t]>100 && tp_dev.x[t]<200 && tp_dev.y[t]>600  && tp_dev.y[t]<700)
					{
						LCD_ShowString(230,645,200,16,16," LM  ");//���
						USART_SendData(USART2,'6');
					}			
					
					if(tp_dev.x[t]>300 && tp_dev.x[t]<400 && tp_dev.y[t]>600  && tp_dev.y[t]<700)
					{
						LCD_ShowString(230,645,200,16,16," RM  ");//���
						USART_SendData(USART2,'5');
					}
					
					if(tp_dev.x[t]>200 && tp_dev.x[t]<300 && tp_dev.y[t]>200  && tp_dev.y[t]<300)
					{
						LCD_ShowString(230,645,200,16,16,"MOVE  ");//���
						USART_SendData(USART2,'4');
					}
					if(tp_dev.x[t]>100 && tp_dev.x[t]<200 && tp_dev.y[t]>300 && tp_dev.y[t]<400)
					{
						LCD_ShowString(230,645,200,16,16,"LEFT  ");//���
						USART_SendData(USART2,'3');
					}
					if(tp_dev.x[t]>300 && tp_dev.x[t]<400 && tp_dev.y[t]>300 && tp_dev.y[t]<400)
					{
						LCD_ShowString(230,645,200,16,16,"RIGHT");//���
						USART_SendData(USART2,'2');
					}
					if(tp_dev.x[t]>200 && tp_dev.x[t]<300 && tp_dev.y[t]>400 && tp_dev.y[t]<500)
					{
						LCD_ShowString(230,645,200,16,16,"BACK  ");//���
						USART_SendData(USART2,'1');
					}
				}
			}else lastpos[t][0]=0XFFFF;
		}		
		delay_ms(5);i++;

		if(flag==1)
		{
			//FC�ֱ�����
			key_FC=JOYPAD_Read();
			
			if(key_FC==16)	//move
			{
				USART_SendData(USART2,'4');
				LCD_ShowString(230,645,200,16,16,"MOVE  ");//���				
			}
			if(key_FC==64)	//left
			{
				USART_SendData(USART2,'3');
				LCD_ShowString(230,645,200,16,16,"LEFT  ");//���
			}
			if(key_FC==128)//right
			{
				USART_SendData(USART2,'2');
				LCD_ShowString(230,645,200,16,16,"RIGHT");//���
			}
			if(key_FC==32)	//back
			{
				USART_SendData(USART2,'1');
				LCD_ShowString(230,645,200,16,16,"BACK  ");//���
			}	
			if(key_FC==2)	//up
			{
				LCD_ShowString(230,645,200,16,16," UP  ");//���
				USART_SendData(USART2,'a');
			}
			if(key_FC==1)	//down
			{
				LCD_ShowString(230,645,200,16,16,"DOWN ");//���
				USART_SendData(USART2,'b');
			}	
		}

		if(flag==2)
		{
			//�������
			key_RX=Remote_Scan();
		
			if(key_RX==98)	//move
			{
				USART_SendData(USART2,'4');	
				LCD_ShowString(230,645,200,16,16,"MOVE  ");//���
			}
			if(key_RX==34)	//left
			{
				USART_SendData(USART2,'3');
				LCD_ShowString(230,645,200,16,16,"LEFT  ");//���
			}
			if(key_RX==194)//right
			{
				USART_SendData(USART2,'2');
				LCD_ShowString(230,645,200,16,16,"RIGHT");//���
			}
			if(key_RX==168)	//back
			{
				USART_SendData(USART2,'1');
				LCD_ShowString(230,645,200,16,16,"BACK  ");//���
			}	
			if(key_RX==152)	//up
			{
				LCD_ShowString(230,645,200,16,16," UP  ");//���
				USART_SendData(USART2,'a');
			}
			if(key_RX==56)	//down
			{
				LCD_ShowString(230,645,200,16,16,"DOWN ");//���
				USART_SendData(USART2,'b');
			}
			if(key_RX==48)	//TL
			{
				LCD_ShowString(230,645,200,16,16," TL  ");//���
				USART_SendData(USART2,'c');
			}
			if(key_RX==122)	//TR
			{
				LCD_ShowString(230,645,200,16,16," TR  ");//���
				USART_SendData(USART2,'d');
			}
			if(key_RX==24)	//stop
			{
				LCD_ShowString(230,645,200,16,16,"STOP  ");//���
				USART_SendData(USART2,'7');
			}
		}

		if(flag==3)
		{			
			//�����ǿ���
			mpu_dmp_get_data(&pitch,&roll,&yaw);
			
			if(pitch>=20)
			{
				LCD_ShowString(230,645,200,16,16,"MOVE  ");//���
				USART_SendData(USART2,'4');
			}
			if(pitch<=-20)
			{
				LCD_ShowString(230,645,200,16,16,"BACK  ");//���
				USART_SendData(USART2,'1');			
			}
			if(roll<=-20)
			{
				LCD_ShowString(230,645,200,16,16,"LEFT  ");//���
				USART_SendData(USART2,'3');			
			}
			if(roll>=20)
			{
				LCD_ShowString(230,645,200,16,16,"RIGHT");//���
				USART_SendData(USART2,'2');			
			}
			if(pitch>=-20 && pitch<=20 && roll>=-20 && roll<=20)
			{
				LCD_ShowString(230,645,200,16,16,"STOP  ");//���
				USART_SendData(USART2,'7');
			}
		}
	}	
}

void USART2_Configuration(void)
{

	USART_InitTypeDef USART_InitStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	SystemInit(); 
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

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
		
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	            //ֻ���޸�һ��
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	   	//�����ж� 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //��ռ���ȼ�0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //�����ȼ�Ϊ0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//ʹ��
	NVIC_Init(&NVIC_InitStructure);		
}

 int main(void)
 {	 
	int k=0;
	 
	vu8 KEY=0;
	 
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//�����ж����ȼ�����Ϊ��2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(115200);	 	//���ڳ�ʼ��Ϊ115200
	 
 	LED_Init();			     //LED�˿ڳ�ʼ��
	LCD_Init();	
	KEY_Init();	
	MPU_Init();		//��ʼ��MPU6050			 
	JOYPAD_Init();			//�ֱ���ʼ��	 
	Remote_Init();			//������ճ�ʼ��	
	 
 	tp_dev.init();
	USART2_Configuration();
	 	 
	while(1)
	{
		POINT_COLOR=RED;//��������Ϊ��ɫ 
		LCD_ShowString(145,225,200,16,16,"MPU6050 AND JOYPAD");//���
		LCD_ShowString(145,245,200,16,16,"CANNOT BE USED TOGETHER");//���
		LCD_ShowString(145,265,200,16,16,"KEY0 JOYPAD");//���	
		LCD_ShowString(145,285,200,16,16,"KEY1 MUP");//���	
		LCD_ShowString(145,305,200,16,16,"MOD1 screen control");//���	
		LCD_ShowString(145,325,200,16,16,"MOD2 joypad control");//���	
		LCD_ShowString(145,345,200,16,16,"MOD3 infrared control");//���
		LCD_ShowString(145,365,200,16,16,"MOD4 mpu6050 control");//���
		LCD_ShowString(145,385,200,16,16,"MPU GBC-PB10PB11");//���
		LCD_ShowString(145,405,200,16,16,"JOYPAD COM3-PB10PB11");//���
		LCD_ShowString(145,425,200,16,16,"USE KEY2 TO CHANGE MODS");//���
		
		KEY=KEY_Scan(0);	//�õ���ֵ
		
		if(KEY==KEY0_PRES)
		{
			LCD_Clear(WHITE);
			touch_load_keyboard(0,200,(u8**)kbd_tbl1); 
			POINT_COLOR=RED;//��������Ϊ��ɫ 
			Control();	//����������
		}			
			
		if(KEY==KEY1_PRES)
		{
			LCD_Clear(WHITE);
			touch_load_keyboard(0,200,(u8**)kbd_tbl1); 
			POINT_COLOR=RED;//��������Ϊ��ɫ 			
			
			while(mpu_dmp_init())
			{
				LCD_ShowString(215,645,200,16,16,"MPU ERROR");//���	
				k++;
				delay_ms(500);
				if(k==10)
				{
					break;	
				}	
			} 
			LCD_ShowString(215,645,200,16,16,"         ");//���
			Control();	//����������	
		}			
	}
}
