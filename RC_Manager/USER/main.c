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
//蓝牙 A2 A3
/************************************************
 ALIENTEK战舰STM32开发板实验27
 触摸屏 实验 
 技术支持：www.openedv.com
 淘宝店铺：http://eboard.taobao.com 
 关注微信公众平台微信号："正点原子"，免费获取STM32资料。
 广州市星翼电子科技有限公司  
 作者：正点原子 @ALIENTEK
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
		if(i==11)LCD_ShowString(130,y+345,200,16,16,"BEEP");//清除
		if(i==12)LCD_ShowString(230,y+345,200,16,16,"FIRE");//清除
		if(i==13)LCD_ShowString(330,y+345,200,16,16,"REDX");//清除
	}  		 					   
}

//电容触摸屏控制
void Control(void)
{
	vu8 key=0;	
	int flag=0;
	float pitch,roll,yaw; 		//欧拉角
	u8 t=0;
	u8 i=0;	  	    
 	u16 lastpos[5][2];		//记录最后一次的数据 
	while(1)
	{		
		tp_dev.scan(0);
		
		key=KEY_Scan(0);	//得到键值
		
		if(key==KEY2_PRES)
		{
			flag++;
			
			if(flag==4)
			{
				flag=0;
			}		
		}	
		
		if(flag==0)//屏幕遥控
		{
			LCD_ShowString(230,675,200,16,16,"MOD1");
		}
		if(flag==1)//手柄遥控
		{
			LCD_ShowString(230,675,200,16,16,"MOD2");
		}
		if(flag==2)//红外遥控
		{
			LCD_ShowString(230,675,200,16,16,"MOD3");
		}
		if(flag==3)//陀螺仪遥控
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
						LCD_ShowString(230,645,200,16,16,"FIRE ");//清除
						USART_SendData(USART2,'e');
					}
	
					if(tp_dev.x[t]>300 && tp_dev.x[t]<400 && tp_dev.y[t]>400  && tp_dev.y[t]<500)
					{
						LCD_ShowString(230,645,200,16,16," TR  ");//清除
						USART_SendData(USART2,'d');
					}
					
					if(tp_dev.x[t]>100 && tp_dev.x[t]<200 && tp_dev.y[t]>400  && tp_dev.y[t]<500)
					{
						LCD_ShowString(230,645,200,16,16," TL  ");//清除
						USART_SendData(USART2,'c');
					}
					
					if(tp_dev.x[t]>300 && tp_dev.x[t]<400 && tp_dev.y[t]>200  && tp_dev.y[t]<300)
					{
						LCD_ShowString(230,645,200,16,16,"DOWN ");//清除
						USART_SendData(USART2,'b');
					}
					
					if(tp_dev.x[t]>100 && tp_dev.x[t]<200 && tp_dev.y[t]>200  && tp_dev.y[t]<300)
					{
						LCD_ShowString(230,645,200,16,16," UP  ");//清除
						USART_SendData(USART2,'a');
					}
					
					if(tp_dev.x[t]>300 && tp_dev.x[t]<400 && tp_dev.y[t]>500  && tp_dev.y[t]<600)
					{
						LCD_ShowString(230,645,200,16,16,"REDX  ");//清除
						USART_SendData(USART2,'9');
					}										
					
					if(tp_dev.x[t]>100 && tp_dev.x[t]<200 && tp_dev.y[t]>500  && tp_dev.y[t]<600)
					{
						LCD_ShowString(230,645,200,16,16,"BEEP  ");//清除
						USART_SendData(USART2,'8');
					}					
					
					if(tp_dev.x[t]>200 && tp_dev.x[t]<300 && tp_dev.y[t]>300  && tp_dev.y[t]<400)
					{
						LCD_ShowString(230,645,200,16,16,"STOP  ");//清除
						USART_SendData(USART2,'7');
					}
					
					if(tp_dev.x[t]>100 && tp_dev.x[t]<200 && tp_dev.y[t]>600  && tp_dev.y[t]<700)
					{
						LCD_ShowString(230,645,200,16,16," LM  ");//清除
						USART_SendData(USART2,'6');
					}			
					
					if(tp_dev.x[t]>300 && tp_dev.x[t]<400 && tp_dev.y[t]>600  && tp_dev.y[t]<700)
					{
						LCD_ShowString(230,645,200,16,16," RM  ");//清除
						USART_SendData(USART2,'5');
					}
					
					if(tp_dev.x[t]>200 && tp_dev.x[t]<300 && tp_dev.y[t]>200  && tp_dev.y[t]<300)
					{
						LCD_ShowString(230,645,200,16,16,"MOVE  ");//清除
						USART_SendData(USART2,'4');
					}
					if(tp_dev.x[t]>100 && tp_dev.x[t]<200 && tp_dev.y[t]>300 && tp_dev.y[t]<400)
					{
						LCD_ShowString(230,645,200,16,16,"LEFT  ");//清除
						USART_SendData(USART2,'3');
					}
					if(tp_dev.x[t]>300 && tp_dev.x[t]<400 && tp_dev.y[t]>300 && tp_dev.y[t]<400)
					{
						LCD_ShowString(230,645,200,16,16,"RIGHT");//清除
						USART_SendData(USART2,'2');
					}
					if(tp_dev.x[t]>200 && tp_dev.x[t]<300 && tp_dev.y[t]>400 && tp_dev.y[t]<500)
					{
						LCD_ShowString(230,645,200,16,16,"BACK  ");//清除
						USART_SendData(USART2,'1');
					}
				}
			}else lastpos[t][0]=0XFFFF;
		}		
		delay_ms(5);i++;

		if(flag==1)
		{
			//FC手柄控制
			key_FC=JOYPAD_Read();
			
			if(key_FC==16)	//move
			{
				USART_SendData(USART2,'4');
				LCD_ShowString(230,645,200,16,16,"MOVE  ");//清除				
			}
			if(key_FC==64)	//left
			{
				USART_SendData(USART2,'3');
				LCD_ShowString(230,645,200,16,16,"LEFT  ");//清除
			}
			if(key_FC==128)//right
			{
				USART_SendData(USART2,'2');
				LCD_ShowString(230,645,200,16,16,"RIGHT");//清除
			}
			if(key_FC==32)	//back
			{
				USART_SendData(USART2,'1');
				LCD_ShowString(230,645,200,16,16,"BACK  ");//清除
			}	
			if(key_FC==2)	//up
			{
				LCD_ShowString(230,645,200,16,16," UP  ");//清除
				USART_SendData(USART2,'a');
			}
			if(key_FC==1)	//down
			{
				LCD_ShowString(230,645,200,16,16,"DOWN ");//清除
				USART_SendData(USART2,'b');
			}	
		}

		if(flag==2)
		{
			//红外控制
			key_RX=Remote_Scan();
		
			if(key_RX==98)	//move
			{
				USART_SendData(USART2,'4');	
				LCD_ShowString(230,645,200,16,16,"MOVE  ");//清除
			}
			if(key_RX==34)	//left
			{
				USART_SendData(USART2,'3');
				LCD_ShowString(230,645,200,16,16,"LEFT  ");//清除
			}
			if(key_RX==194)//right
			{
				USART_SendData(USART2,'2');
				LCD_ShowString(230,645,200,16,16,"RIGHT");//清除
			}
			if(key_RX==168)	//back
			{
				USART_SendData(USART2,'1');
				LCD_ShowString(230,645,200,16,16,"BACK  ");//清除
			}	
			if(key_RX==152)	//up
			{
				LCD_ShowString(230,645,200,16,16," UP  ");//清除
				USART_SendData(USART2,'a');
			}
			if(key_RX==56)	//down
			{
				LCD_ShowString(230,645,200,16,16,"DOWN ");//清除
				USART_SendData(USART2,'b');
			}
			if(key_RX==48)	//TL
			{
				LCD_ShowString(230,645,200,16,16," TL  ");//清除
				USART_SendData(USART2,'c');
			}
			if(key_RX==122)	//TR
			{
				LCD_ShowString(230,645,200,16,16," TR  ");//清除
				USART_SendData(USART2,'d');
			}
			if(key_RX==24)	//stop
			{
				LCD_ShowString(230,645,200,16,16,"STOP  ");//清除
				USART_SendData(USART2,'7');
			}
		}

		if(flag==3)
		{			
			//陀螺仪控制
			mpu_dmp_get_data(&pitch,&roll,&yaw);
			
			if(pitch>=20)
			{
				LCD_ShowString(230,645,200,16,16,"MOVE  ");//清除
				USART_SendData(USART2,'4');
			}
			if(pitch<=-20)
			{
				LCD_ShowString(230,645,200,16,16,"BACK  ");//清除
				USART_SendData(USART2,'1');			
			}
			if(roll<=-20)
			{
				LCD_ShowString(230,645,200,16,16,"LEFT  ");//清除
				USART_SendData(USART2,'3');			
			}
			if(roll>=20)
			{
				LCD_ShowString(230,645,200,16,16,"RIGHT");//清除
				USART_SendData(USART2,'2');			
			}
			if(pitch>=-20 && pitch<=20 && roll>=-20 && roll<=20)
			{
				LCD_ShowString(230,645,200,16,16,"STOP  ");//清除
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
		
	NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	            //只需修改一次
	
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;	   	//串口中断 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;		   //抢占优先级0
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;			   //子优先级为0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		//使能
	NVIC_Init(&NVIC_InitStructure);		
}

 int main(void)
 {	 
	int k=0;
	 
	vu8 KEY=0;
	 
	delay_init();	    	 //延时函数初始化	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置中断优先级分组为组2：2位抢占优先级，2位响应优先级
	uart_init(115200);	 	//串口初始化为115200
	 
 	LED_Init();			     //LED端口初始化
	LCD_Init();	
	KEY_Init();	
	MPU_Init();		//初始化MPU6050			 
	JOYPAD_Init();			//手柄初始化	 
	Remote_Init();			//红外接收初始化	
	 
 	tp_dev.init();
	USART2_Configuration();
	 	 
	while(1)
	{
		POINT_COLOR=RED;//设置字体为红色 
		LCD_ShowString(145,225,200,16,16,"MPU6050 AND JOYPAD");//清除
		LCD_ShowString(145,245,200,16,16,"CANNOT BE USED TOGETHER");//清除
		LCD_ShowString(145,265,200,16,16,"KEY0 JOYPAD");//清除	
		LCD_ShowString(145,285,200,16,16,"KEY1 MUP");//清除	
		LCD_ShowString(145,305,200,16,16,"MOD1 screen control");//清除	
		LCD_ShowString(145,325,200,16,16,"MOD2 joypad control");//清除	
		LCD_ShowString(145,345,200,16,16,"MOD3 infrared control");//清除
		LCD_ShowString(145,365,200,16,16,"MOD4 mpu6050 control");//清除
		LCD_ShowString(145,385,200,16,16,"MPU GBC-PB10PB11");//清除
		LCD_ShowString(145,405,200,16,16,"JOYPAD COM3-PB10PB11");//清除
		LCD_ShowString(145,425,200,16,16,"USE KEY2 TO CHANGE MODS");//清除
		
		KEY=KEY_Scan(0);	//得到键值
		
		if(KEY==KEY0_PRES)
		{
			LCD_Clear(WHITE);
			touch_load_keyboard(0,200,(u8**)kbd_tbl1); 
			POINT_COLOR=RED;//设置字体为红色 
			Control();	//电容屏测试
		}			
			
		if(KEY==KEY1_PRES)
		{
			LCD_Clear(WHITE);
			touch_load_keyboard(0,200,(u8**)kbd_tbl1); 
			POINT_COLOR=RED;//设置字体为红色 			
			
			while(mpu_dmp_init())
			{
				LCD_ShowString(215,645,200,16,16,"MPU ERROR");//清除	
				k++;
				delay_ms(500);
				if(k==10)
				{
					break;	
				}	
			} 
			LCD_ShowString(215,645,200,16,16,"         ");//清除
			Control();	//电容屏测试	
		}			
	}
}
