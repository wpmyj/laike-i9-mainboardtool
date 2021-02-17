/**
  ******************************************************************************
  * @file    GPIO/IOToggle/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and peripherals
  *          interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x_it.h" 
#include "maindef.h"
#include "apiLib.h"


 
void NMI_Handler(void)
{
}
 
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}
 
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

 
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}
 
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}
 
//void SVC_Handler(void)
//{
//}
 
void DebugMon_Handler(void)
{
}
 
//void PendSV_Handler(void)
//{
//}
 
//void SysTick_Handler(void)
//{
//}



void TIM2_IRQHandler(void)        //1ms interrupt
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		/*        用于生成1ms滴答定时器          */
		mMaininf.mSystem.mSystemTick ++;
		if(mMaininf.mSystem.mSystemTick >= SYSTEMTIMEMAX) mMaininf.mSystem.mSystemTick = 0;
		
 		/*        用于生成SD卡卡控制时序         */
// 		if(mMaininf.mWork.mWorkDropSendFlag == 1)
// 		{
// 			PBout(0) = ~PBout(0);
// // 			mMaininf.mWork.mWorkDropSendCont ++;
// // 			if(mMaininf.mWork.mWorkDropSendCont >= 2)
// // 			{
// // 				PBout(0) = ~PBout(0);
// // 				mMaininf.mWork.mWorkDropSendCont = 0;
// // 			}
// 		}
// 		
// 		if(PAout(0) == 0)
// 		{
// 			PAout(0) = 1;
// 		}
// 		else
// 		{
// 			PAout(0) = 0;
// 		}
	}
	TIM_ClearITPendingBit(TIM2,TIM_IT_Update);
}

void TIM3_IRQHandler(void)        //200us interrupt
{
	if(TIM_GetITStatus(TIM3,TIM_IT_Update)!=RESET)
	{
		mMaininf.mSystem.mSystem200usTick ++;
		if(mMaininf.mSystem.mSystem200usTick >= SYSTEMTIMEMAX) mMaininf.mSystem.mSystem200usTick = 0;
		
		if(mMaininf.mWork.mWorkCodeSendFlag == 1)
		{
			mMaininf.mWork.mWorkCodeSendCont ++ ;
			
			if(mMaininf.mWork.mWorkCodeSendCont == 2)
			{
				PBout(0) = 1;
			}
			if(mMaininf.mWork.mWorkCodeSendCont >= 5)
			{
// 				PBout(0) = ~PBout(0);
// 				mMaininf.mWork.mWorkCodeSendCont = 0;
				PBout(0) = 0;
				mMaininf.mWork.mWorkCodeSendCont = 0;
			}
			
		}
		if(mMaininf.mWork.mWorkDropSendFlag == 1)
		{
			mMaininf.mWork.mWorkDropSendCont ++;
			
			if(mMaininf.mWork.mWorkChangePhaseFlag == 0)
			{
				if(mMaininf.mWork.mWorkDropSendCont == 1)
				{
					PBout(0) = ~PBout(0);
				}
				else if(mMaininf.mWork.mWorkDropSendCont == 6)
				{
					PBout(0) = ~PBout(0);
				}
			}
			else
			{
				if(mMaininf.mWork.mWorkDropSendCont == 3)
				{
					PBout(0) = ~PBout(0);
				}
				else if(mMaininf.mWork.mWorkDropSendCont == 8)
				{
					PBout(0) = ~PBout(0);
				}
			}
			
			if(mMaininf.mWork.mWorkDropSendCont >= 10)
			{
				mMaininf.mWork.mWorkDropSendCont = 0;
			}
			
// 			if(mMaininf.mWork.mWorkChangePhaseFlag == 0)
// 			{
// 				if(mMaininf.mWork.mWorkDropSendCont >= 5)//2ms周期
// 				{
// 					PBout(0) = ~PBout(0);
// 					mMaininf.mWork.mWorkDropSendCont = 0;
// 				}
// 			}
		}
		
	}
	
	TIM_ClearITPendingBit(TIM3,TIM_IT_Update);
}

void TIM4_IRQHandler(void)        //10us interrupt
{
	u8 mPin = 0;
	
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=RESET)
	{
		mMaininf.mSystem.mSystem10usTick ++;
		if(mMaininf.mSystem.mSystem10usTick >= SYSTEMTIMEMAX) mMaininf.mSystem.mSystem10usTick = 0;
		
		
		if(mMaininf.mWork.mWorkGuideSendFlag == 1)
		{
			switch(mMaininf.mWork.mWorkGuideSendStep)
			{
				case 0:   //head
					mPin = 1;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 449)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
					break;
				case 1:
					mPin = 0;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 449)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
					break;
				case 2:   //1
					mPin = 1;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 3:
					mPin = 0;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 168)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 4:   //0
					mPin = 1;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 5:
					mPin = 0;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 6:   //1
					mPin = 1;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 7:
					mPin = 0;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 168)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 8:   //0
					mPin = 1;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 9:
					mPin = 0;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 10:   //0
					mPin = 1;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 11:
				mPin = 0;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 12:   //0
					mPin = 1;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 13:
					mPin = 0;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 14:   //1
					mPin = 1;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 15:
					mPin = 0;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 168)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 16:   //1
					mPin = 1;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 17:
					mPin = 0;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 168)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 18:   //0
					mPin = 1;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 19:
					mPin = 0;
					if((mMaininf.mWork.mWorkGuideSendCont++) > 55)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep++;
					}
				break;
				case 20:
					if((mMaininf.mWork.mWorkGuideSendCont++) > 8180)
					{
						mMaininf.mWork.mWorkGuideSendCont = 0;
						mMaininf.mWork.mWorkGuideSendStep = 0;
					}
					break;
				default:
					break;
			}
			
			api_Guide_Send(~mPin);
		}
	}
	
	TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}

// void USART1_IRQHandler(void)
// {
// 	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)     /*   接收数据   */
// 	{
// 		api_UART1_ReceiveData(USART_ReceiveData(USART1));
// 		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
// 	}
// 	if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)      /*   发送数据   */
// 	{
// 		if(mMaininf.mUart1.mSendSize > 0)
// 		{
// 			USART_SendData(USART1,mMaininf.mUart1.TxBuffer[mMaininf.mUart1.mSendCont ++]);
// 			if(mMaininf.mUart1.mSendCont == mMaininf.mUart1.mSendSize)
// 			{
// 				mMaininf.mUart1.mSendSize = 0;
// 				mMaininf.mUart1.mSendCont = 0;
// 				USART_ITConfig(USART1,USART_IT_TC,DISABLE);
// 				USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
// 			}
// 		}
// 		else
// 		{
// 			mMaininf.mUart1.mSendSize = 0;
// 			mMaininf.mUart1.mSendCont = 0;
// 			USART_ITConfig(USART1,USART_IT_TC,DISABLE);
// 			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
// 		}
// 		USART_ClearITPendingBit(USART1,USART_IT_TC);
// 	}
// }

void USART1_IRQHandler(void)
{
	if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)     /*   接收数据   */
	{
		api_UART1_ReceiveData(USART_ReceiveData(USART1));
		USART_ClearITPendingBit(USART1,USART_IT_RXNE);
	}
	if(USART_GetITStatus(USART1,USART_IT_TC)!=RESET)      /*   发送数据   */
	{
		if(mMaininf.mUart1.mSendSize > 0)
		{
			USART_SendData(USART1,mMaininf.mUart1.TxBuffer[mMaininf.mUart1.mSendCont ++]);
			if(mMaininf.mUart1.mSendCont == mMaininf.mUart1.mSendSize)
			{
				mMaininf.mUart1.mSendSize = 0;
				mMaininf.mUart1.mSendCont = 0;
				USART_ITConfig(USART1,USART_IT_TC,DISABLE);
				USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
			}
		}
		else
		{
			mMaininf.mUart1.mSendSize = 0;
			mMaininf.mUart1.mSendCont = 0;
			USART_ITConfig(USART1,USART_IT_TC,DISABLE);
			USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
		}
		USART_ClearITPendingBit(USART1,USART_IT_TC);
	}
}

void USART3_IRQHandler(void)
{
	if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)     /*   接收数据   */
	{
		mMaininf.mWork.mWorkBigUartFlag = 1;
		USART_ClearITPendingBit(USART3,USART_IT_RXNE);
	}
	if(USART_GetITStatus(USART3,USART_IT_TC)!=RESET)      /*   发送数据   */
	{
		USART_ClearITPendingBit(USART1,USART_IT_TC);
	}
}

void UART4_IRQHandler(void)
{
	if(USART_GetITStatus(UART4,USART_IT_RXNE)!=RESET)     /*   接收数据   */
	{
		api_UART4_ReceiveData(USART_ReceiveData(UART4));
		USART_ClearITPendingBit(UART4,USART_IT_RXNE);
	}
	if(USART_GetITStatus(UART4,USART_IT_TC)!=RESET)      /*   发送数据   */
	{
		if(mMaininf.mUart4.mSendSize > 0)
		{
			USART_SendData(UART4,mMaininf.mUart4.TxBuffer[mMaininf.mUart4.mSendCont ++]);
			if(mMaininf.mUart4.mSendCont == mMaininf.mUart4.mSendSize)
			{
				mMaininf.mUart4.mSendSize = 0;
				mMaininf.mUart4.mSendCont = 0;
				USART_ITConfig(UART4,USART_IT_TC,DISABLE);
				USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
			}
		}
		else
		{
			mMaininf.mUart4.mSendSize = 0;
			mMaininf.mUart4.mSendCont = 0;
			USART_ITConfig(UART4,USART_IT_TC,DISABLE);
			USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
		}
		USART_ClearITPendingBit(UART4,USART_IT_TC);
	}
}

void UART5_IRQHandler(void)
{
	if(USART_GetITStatus(UART5,USART_IT_RXNE)!=RESET)     /*   接收数据   */
	{
		api_UART5_ReceiveData(USART_ReceiveData(UART5));
		USART_ClearITPendingBit(UART5,USART_IT_RXNE);
	}
	if(USART_GetITStatus(UART5,USART_IT_TC)!=RESET)      /*   发送数据   */
	{
		if(mMaininf.mUart5.mSendSize > 0)
		{
			USART_SendData(UART5,mMaininf.mUart5.TxBuffer[mMaininf.mUart5.mSendCont ++]);
			if(mMaininf.mUart5.mSendCont == mMaininf.mUart5.mSendSize)
			{
				mMaininf.mUart5.mSendSize = 0;
				mMaininf.mUart5.mSendCont = 0;
				USART_ITConfig(UART5,USART_IT_TC,DISABLE);
				USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
			}
		}
		else
		{
			mMaininf.mUart5.mSendSize = 0;
			mMaininf.mUart5.mSendCont = 0;
			USART_ITConfig(UART5,USART_IT_TC,DISABLE);
			USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
		}
		USART_ClearITPendingBit(UART5,USART_IT_TC);
	}
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
