/******************************************************************************************************
*			ң��С��
*
* �����̲ο� �ܶ��� ����
* �ļ���: main.c
* ���ݼ���:	����stm32f103rct6����Ļң��С�������ƶ�Ϊ����ԭ��ս��v3
* 
* �ļ���ʷ:
* �汾��  		����       ���� KafuuCoori      ˵��
* v0.1    2021-7-0   		�������ļ�
*/

/*********************************************************************************************************
                                             ��Ϊʧ���ҽ��
                                             ֻΪ�ɹ��ҳ�· 
**********************************************************************************************************/

/*********************************************************************************************************
*                                             INCLUDE FILES
*******************************************************************************************************/
#include <includes.h>
#include <stdlib.h> 
#include "delay.h"
#include "bsp.h"
#define BEEP PAout(0)	
//���TIME3 A11A12 C11C12 B12B13 B14B15
//PWM A6 A7 B0 B1 
//���� A2 A3
//���� C4 C5
//��� B7 B8
//������ A0
/*********************************************************************************************************
*                                          ȫ�ֱ���
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
*                                           �궨��
*********************************************************************************************************/
extern void  BSP_Init (void);

void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...);
int fputc(int ch,FILE  *f);
char *itoa(int value, char *string, int radix);
/*********************************************************************************************************
* ��    �� ��main
* �������� : ��ʼ��STM32
* ������� : none
* ���ز��� : none.
* ��    �� : 
* ��    �� �������ڡ��޸��������޸�ԭ��
* ����˵�� : �����⹦��˵�������磺�в������ȣ�
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
	
	TIM_SetCompare1(TIM4,i); //��Ӧ0��
	TIM_SetCompare2(TIM4,j); //��Ӧ0��
	
	while(1)
	{		

	}
}

/********************************************���²�Ҫ�������޸�*****************************************/

/*********************************************************
										printf�ض���
**********************************************************/
int fputc(int ch,FILE  *f)
{
	USART_SendData(USART1,(u8)ch);
	while (USART_GetFlagStatus(USART1,USART_FLAG_TC) == RESET);
	return ch;
}


/******************************************************
		��ʽ�������������
        "\r"	�س���	   USART_OUT(USART1, "abcdefg\r")   
		"\n"	���з�	   USART_OUT(USART1, "abcdefg\r\n")
		"%s"	�ַ���	   USART_OUT(USART1, "�ַ����ǣ�%s","abcdefg")
		"%d"	ʮ����	   USART_OUT(USART1, "a=%d",10)
**********************************************************/
void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...)
{ 

	const char *s;
    int d;
    char buf[16];
    va_list ap;
    va_start(ap, Data);

	while(*Data!=0){				                          //�ж��Ƿ񵽴��ַ���������
		if(*Data==0x5c){									  //'\'
			switch (*++Data){
				case 'r':							          //�س���
					USART_SendData(USARTx, 0x0d);	   

					Data++;
					break;
				case 'n':							          //���з�
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
				case 's':										  //�ַ���
                	s = va_arg(ap, const char *);
                	for ( ; *s; s++) {
                    	USART_SendData(USARTx,*s);
						while(USART_GetFlagStatus(USARTx, USART_FLAG_TC)==RESET);
                	}
					Data++;
                	break;
            	case 'd':										  //ʮ����
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
		��������ת�ַ�������
        char *itoa(int value, char *string, int radix)
		radix=10 ��ʾ��10����	��ʮ���ƣ�ת�����Ϊ0;  

	    ����d=-379;
		ִ��	itoa(d, buf, 10); ��
		
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
/******************* (C) COPYRIGHT 2019 �ܶ�STM32 *****END OF FILE****/
void move()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
		TIM_SetCompare1(TIM3, 100);		//A6 ��2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		GPIO_SetBits(GPIOC,GPIO_Pin_12);
		TIM_SetCompare2(TIM3, 100);		//A7 ��4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		TIM_SetCompare3(TIM3, 100);		//B0 ��3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		TIM_SetCompare4(TIM3, 100);		//B1 ��1

}

void back()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
		TIM_SetCompare1(TIM3, 100);		//A6 ��2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare2(TIM3, 100);		//A7 ��4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		TIM_SetCompare3(TIM3, 100);		//B0 ��3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		TIM_SetCompare4(TIM3, 100);		//B1 ��1
	
}

void stop()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		TIM_SetCompare1(TIM3, 100);		//A6 ��2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		TIM_SetCompare2(TIM3, 100);		//A7 ��4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		TIM_SetCompare3(TIM3, 100);		//B0 ��3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		TIM_SetCompare4(TIM3, 100);		//B1 ��1

}

void left()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
		TIM_SetCompare1(TIM3, 100);		//A6 ��2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		GPIO_SetBits(GPIOC,GPIO_Pin_12);
		TIM_SetCompare2(TIM3, 100);		//A7 ��4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		TIM_SetCompare3(TIM3, 1000);		//B0 ��3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		TIM_SetCompare4(TIM3, 1000);		//B1 ��1
	
}

void right()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_12);
		GPIO_SetBits(GPIOA,GPIO_Pin_11);
		TIM_SetCompare1(TIM3, 1000);		//A6 ��2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare2(TIM3, 1000);		//A7 ��4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		TIM_SetCompare3(TIM3, 100);		//B0 ��3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		TIM_SetCompare4(TIM3, 100);		//B1 ��1

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
		TIM_SetCompare1(TIM3, 100);		//A6 ��2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_11);
		GPIO_SetBits(GPIOC,GPIO_Pin_12);
		TIM_SetCompare2(TIM3, 100);		//A7 ��4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_13);
		GPIO_SetBits(GPIOB,GPIO_Pin_12);
		TIM_SetCompare3(TIM3, 100);		//B0 ��3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_14);
		GPIO_SetBits(GPIOB,GPIO_Pin_15);
		TIM_SetCompare4(TIM3, 100);		//B1 ��1

}

void Right()
{
		GPIO_ResetBits(GPIOA,GPIO_Pin_11);
		GPIO_SetBits(GPIOA,GPIO_Pin_12);
		TIM_SetCompare1(TIM3, 100);		//A6 ��2
		
		GPIO_ResetBits(GPIOC,GPIO_Pin_12);
		GPIO_SetBits(GPIOC,GPIO_Pin_11);
		TIM_SetCompare2(TIM3, 100);		//A7 ��4
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_12);
		GPIO_SetBits(GPIOB,GPIO_Pin_13);
		TIM_SetCompare3(TIM3, 100);		//B0 ��3
		
		GPIO_ResetBits(GPIOB,GPIO_Pin_15);
		GPIO_SetBits(GPIOB,GPIO_Pin_14);
		TIM_SetCompare4(TIM3, 100);		//B1 ��1

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
				delay_ms(300);//��ʱ300ms
				BEEP=1;  
				delay_ms(300);//��ʱ300ms
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
