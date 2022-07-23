/**
  ******************************************************************************
  * @file CAN/LoopBack/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version  V3.0.0
  * @date  04/06/2009
  * @brief  Main Interrupt Service Routines.
  *         This file provides template for all exceptions handler and 
  *         peripherals interrupt service routine.
  ******************************************************************************
  * @copy
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2009 STMicroelectronics</center></h2>
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h"
#include  <stdio.h>
extern void USART_OUT(USART_TypeDef* USARTx, uint8_t *Data,...);

extern unsigned int overcount;

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval : None
  */

void USART1_IRQHandler (void)
{
	if (USART_GetITStatus(USART1, USART_IT_RXNE) !=RESET)										
	{
//		while(USART_GetFlagStatus(USART1, USART_FLAG_TC) ==RESET);              //判断是否发送完毕
		USART_ClearFlag(USART1, USART_FLAG_RXNE);                              //清楚标志位
	}
}
/****************************************************************************
* 函数名: TIM2_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void TIM2_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET)			//检查指定的TIM中断发生与否:TIM 中断源
	{
		TIM_ClearFlag(TIM2,TIM_FLAG_Update);	//清除中断标志位			
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);	 
	}
}
/****************************************************************************
* 函数名: TIM4_IRQHandler()
* 功 能: 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
void TIM4_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET)			//检查指定的TIM中断发生与否:TIM 中断源
	{		
//		TIM_ClearFlag(TIM2,TIM_FLAG_Update);		
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);	 
//		overcount++;
	}
}
/****************************************************************************
* 函数名: TIM6_IRQHandler()
* 功 能: PID 处理
* 输 入: 无
* 输 出: 无
****************************************************************************/
//void TIM6_IRQHandler(void)
//{ 
//	if (TIM_GetITStatus(TIM6, TIM_IT_Update) != RESET)			//检查指定的TIM中断发生与否:TIM 中断源
//	{  		
//		TIM_ClearFlag(TIM6,TIM_FLAG_Update);	//清除中断标志位			
//		TIM_ClearITPendingBit(TIM6, TIM_IT_Update);	 
//		overcount++;
//	}
//}

/*******************************************************************************
* Function Name  : TIM7_IRQHandler
* Description    : 精确延时
*                  request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void TIM7_IRQHandler(void)
{
	if (TIM_GetITStatus(TIM7, TIM_IT_Update) != RESET)			//检查指定的TIM中断发生与否:TIM 中断源
	{  		
		TIM_ClearFlag(TIM7,TIM_FLAG_Update);	//清除中断标志位
		TIM_ClearITPendingBit(TIM7, TIM_IT_Update);										
	}
}

/*******************************************************************************
* Function Name  : EXTI5_IRQHandler
* Description    : This function handles External interrupt Line 0 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void EXTI9_5_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
//	{
//		
//	}
//	EXTI_ClearITPendingBit(EXTI_Line15);
//}
/*******************************************************************************
* Function Name  : EXTI5_IRQHandler
* Description    : This function handles External interrupt Line 0 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
//void EXTI0_IRQHandler(void)
//{
//	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
//	{
//	
//	}
//	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
//}

/*******************************************************************************
* Function Name  : EXTI5_IRQHandler
* Description    : This function handles External interrupt Line 0 request.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus(EXTI_Line5)!=RESET)
	{
		
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //清除EXTI0线路挂起位
}

void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval : None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval : None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval : None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval : None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval : None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval : None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSV_Handler exception.
  * @param  None
  * @retval : None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval : None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*            STM32F10x Peripherals Interrupt Handlers                        */
/******************************************************************************/

/**
  * @brief  This function handles USB Low Priority or CAN RX0 interrupts 
  *   requests.
  * @param  None
  * @retval : None
  */
void USB_LP_CAN1_RX0_IRQHandler(void)
{

}
/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval : None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */ 

/**
  * @}
  */ 

/******************* (C) COPYRIGHT 2009 STMicroelectronics *****END OF FILE****/
