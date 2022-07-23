/******************************************************************************************************
*			遥控小车
*
* 本例程参考 奋斗版 例程
* 文件名: main.c
* 内容简述:	基于stm32f103rct6的屏幕遥控小车，控制端为正点原子战舰v3
* 
* 文件历史:
* 版本号  		日期       作者 KafuuCoori      说明
* v0.1    2021-7-0   		创建该文件
*/

/*********************************************************************************************************
                                             不为失败找借口
                                             只为成功找出路 
**********************************************************************************************************/

/*********************************************************************************************************
*                                             INCLUDE FILES
*******************************************************************************************************/
#include <includes.h>
#include <stdlib.h> 
#include "delay.h"
#include "bsp.h"
#define BEEP PAout(0)	
//电机TIME3 A11A12 C11C12 B12B13 B14B15
//PWM A6 A7 B0 B1 
//蓝牙 A2 A3
//激光 C4 C5
//舵机 B7 B8
//蜂鸣器 A0
/*********************************************************************************************************
*                                          全局变量
*********************************************************************************************************/
void TIM3_Configuration1(u16 arr,u16 psc);	
void TIM3_Configuration2(u16 arr,u16 psc);	
void TIM3_Configuration3(u16 arr,u16 psc);	
void TIM3_Configuration4(u16 arr,u16 psc);	

void TIM4_Configuration1(u16 arr,u16 psc);	
void TIM4_Configuration2(u16 arr,u16 psc);	

void move(void);
void back(void);
void stop(void);
void left(void);
void right(void);

void up(void);
void down(void);
void tl(void);
void tr(void);

void Left(void);
void Right(void);

/*********************************************************************************************************
*                                           宏定义
*********************************************************************************************************/
extern void  BSP_Init (void);

void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...);
int fputc(int ch,FILE  *f);
char *itoa(int value, char *string, int radix);
/*********************************************************************************************************
* 名    称 ：main
* 功能描述 : 初始化STM32
* 输入参数 : none
* 返回参数 : none.
* 作    者 : 
* 修    改 ：（日期、修改人名、修改原因）
* 特殊说明 : （特殊功能说明，例如：有参数检查等）
*********************************************************************************************************/ 

char  data;
int i=1950;
int j=1850;

int main(void)
{	
	BSP_Init();

	TIM3_Configuration1(1999,719);	
	TIM3_Configuration2(1999,719);	
	TIM3_Configuration3(1999,719);	
	TIM3_Configuration4(1999,719);	
	
	TIM4_Configuration1(1999,719);	
	TIM4_Configuration2(1999,719);	
	
	TIM_SetCompare1(TIM4,i); //对应0度
	TIM_SetCompare2(TIM4,j); //对应0度
	
	while(1)
	{		

	}
}

/********************************************以下不要擅自乱修改*****************************************/

/*********************************************************
										printf重定义
**********************************************************/
int fputc(int ch,FILE  *f)
{
	USART_SendData(USART1,(u8)ch);
	while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	return ch;
}


/******************************************************
		格式化串口输出函数
        "\r"	回车符	   USART_OUT(USART1, "abcdefg\r")   
		"\n"	换行符	   USART_OUT(USART1, "abcdefg\r\n")
		"%s"	字符串	   USART_OUT(USART1, "字符串是：%s","abcdefg")
		"%d"	十进制	   USART_OUT(USART1, "a=%d",10)
**********************************************************/
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...)
{ 

	const char *s;
    int d;
    char buf[16];
    va_list ap;
    va_start(ap, Data);

	while(*Data!=0){				                          //判断是否到达字符串结束符
		if(*Data==0x5c){									  //'\'
			switch (*++Data){
				case 'r':							          //回车符
					USART_SendData(USARTx, 0x0d);	   

					Data++;
					break;
				case 'n':							          //换行符
					USART_SendData(USARTx, 0x0a);	
					Data++;
					break;
				
				default:
					Data++;
				    break;
			}
			
			 
		}
		else if(*Data=='%'){									  //
			switch (*++Data){				
				case 's':										  //字符串
                	s = va_arg(ap, const char *);
                	for ( ; *s; s++) {
                    	USART_SendData(USARTx,*s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
                	}
					Data++;
                	break;
            	case 'd':										  //十进制
                	d = va_arg(ap, int);
                	itoa(d, buf, 10);
                	for (s = buf; *s; s++) {
                    	USART_SendData(USARTx,*s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
                	}
					Data++;
                	break;
				default:
					Data++;
				    break;
			}		 
		}
		else USART_SendData(USARTx, *Data++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
	}
}
/******************************************************
		整形数据转字符串函数
        char *itoa(int value, char *string, int radix)
		radix=10 标示是10进制	非十进制，转换结果为0;  

	    例：d=-379;
		执行	itoa(d, buf, 10); 后
		
		buf="-379"							   			  
**********************************************************/
char *itoa(int value, char *string, int radix)
{
    int     i, d;
    int     flag = 0;
    char    *ptr = string;

    /* This implementation only works for decimal numbers. */
    if (radix != 10)
    {
        *ptr = 0;
        return string;
    }

    if (!value)
    {
        *ptr++ = 0x30;
        *ptr = 0;
        return string;
    }

    /* if this is a negative value insert the minus sign. */
    if (value < 0)
    {
        *ptr++ = '-';

        /* Make the value positive. */
        value *= -1;
    }

    for (i = 10000; i > 0; i /= 10)
    {
        d = value / i;

        if (d || flag)
        {
            *ptr++ = (char)(d + 0x30);
            value -= (d * i);
            flag = 1;
        }
    }

    /* Null terminate the string. */
    *ptr = 0;

    return string;

} /* NCL_Itoa */
/******************* (C) COPYRIGHT 2019 奋斗STM32 *****END OF FILE****/
void move()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
		TIM_SetCompare1(TIM3, 100);		//A6 右2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		GPIO_SetBits(GPIOC,GPIO_Pin_12);
		TIM_SetCompare2(TIM3, 100);		//A7 右4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		TIM_SetCompare3(TIM3, 100);		//B0 左3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		TIM_SetCompare4(TIM3, 100);		//B1 左1

}

void back()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
		TIM_SetCompare1(TIM3, 100);		//A6 右2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare2(TIM3, 100);		//A7 右4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		TIM_SetCompare3(TIM3, 100);		//B0 左3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		TIM_SetCompare4(TIM3, 100);		//B1 左1
	
}

void stop()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		TIM_SetCompare1(TIM3, 100);		//A6 右2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		TIM_SetCompare2(TIM3, 100);		//A7 右4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		TIM_SetCompare3(TIM3, 100);		//B0 左3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		TIM_SetCompare4(TIM3, 100);		//B1 左1

}

void left()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
		TIM_SetCompare1(TIM3, 100);		//A6 右2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		GPIO_SetBits(GPIOC,GPIO_Pin_12);
		TIM_SetCompare2(TIM3, 100);		//A7 右4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		TIM_SetCompare3(TIM3, 1000);		//B0 左3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		TIM_SetCompare4(TIM3, 1000);		//B1 左1
	
}

void right()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
		TIM_SetCompare1(TIM3, 1000);		//A6 右2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare2(TIM3, 1000);		//A7 右4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		TIM_SetCompare3(TIM3, 100);		//B0 左3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		TIM_SetCompare4(TIM3, 100);		//B1 左1

}

void up()
{	
			i=i-5;
			TIM_SetCompare1(TIM4,i);
			delay(100);
			
			if(i<=1750)
			{
				i=1750;
			}
}

void down()
{	
			i=i+5;
			TIM_SetCompare1(TIM4,i);
			delay(100);
			
			if(i>=1950)
			{
				i=1950;
			}
}

void tl()
{	
			TIM_SetCompare2(TIM4,1800);
			delay(100);
}

void tr()
{	
			TIM_SetCompare2(TIM4,1900);
			delay(100);
}

void Left()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
		TIM_SetCompare1(TIM3, 100);		//A6 右2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		GPIO_SetBits(GPIOC,GPIO_Pin_12);
		TIM_SetCompare2(TIM3, 100);		//A7 右4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		TIM_SetCompare3(TIM3, 100);		//B0 左3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		TIM_SetCompare4(TIM3, 100);		//B1 左1

}

void Right()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
		TIM_SetCompare1(TIM3, 100);		//A6 右2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare2(TIM3, 100);		//A7 右4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		TIM_SetCompare3(TIM3, 100);		//B0 左3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		TIM_SetCompare4(TIM3, 100);		//B1 左1

}

void USART2_IRQHandler (void)
{
	if (USART_GetITStatus(USART2, USART_IT_RXNE) !=RESET)										
	{
		data = USART_ReceiveData(USART2);	

		if(data=='1')
		{		 
				move();		
				delay(50);
				stop();				
		}				
		if(data=='2')
		{			
				left();		
				delay(50);			
				stop();
		}		
		if(data=='3')
		{			  
				right();		
				delay(50);			
				stop();
		}
		if(data=='4')
		{		 
				back();		
				delay(50);			
				stop();
		}
		if(data=='5')
		{		 
				Left();
				delay(50);			
				stop();
		}
		if(data=='6')
		{		 
				Right();
				delay(50);			
				stop();
		}
		if(data=='7')
		{	
				GPIO_ResetBits(GPIOC,GPIO_Pin_4);
				GPIO_ResetBits(GPIOC,GPIO_Pin_5);			
				stop();
				TIM_SetCompare2(TIM4,1850);
				delay(50);	
		}
		if(data=='8')
		{		 
				BEEP=0;		  
				delay_ms(300);//延时300ms
				BEEP=1;  
				delay_ms(300);//延时300ms
		}	
		if(data=='9')
		{		 
				GPIO_ResetBits(GPIOC,GPIO_Pin_4);
				GPIO_SetBits(GPIOC,GPIO_Pin_5);
		}
		if(data=='a')
		{		 
				up();
		}
		if(data=='b')
		{		 
				down();
		}
		if(data=='c')
		{		 
				tl();
		}
		if(data=='d')
		{		 
				tr();
		}				
	}
}
