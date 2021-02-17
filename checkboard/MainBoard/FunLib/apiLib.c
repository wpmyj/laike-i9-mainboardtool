/****************************************************************************************************/
/*			@FileName		:	APILIB.c														  	*/
/*			@Author			:	zhengbaiqiu															*/
/*			@Version		:	v1.0																*/
/*			@Date			:	2019.11.12  														*/
/****************************************************************************************************/


/* Includes --------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32f10x_it.h"
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "math.h"
#include <stdarg.h>

/* FreeRTOS --------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "FreeRTOSConfig.h"
#include "portmacro.h"
#include "projdefs.h"
#include "task.h"
#include "queue.h"
#include "event_groups.h"
#include "semphr.h"

/* Project ---------------------------------------------------------------------*/
#include "maindef.h"
#include "bsp.h"
#include "gpioredef.h"
#include "apiLib.h"
#include "eeprom.h"

#include "TK_TimerController.h"


/* Variable --------------------------------------------------------------------*/

/* Function --------------------------------------------------------------------*/
/*  ʱ����ؿ��ƿ�                                                  */
u32 api_GetSystemTimePeriod(u32 StartTime);
u32 api_GetCurrentSystemTime(void);
void api_UART1_MainBoard_SendCMDData(u8 seq,u8 mode,u8 cmd);
void api_UART1_ReceiveData(u8 vData);
void api_UART4_DEBUG_SendCMDData(u8 seq,u8 mode,u8 cmd);
void api_UART4_ReceiveData(u8 vData);
void api_UART4_SendData(u16 vCont, u8 *pData);
void api_UART5_Display_SendCMDData(u8 mode,u8 cmd,u8 status);
void api_UART5_ReceiveData(u8 vData);
void api_MachinePowerOn(void);
void api_Send_Signal(u8 mCmd,u8 OpenFlag);
void api_Control_Motor(u8 mCmd,u8 OpenFlag);
u8 api_ReadGpioInputStauts(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 Val,uint8_t Cont);
u8 api_ReadWheelGpioInputStauts(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 Val,uint8_t Cont);
u8 api_Check_PWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 cycle,u8 differ,u8 count);
u8 api_Check_Wheel_PWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 cycle,u8 differ);
u8 api_Test_ADC(__IO uint16_t *adcval,uint16_t detectval,uint16_t diffval);
void api_Guide_Send(u8 mStatus);
u8 api_Check_MainBoard_Mode(void);
void api_ShortToStr(u8* str,s16 data);






/*--------------------------------------------------------------------------------

        ʱ����ؿ⺯��

---------------------------------------------------------------------------------*/

/*****************************************************************************
 * @name       :u32 api_GetSystemTimePeriod(u32 StartTime)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :���ش�ʱ���뿪ʼʱ�̵�ʱ����
 * @parameters :��ʼʱ��
 * @retvalue   :ʱ����
******************************************************************************/
u32 api_GetSystemTimePeriod(u32 StartTime)
{
	u32 res;
	
	if(mMaininf.mSystem.mSystemTick >= StartTime)
	{
		res = mMaininf.mSystem.mSystemTick - StartTime;
	}
	else
	{
		res = SYSTEMTIMEMAX - StartTime + mMaininf.mSystem.mSystemTick;
	}
	
	return res;
}

/*****************************************************************************
 * @name       :u32 api_GetCurrentSystemTime(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :���ش˿̵�ʱ��δ�
 * @parameters :None
 * @retvalue   :��ʱʱ��
******************************************************************************/
u32 api_GetCurrentSystemTime(void)
{
	return mMaininf.mSystem.mSystemTick;
}


/*------------------------------------------------------------------------------

        ����uartͨѶ

--------------------------------------------------------------------------------*/


/*****************************************************************************
 * @name       :void api_UART1_SendData(u16 vCont, u8 *pData)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :send data
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void api_UART1_SendData(u16 vCont, u8 *pData)
{
	u16 iCont ;
	mMaininf.mUart1.mSendSize = vCont;
	for (iCont=0;iCont < vCont;iCont ++)
	{
		mMaininf.mUart1.TxBuffer[iCont] = *(pData + iCont);
	}
	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
	USART_ITConfig(USART1,USART_IT_TC,ENABLE);
}

/*****************************************************************************
 * @name       :void api_UART1_MainBoard_SendCMDData(u8 seq,u8 mode,u8 cmd)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :send data
 * @parameters :cmd
 * @retvalue   :None
******************************************************************************/
void api_UART1_MainBoard_SendCMDData(u8 seq,u8 mode,u8 cmd)
{
	mMaininf.mUart1.SendBuf[0] = 0xAA;
	mMaininf.mUart1.SendBuf[1] = 0xDD;
	mMaininf.mUart1.SendBuf[2] = seq;
	mMaininf.mUart1.SendBuf[3] = mode;
	mMaininf.mUart1.SendBuf[4] = cmd;
	mMaininf.mUart1.SendBuf[5] = mMaininf.mUart1.SendBuf[0] ^ mMaininf.mUart1.SendBuf[1] ^
								 mMaininf.mUart1.SendBuf[2] ^ mMaininf.mUart1.SendBuf[3] ^
								 mMaininf.mUart1.SendBuf[4];
	
	api_UART1_SendData(6,mMaininf.mUart1.SendBuf);
}

/*****************************************************************************
 * @name       :void api_ClearUART1ReceiveFlag(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :clear uart2 receive flag
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void api_ClearUART1ReceiveFlag(void)
{
	mMaininf.mUart1.mReceiveStep = ST_MAIN_0xAA;
	mMaininf.mUart1.mReceiveBCC = 0;
	mMaininf.mUart1.mReceiveSize = 0;
}

/*****************************************************************************
 * @name       :void api_UART1_ReceiveData(u8 vData)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :receive data
 * @parameters :data
 * @retvalue   :None
******************************************************************************/
void api_UART1_ReceiveData(u8 vData)
{
	if(mMaininf.mUart1.mReceiveTimeOut == 0)
	{
		api_ClearUART1ReceiveFlag();
	}
	switch(mMaininf.mUart1.mReceiveStep)
	{
		case ST_MAIN_0xAA :
			if(vData == 0xAA)
			{
				mMaininf.mUart1.mReceiveStep = ST_MAIN_0xDD;
				mMaininf.mUart1.mReceiveBCC = mMaininf.mUart1.mReceiveBCC ^ vData;
				mMaininf.mUart1.mReceiveTimeOut = 10;
			}
			else mMaininf.mUart1.mReceiveTimeOut = 0;
			break;
		case ST_MAIN_0xDD :
			if(vData == 0xDD)
			{
				mMaininf.mUart1.mReceiveStep = ST_MAIN_SEQ;
				mMaininf.mUart1.mReceiveBCC = mMaininf.mUart1.mReceiveBCC ^ vData;
				mMaininf.mUart1.mReceiveTimeOut = 10;
			}
			else mMaininf.mUart1.mReceiveTimeOut = 0;
			break;
		case ST_MAIN_SEQ :
			mMaininf.mUart1.mReceiveStep = ST_MAIN_MODE;
			mMaininf.mUart1.mReceiveTimeOut = 10;
			mMaininf.mUart1.RxBuffer[mMaininf.mUart1.mReceiveSize ++] = vData;
			mMaininf.mUart1.mReceiveBCC = mMaininf.mUart1.mReceiveBCC ^ vData;
			break;
		case ST_MAIN_MODE :
			mMaininf.mUart1.mReceiveStep = ST_MAIN_CMD;
			mMaininf.mUart1.mReceiveTimeOut = 10;
			mMaininf.mUart1.RxBuffer[mMaininf.mUart1.mReceiveSize ++] = vData;
			mMaininf.mUart1.mReceiveBCC = mMaininf.mUart1.mReceiveBCC ^ vData;
			break;
		case ST_MAIN_CMD :
			mMaininf.mUart1.mReceiveStep = ST_MAIN_LEN;
			mMaininf.mUart1.mReceiveTimeOut = 10;
			mMaininf.mUart1.RxBuffer[mMaininf.mUart1.mReceiveSize ++] = vData;
			mMaininf.mUart1.mReceiveBCC = mMaininf.mUart1.mReceiveBCC ^ vData;
			break;
		case ST_MAIN_LEN :
			mMaininf.mUart1.mReceiveStep = ST_MAIN_DATA;
			mMaininf.mUart1.mReceiveTimeOut = 10;
			mMaininf.mUart1.mReceiveLen = vData;
			mMaininf.mUart1.RxBuffer[mMaininf.mUart1.mReceiveSize ++] = vData;
			mMaininf.mUart1.mReceiveBCC = mMaininf.mUart1.mReceiveBCC ^ vData;
// 			if()
// 			{
// 				
// 			}
// 			else
// 			{
// 				
// 			}
			break;
		case ST_MAIN_DATA :
			mMaininf.mUart1.mReceiveLen --;
			if(mMaininf.mUart1.mReceiveLen == 0)
			{
				mMaininf.mUart1.mReceiveStep = ST_MAIN_BCC;
			}
			mMaininf.mUart1.mReceiveTimeOut = 10;
			mMaininf.mUart1.RxBuffer[mMaininf.mUart1.mReceiveSize ++] = vData;
			mMaininf.mUart1.mReceiveBCC = mMaininf.mUart1.mReceiveBCC ^ vData;
			break;
		case ST_MAIN_BCC :
			if(mMaininf.mUart1.mReceiveBCC == vData)
			{
				for(mMaininf.mUart1.mReceiveCont = 0;mMaininf.mUart1.mReceiveCont < (mMaininf.mUart1.RxBuffer[3] + 4);mMaininf.mUart1.mReceiveCont ++)
				{
					mMaininf.mUart1.ReceiveBuf[mMaininf.mUart1.mReceiveCont] = mMaininf.mUart1.RxBuffer[mMaininf.mUart1.mReceiveCont];
				}
				
				mMaininf.mUart1.mReceiveFlag = 1;       //���յ�����
				mMaininf.mUart1.mReceiveTimeOut = 0;
				
			}
			else mMaininf.mUart1.mReceiveTimeOut = 0;
			break;
		default :
			break;
	}
}

/*****************************************************************************
 * @name       :void api_UART4_SendData(u16 vCont, u8 *pData)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :send data
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void api_UART4_SendData(u16 vCont, u8 *pData)
{
	u16 iCont ;
	mMaininf.mUart4.mSendSize = vCont;
	for (iCont=0;iCont < vCont;iCont ++)
	{
		mMaininf.mUart4.TxBuffer[iCont] = *(pData + iCont);
	}
//	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
	USART_ITConfig(UART4,USART_IT_TC,ENABLE);
}

// void api_UART4_SendNum(u16 vCont, u8 *pData)
// {
// 	u16 iCont ;
// 	mMaininf.mUart4.mSendSize = vCont;
// 	for (iCont=0;iCont < vCont;iCont ++)
// 	{
// 		mMaininf.mUart4.TxBuffer[iCont] = *(pData + iCont);
// 	}
// //	USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
// 	USART_ITConfig(UART4,USART_IT_TC,ENABLE);
// }

/*****************************************************************************
 * @name       :void api_UART4_DEBUG_SendCMDData(u8 seq,u8 mode,u8 cmd)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :send data
 * @parameters :cmd
 * @retvalue   :None
******************************************************************************/
void api_UART4_DEBUG_SendCMDData(u8 seq,u8 mode,u8 cmd)
{
	mMaininf.mUart4.SendBuf[0] = 0xAA;
	mMaininf.mUart4.SendBuf[1] = 0xDD;
	mMaininf.mUart4.SendBuf[2] = seq;
	mMaininf.mUart4.SendBuf[3] = mode;
	mMaininf.mUart4.SendBuf[4] = cmd;
	mMaininf.mUart4.SendBuf[5] = mMaininf.mUart4.SendBuf[0] ^ mMaininf.mUart4.SendBuf[1] ^
								 mMaininf.mUart4.SendBuf[2] ^ mMaininf.mUart4.SendBuf[3] ^
								 mMaininf.mUart4.SendBuf[4];
	
	api_UART4_SendData(6,mMaininf.mUart4.SendBuf);
}

// void api_UART4_DEBUG_SendCMDData(u8 seq,u8 mode,u8 cmd,u8 len,u8* data)
// {
// 	mMaininf.mUart4.SendBuf[0] = 0xAA;
// 	mMaininf.mUart4.SendBuf[1] = 0xDD;
// 	mMaininf.mUart4.SendBuf[2] = seq;
// 	mMaininf.mUart4.SendBuf[3] = mode;
// 	mMaininf.mUart4.SendBuf[4] = cmd;
// 	mMaininf.mUart4.SendBuf[5] = mMaininf.mUart4.SendBuf[0] ^ mMaininf.mUart4.SendBuf[1] ^
// 								 mMaininf.mUart4.SendBuf[2] ^ mMaininf.mUart4.SendBuf[3] ^
// 								 mMaininf.mUart4.SendBuf[4];
// 	
// 	api_UART4_SendData(6,mMaininf.mUart4.SendBuf);
// }

/*****************************************************************************
 * @name       :void api_ClearUART4ReceiveFlag(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :clear uart2 receive flag
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void api_ClearUART4ReceiveFlag(void)
{
	mMaininf.mUart4.mReceiveStep = ST_MAIN_0xAA;
	mMaininf.mUart4.mReceiveBCC = 0;
	mMaininf.mUart4.mReceiveSize = 0;
}

/*****************************************************************************
 * @name       :void api_UART4_ReceiveData(u8 vData)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :receive data
 * @parameters :data
 * @retvalue   :None
******************************************************************************/
void api_UART4_ReceiveData(u8 vData)
{
	if(mMaininf.mUart4.mReceiveTimeOut == 0)
	{
		api_ClearUART4ReceiveFlag();
	}
	switch(mMaininf.mUart4.mReceiveStep)
	{
		case ST_MAIN_0xAA :
			if(vData == 0xAA)
			{
				mMaininf.mUart4.mReceiveStep = ST_MAIN_0xDD;
				mMaininf.mUart4.mReceiveBCC = mMaininf.mUart4.mReceiveBCC ^ vData;
				mMaininf.mUart4.mReceiveTimeOut = 10;
			}
			else mMaininf.mUart4.mReceiveTimeOut = 0;
			break;
		case ST_MAIN_0xDD :
			if(vData == 0xDD)
			{
				mMaininf.mUart4.mReceiveStep = ST_MAIN_SEQ;
				mMaininf.mUart4.mReceiveBCC = mMaininf.mUart4.mReceiveBCC ^ vData;
				mMaininf.mUart4.mReceiveTimeOut = 10;
			}
			else mMaininf.mUart4.mReceiveTimeOut = 0;
			break;
		case ST_MAIN_SEQ :
			mMaininf.mUart4.mReceiveStep = ST_MAIN_MODE;
			mMaininf.mUart4.mReceiveTimeOut = 10;
			mMaininf.mUart4.RxBuffer[mMaininf.mUart4.mReceiveSize ++] = vData;
			mMaininf.mUart4.mReceiveBCC = mMaininf.mUart4.mReceiveBCC ^ vData;
			break;
		case ST_MAIN_MODE :
			mMaininf.mUart4.mReceiveStep = ST_MAIN_CMD;
			mMaininf.mUart4.mReceiveTimeOut = 10;
			mMaininf.mUart4.RxBuffer[mMaininf.mUart4.mReceiveSize ++] = vData;
			mMaininf.mUart4.mReceiveBCC = mMaininf.mUart4.mReceiveBCC ^ vData;
			break;
		case ST_MAIN_CMD :
			mMaininf.mUart4.mReceiveStep = ST_MAIN_LEN;
			mMaininf.mUart4.mReceiveTimeOut = 10;
			mMaininf.mUart4.RxBuffer[mMaininf.mUart4.mReceiveSize ++] = vData;
			mMaininf.mUart4.mReceiveBCC = mMaininf.mUart4.mReceiveBCC ^ vData;
			break;
		case ST_MAIN_LEN :
			mMaininf.mUart4.mReceiveStep = ST_MAIN_DATA;
			mMaininf.mUart4.mReceiveTimeOut = 10;
			mMaininf.mUart4.mReceiveLen = vData;
			mMaininf.mUart4.RxBuffer[mMaininf.mUart4.mReceiveSize ++] = vData;
			mMaininf.mUart4.mReceiveBCC = mMaininf.mUart4.mReceiveBCC ^ vData;
			break;
		case ST_MAIN_DATA :
			mMaininf.mUart4.mReceiveLen --;
			if(mMaininf.mUart4.mReceiveLen == 0)
			{
				mMaininf.mUart4.mReceiveStep = ST_MAIN_BCC;
			}
			mMaininf.mUart4.mReceiveTimeOut = 10;
			mMaininf.mUart4.RxBuffer[mMaininf.mUart4.mReceiveSize ++] = vData;
			mMaininf.mUart4.mReceiveBCC = mMaininf.mUart4.mReceiveBCC ^ vData;
			break;
		case ST_MAIN_BCC :
			if(mMaininf.mUart4.mReceiveBCC == vData)
			{
				for(mMaininf.mUart4.mReceiveCont = 0;mMaininf.mUart4.mReceiveCont < (mMaininf.mUart4.RxBuffer[3] + 4);mMaininf.mUart4.mReceiveCont ++)
				{
					mMaininf.mUart4.ReceiveBuf[mMaininf.mUart4.mReceiveCont] = mMaininf.mUart4.RxBuffer[mMaininf.mUart4.mReceiveCont];
				}
				
				if((mMaininf.mUart4.ReceiveBuf[1] == 0) && (mMaininf.mUart4.ReceiveBuf[2] == 1))//i9
				{
					api_EEPROM_EarsePage(0x08020000);
					api_EEPROM_Write_Buffer(0x08020000,(uint16_t *)(mMaininf.mUart4.ReceiveBuf + 4),32);
					api_UART4_SendData(32,&mMaininf.mUart4.ReceiveBuf[4]);
				}
// 				else if((mMaininf.mUart4.ReceiveBuf[1] == 0) && (mMaininf.mUart4.ReceiveBuf[2] == 2))//i8
// 				{
// 					api_EEPROM_EarsePage(0x08020100);
// 					api_EEPROM_Write_Buffer(0x08020100,(uint16_t *)(mMaininf.mUart4.ReceiveBuf + 4),8);
// 				}
				else
				{
					mMaininf.mUart4.mReceiveFlag = 1;       //���յ�����
					mMaininf.mUart4.mReceiveTimeOut = 0;
				}
				
			}
			else mMaininf.mUart4.mReceiveTimeOut = 0;
			break;
		default :
			break;
	}
}

/*****************************************************************************
 * @name       :void api_UART5_SendData(u16 vCont, u8 *pData)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :send data
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void api_UART5_SendData(u16 vCont, u8 *pData)
{
	u16 iCont ;
	mMaininf.mUart5.mSendSize = vCont;
	for (iCont=0;iCont < vCont;iCont ++)
	{
		mMaininf.mUart5.TxBuffer[iCont] = *(pData + iCont);
	}
	//USART_ITConfig(UART5,USART_IT_RXNE,DISABLE);
	USART_ITConfig(UART5,USART_IT_TC,ENABLE);
}

/*****************************************************************************
 * @name       :void api_UART5_Display_SendCMDData(u8 mode,u8 cmd,u8 status)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :send data
 * @parameters :cmd
 * @retvalue   :None
******************************************************************************/
void api_UART5_Display_SendCMDData(u8 mode,u8 cmd,u8 status)
{
	mMaininf.mUart5.SendBuf[0] = 0x55;
	mMaininf.mUart5.SendBuf[1] = 0xAA;
	mMaininf.mUart5.SendBuf[2] = mode;
	mMaininf.mUart5.SendBuf[3] = cmd;
	mMaininf.mUart5.SendBuf[4] = status;
	mMaininf.mUart5.SendBuf[5] = mMaininf.mUart5.SendBuf[2] ^ mMaininf.mUart5.SendBuf[3] ^
								 mMaininf.mUart5.SendBuf[4];
	
	api_UART5_SendData(6,mMaininf.mUart5.SendBuf);
}

/*****************************************************************************
 * @name       :void api_ClearUART5ReceiveFlag(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :clear uart2 receive flag
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void api_ClearUART5ReceiveFlag(void)
{
	mMaininf.mUart5.mReceiveStep = ST_0x55;
	mMaininf.mUart5.mReceiveBCC = 0;
	mMaininf.mUart5.mReceiveSize = 0;
}

/*****************************************************************************
 * @name       :void api_UART5_ReceiveData(u8 vData)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :receive data
 * @parameters :data
 * @retvalue   :None
******************************************************************************/
// char dddd[50] = {0};
// char ffff =0 ;
void api_UART5_ReceiveData(u8 vData)
{
//	dddd[ffff++] = vData;
	if(mMaininf.mUart5.mReceiveTimeOut == 0)
	{
		api_ClearUART5ReceiveFlag();
	}
	switch(mMaininf.mUart5.mReceiveStep)
	{
		case ST_0x55 :
			if(vData == 0x55)
			{
				mMaininf.mUart5.mReceiveStep = ST_0xAA;
				mMaininf.mUart5.mReceiveTimeOut = 10;
			}
			else mMaininf.mUart5.mReceiveTimeOut = 0;
			break;
		case ST_0xAA :
			if(vData == 0xAA)
			{
				mMaininf.mUart5.mReceiveStep = ST_MODE;
				mMaininf.mUart5.mReceiveTimeOut = 10;
			}
			else mMaininf.mUart5.mReceiveTimeOut = 0;
			break;
		case ST_MODE :
			mMaininf.mUart5.mReceiveStep = ST_CMD;
			mMaininf.mUart5.mReceiveTimeOut = 10;
			mMaininf.mUart5.RxBuffer[mMaininf.mUart5.mReceiveSize ++] = vData;
			mMaininf.mUart5.mReceiveBCC = mMaininf.mUart5.mReceiveBCC ^ vData;
			break;
		case ST_CMD :
			mMaininf.mUart5.mReceiveStep = ST_STA;
			mMaininf.mUart5.mReceiveTimeOut = 10;
			mMaininf.mUart5.RxBuffer[mMaininf.mUart5.mReceiveSize ++] = vData;
			mMaininf.mUart5.mReceiveBCC = mMaininf.mUart5.mReceiveBCC ^ vData;
			break;
		case ST_STA :
			mMaininf.mUart5.mReceiveStep = ST_BCC;
			mMaininf.mUart5.mReceiveTimeOut = 10;
			mMaininf.mUart5.RxBuffer[mMaininf.mUart5.mReceiveSize ++] = vData;
			mMaininf.mUart5.mReceiveBCC = mMaininf.mUart5.mReceiveBCC ^ vData;
			break;
		case ST_BCC :
			if(mMaininf.mUart5.mReceiveBCC == vData)
			{
				for(mMaininf.mUart5.mReceiveCont = 0;mMaininf.mUart5.mReceiveCont < 3;mMaininf.mUart5.mReceiveCont ++)
				{
					mMaininf.mUart5.ReceiveBuf[mMaininf.mUart5.mReceiveCont] = mMaininf.mUart5.RxBuffer[mMaininf.mUart5.mReceiveCont];
				}
				
				mMaininf.mUart5.mReceiveFlag = 1;       //���յ�����
				mMaininf.mUart5.mReceiveTimeOut = 0;
				
			}
			else mMaininf.mUart5.mReceiveTimeOut = 0;
			break;
		default :
			break;
	}
}

/*****************************************************************************
 * @name       :void api_MachinePowerOn(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :�ϵ�
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void api_MachinePowerOn(void)
{
	mMaininf.mSystem.mPowerOnStartTime = api_GetCurrentSystemTime();
	
	/*while(1)
	{
		if(mMaininf.mUart5.mReceiveFlag == 1)            //    ���յ�����
		{
			mMaininf.mUart5.mReceiveFlag = 0;
			
			if((mMaininf.mUart5.ReceiveBuf[0] == 0) && (mMaininf.mUart5.ReceiveBuf[1] == 0) &&
			   (mMaininf.mUart5.ReceiveBuf[2] == 1))
			{
				api_UART5_Display_SendCMDData(0,0,1);
				mMaininf.mWork.mWorkInitFlag = 1;
				break;
			}
		}
		
		if(api_GetSystemTimePeriod(mMaininf.mSystem.mPowerOnStartTime) > 5000)
		{
			
			mMaininf.mWork.mWorkInitFlag = 0;
			break;
		}
	}*/
}

/*****************************************************************************
 * @name       :void api_Send_Signal(u8 mCmd)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :�����ź�
 * @parameters :mCmd ��
				0x01:���ر�   0x02:���ر�   0x03:������   0x04:������
				0x05:������   0x06:ǰ����   0x07:������   0x08:������
				0x09:������   0x0a:ǰ����   0x0b:������   0x0c:����ײ
				0x0d:����ײ   0x0e:�����   0x0f:�����   0x10:������
				0x11:������   0x12:BAT+     0x13:������   0x14:�ҳ����
				0x15:���м�� 0x16:���ⷢ�� 0x17:���ⷢ�� 0x18:ǰ�ⷢ��
 * @retvalue   :None
******************************************************************************/
void api_Send_Signal(u8 mCmd,u8 OpenFlag)
{
	switch(mCmd)
	{
		case 0x01 ://���ر�
			if(OpenFlag == 1)
			{
				PFout(11) = 0;
// 				TIM1_PWM_Configure(200,719);
// 				TIM_SetCompare2(TIM1,201);
				PBout(0) = 1;
			}
			else
			{
				PFout(11) = 1;
// 				TIM1_PWM_Configure(26,71);
// 				TIM_SetCompare2(TIM1,0);
				PBout(0) = 0;
			}
			break;
		case 0x02 ://���ر�
			if(OpenFlag == 1)
			{
				PBout(1) = 0;
// 				TIM1_PWM_Configure(200,719);
// 				TIM_SetCompare2(TIM1,201);
				PBout(0) = 1;
			}
			else
			{
				PBout(1) = 1;
// 				TIM1_PWM_Configure(26,71);
// 				TIM_SetCompare2(TIM1,0);
				PBout(0) = 0;
			}
			break;
		case 0x03 ://������
			if(OpenFlag == 1)
			{
				PFout(7) = 0;
				mMaininf.mWork.mWorkGuideSendFlag = 1;
				mMaininf.mWork.mWorkGuideSendStep = 0;
				mMaininf.mWork.mWorkGuideSendCont = 0;
				mMaininf.mWork.mWorkGuide[0].Flag = 1;
				TIM_Cmd(TIM4,ENABLE);
			}
			else
			{
				PFout(7) = 1;
				TIM_Cmd(TIM4,DISABLE);
				mMaininf.mWork.mWorkGuideSendFlag = 0;
				mMaininf.mWork.mWorkGuideSendStep = 0;
				mMaininf.mWork.mWorkGuideSendCont = 0;
				mMaininf.mWork.mWorkGuide[0].Flag = 0;
			}
			break;
		case 0x04 ://������
			if(OpenFlag == 1)
			{
				PFout(6) = 0;
				mMaininf.mWork.mWorkGuideSendFlag = 1;
				mMaininf.mWork.mWorkGuideSendStep = 0;
				mMaininf.mWork.mWorkGuideSendCont = 0;
				mMaininf.mWork.mWorkGuide[1].Flag = 1;
				TIM_Cmd(TIM4,ENABLE);
			}
			else
			{
				PFout(6) = 1;
				TIM_Cmd(TIM4,DISABLE);
				mMaininf.mWork.mWorkGuideSendFlag = 0;
				mMaininf.mWork.mWorkGuideSendStep = 0;
				mMaininf.mWork.mWorkGuideSendCont = 0;
				mMaininf.mWork.mWorkGuide[1].Flag = 0;
			}
			break;
		case 0x05 ://������
			if(OpenFlag == 1)
			{
				PFout(5) = 0;
				mMaininf.mWork.mWorkGuideSendFlag = 1;
				mMaininf.mWork.mWorkGuideSendStep = 0;
				mMaininf.mWork.mWorkGuideSendCont = 0;
				mMaininf.mWork.mWorkGuide[2].Flag = 1;
				TIM_Cmd(TIM4,ENABLE);
			}
			else
			{
				PFout(5) = 1;
				TIM_Cmd(TIM4,DISABLE);
				mMaininf.mWork.mWorkGuideSendFlag = 0;
				mMaininf.mWork.mWorkGuideSendStep = 0;
				mMaininf.mWork.mWorkGuideSendCont = 0;
				mMaininf.mWork.mWorkGuide[2].Flag = 0;
			}
			break;
		case 0x06 ://ǰ����
			if(OpenFlag == 1)
			{
				PFout(4) = 0;
				mMaininf.mWork.mWorkGuideSendFlag = 1;
				mMaininf.mWork.mWorkGuideSendStep = 0;
				mMaininf.mWork.mWorkGuideSendCont = 0;
				mMaininf.mWork.mWorkGuide[3].Flag = 1;
				TIM_Cmd(TIM4,ENABLE);
			}
			else
			{
				PFout(4) = 1;
				TIM_Cmd(TIM4,DISABLE);
				mMaininf.mWork.mWorkGuideSendFlag = 0;
				mMaininf.mWork.mWorkGuideSendStep = 0;
				mMaininf.mWork.mWorkGuideSendCont = 0;
				mMaininf.mWork.mWorkGuide[3].Flag = 0;
			}
			break;
		case 0x07 ://������
			if(OpenFlag == 1)
			{
				PFout(3) = 0;
				mMaininf.mWork.mWorkGuideSendFlag = 1;
				mMaininf.mWork.mWorkGuideSendStep = 0;
				mMaininf.mWork.mWorkGuideSendCont = 0;
				mMaininf.mWork.mWorkGuide[4].Flag = 1;
				TIM_Cmd(TIM4,ENABLE);
			}
			else
			{
				PFout(3) = 1;
				TIM_Cmd(TIM4,DISABLE);
				mMaininf.mWork.mWorkGuideSendFlag = 0;
				mMaininf.mWork.mWorkGuideSendStep = 0;
				mMaininf.mWork.mWorkGuideSendCont = 0;
				mMaininf.mWork.mWorkGuide[4].Flag = 0;
			}
			break;
		case 0x08 ://������
			if(OpenFlag == 1)
			{
				PCout(2) = 0;
// 				TIM1_PWM_Configure(200,719);
// 				TIM_SetCompare2(TIM1,175);
// 				PBout(0) = 1;
				mMaininf.mWork.mWorkDropSendCont = 0;
				mMaininf.mWork.mWorkDropSendFlag = 1;
				TIM_Cmd(TIM3,ENABLE);
			}
			else
			{
				PCout(2) = 1;
// 				TIM1_PWM_Configure(26,71);
// 				TIM_SetCompare2(TIM1,0);
//				PBout(0) = 0;
				TIM_Cmd(TIM3,DISABLE);
				mMaininf.mWork.mWorkDropSendFlag = 0;
				mMaininf.mWork.mWorkDropSendCont = 0;
			}
			break;
		case 0x09 ://������
			if(OpenFlag == 1)
			{
				PCout(1) = 0;
// 				TIM1_PWM_Configure(200,719);
// 				TIM_SetCompare2(TIM1,175);
				//PBout(0) = 1;
				mMaininf.mWork.mWorkDropSendCont = 0;
				mMaininf.mWork.mWorkDropSendFlag = 1;
				TIM_Cmd(TIM3,ENABLE);
			}
			else
			{
				PCout(1) = 1;
// 				TIM1_PWM_Configure(26,71);
// 				TIM_SetCompare2(TIM1,0);
				//PBout(0) = 0;
				TIM_Cmd(TIM3,DISABLE);
				mMaininf.mWork.mWorkDropSendFlag = 0;
				mMaininf.mWork.mWorkDropSendCont = 0;
			}
			break;
		case 0x0a ://ǰ����
			if(OpenFlag == 1)
			{
				PCout(0) = 0;
// 				TIM1_PWM_Configure(200,719);
// 				TIM_SetCompare2(TIM1,175);
				//PBout(0) = 1;
				mMaininf.mWork.mWorkDropSendCont = 0;
				mMaininf.mWork.mWorkDropSendFlag = 1;
				TIM_Cmd(TIM3,ENABLE);
			}
			else
			{
				PCout(0) = 1;
// 				TIM1_PWM_Configure(26,71);
// 				TIM_SetCompare2(TIM1,0);
				//PBout(0) = 0;
				TIM_Cmd(TIM3,DISABLE);
				mMaininf.mWork.mWorkDropSendFlag = 0;
				mMaininf.mWork.mWorkDropSendCont = 0;
				
			}
			break;
		case 0x0b ://������
			if(OpenFlag == 1)
			{
				PFout(10) = 0;
// 				TIM1_PWM_Configure(200,719);
// 				TIM_SetCompare2(TIM1,175);
				//PBout(0) = 1;
				mMaininf.mWork.mWorkDropSendCont = 0;
				mMaininf.mWork.mWorkDropSendFlag = 1;
				TIM_Cmd(TIM3,ENABLE);
			}
			else
			{
				PFout(10) = 1;
// 				TIM1_PWM_Configure(26,71);
// 				TIM_SetCompare2(TIM1,0);
				//PBout(0) = 0;
				TIM_Cmd(TIM3,DISABLE);
				mMaininf.mWork.mWorkDropSendFlag = 0;
				mMaininf.mWork.mWorkDropSendCont = 0;
			}
			break;
		case 0x0c ://����ײ
			if(OpenFlag == 1)
			{
				PEout(6) = 0;
			}
			else
			{
				PEout(6) = 1;
			}
			break;
		case 0x0d ://����ײ
			if(OpenFlag == 1)
			{
				PEout(5) = 0;
			}
			else
			{
				PEout(5) = 1;
			}
			break;
		case 0x0e ://�����
			if(OpenFlag == 1)
			{
				PEout(4) = 0;
			}
			else
			{
				PEout(4) = 1;
			}
			break;
		case 0x0f ://�����
			if(OpenFlag == 1)
			{
				PEout(3) = 0;
			}
			else
			{
				PEout(3) = 1;
			}
			break;
		case 0x10 ://������
			if(OpenFlag == 1)
			{
				PFout(2) = 0;
// 				TIM1_PWM_Configure(100,719);
// 				TIM_SetCompare2(TIM1,20);
				mMaininf.mWork.mWorkCodeSendFlag = 1;
				TIM_Cmd(TIM3,ENABLE);
			}
			else
			{
				TIM_Cmd(TIM3,DISABLE);
				PFout(2) = 1;
// 				TIM1_PWM_Configure(26,71);
// 				TIM_SetCompare2(TIM1,0);
				mMaininf.mWork.mWorkCodeSendFlag = 0;
				mMaininf.mWork.mWorkCodeSendCont = 0;
				PBout(0) = 0;
			}
			break;
		case 0x11 ://������
			if(OpenFlag == 1)
			{
				//PFout(1) = 0;//PF1-->PC13
				PCout(13) = 0;
				mMaininf.mWork.mWorkCodeSendFlag = 1;
				TIM_Cmd(TIM3,ENABLE);
			}
			else
			{
				TIM_Cmd(TIM3,DISABLE);
				PCout(13) = 1;
				mMaininf.mWork.mWorkCodeSendFlag = 0;
				mMaininf.mWork.mWorkCodeSendCont = 0;
				PBout(0) = 0;
			}
			break;
		case 0x12 ://BAT+
			if(OpenFlag == 1)
			{
				//PEout(2) = 0;
				//PEout(2) = 1;
				PBout(9) = 1;
			}
			else
			{
				//PEout(2) = 1;
				//PEout(2) = 0;
				PBout(9) = 0;
			}
			break;
		case 0x13 ://������
			if(OpenFlag == 1)
			{
				PEout(1) = 0;
			}
			else
			{
				PEout(1) = 1;
			}
			break;
		case 0x14 ://�ҳ����
			if(OpenFlag == 1)
			{
				PFout(8) = 0;
				PBout(0) = 1;
			}
			else
			{
				PFout(8) = 1;
				PBout(0) = 0;
			}
			break;
		case 0x15 ://���м��
			if(OpenFlag == 1)
			{
				PEout(0) = 0;
			}
			else
			{
				PEout(0) = 1;
			}
			break;
		case 0x16 ://���ⷢ��
			if(OpenFlag == 1)
			{
				PCout(5) = 0;
// 				TIM1_PWM_Configure(200,719);
// 				TIM_SetCompare2(TIM1,150);
				PBout(0) = 1;
			}
			else
			{
				PCout(5) = 1;
// 				TIM1_PWM_Configure(26,71);
// 				TIM_SetCompare2(TIM1,0);
				PBout(0) = 0;
			}
			break;
		case 0x17 ://���ⷢ��
			if(OpenFlag == 1)
			{
				PCout(4) = 0;
// 				TIM1_PWM_Configure(200,719);
// 				TIM_SetCompare2(TIM1,150);
				PBout(0) = 1;
			}
			else
			{
				PCout(4) = 1;
// 				TIM1_PWM_Configure(26,71);
// 				TIM_SetCompare2(TIM1,0);
				PBout(0) = 0;
			}
			break;
		case 0x18 ://ǰ�ⷢ��
			if(OpenFlag == 1)
			{
				PCout(3) = 0;
// 				TIM1_PWM_Configure(200,719);
// 				TIM_SetCompare2(TIM1,150);
				PBout(0) = 1;
			}
			else
			{
				PCout(3) = 1;
// 				TIM1_PWM_Configure(26,71);
// 				TIM_SetCompare2(TIM1,0);
				PBout(0) = 0;
			}
			break;
		default :
			break;
	}
}

/*****************************************************************************
 * @name       :void api_Control_Motor(u8 mCmd,u8 OpenFlag)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :���Ƽ̵���������
 * @parameters :0:�����Ǽ̵���  1������1����  2������2����  3������3����
				4����ˢ�̵���   5���������   6���ŵ�̵��� 7�����̵���
				8��ˮ��̵���
 * @retvalue   :None
******************************************************************************/
void api_Control_Motor(u8 mCmd,u8 OpenFlag)
{
	switch(mCmd)
	{
		case 0://�����Ǽ̵���
			if(OpenFlag == 1)
			{
				PDout(7) = 1;
			}
			else
			{
				PDout(7) = 0;
			}
			break;
		case 1://����1����
			if(OpenFlag == 1)
			{
				PGout(15) = 1;
			}
			else
			{
				PGout(15) = 0;
			}
			break;
		case 2://����2����
			if(OpenFlag == 1)
			{
				PGout(14) = 1;
			}
			else
			{
				PGout(14) = 0;
			}
			break;
		case 3://����3����
			if(OpenFlag == 1)
			{
				PGout(13) = 1;
			}
			else
			{
				PGout(13) = 0;
			}
			break;
		case 4://��ˢ�̵���
			if(OpenFlag == 1)
			{
				PDout(4) = 1;
			}
			else
			{
				PDout(4) = 0;
			}
			break;
		case 5://�������
			if(OpenFlag == 1)
			{
				PDout(3) = 1;
			}
			else
			{
				PDout(3) = 0;
			}
			break;
		case 6://�ŵ�̵���
			if(OpenFlag == 1)
			{
				PDout(1) = 1;
			}
			else
			{
				PDout(1) = 0;
			}
			break;
		case 7://���̵���
			if(OpenFlag == 1)
			{
				PAout(11) = 1;
			}
			else
			{
				PAout(11) = 0;
			}
			break;
		case 8://ˮ��̵���
			if(OpenFlag == 1)
			{
				PDout(0) = 1;
			}
			else
			{
				PDout(0) = 0;
			}
			break;
		default :
			break;
	}
}

/*****************************************************************************
 * @name       :u8 api_ReadGpioInputStauts(GPIO_TypeDef* GPIOx, 
											uint16_t GPIO_Pin,uint8_t Cont)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :GPIOx��GPIO
				GPIO_Pin��Pin��
				val:����ƽֵ
				Cont��������
 * @parameters :None
 * @retvalue   :0:���ʧ��   1�����ɹ�
******************************************************************************/
//u8 iiiiiii;
u8 api_ReadGpioInputStauts(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 Val,uint8_t Cont)
{
	uint8_t mCont;
	uint8_t mNum = 0;
	
// 	iiiiiii = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15);
// 	iiiiiii = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
	
	for(mCont = 0;mCont < Cont;mCont ++)
	{
		//mNum = mNum + GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == Val)
		{
			mNum ++;
		}
		vTaskDelay(10);
	}
	
	mNum = mNum / Cont;
	
	if(mNum == 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*****************************************************************************
 * @name       :u8 api_ReadGpioInputStauts(GPIO_TypeDef* GPIOx, 
											uint16_t GPIO_Pin,uint8_t Cont)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :GPIOx��GPIO
				GPIO_Pin��Pin��
				val:����ƽֵ
				Cont��������
 * @parameters :None
 * @retvalue   :0:���ʧ��   1�����ɹ�
******************************************************************************/
//u8 iiiiiii;
u8 api_ReadWheelGpioInputStauts(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 Val,uint8_t Cont)
{
	uint8_t mCont;
	uint8_t mNum = 0;
	
// 	iiiiiii = GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_15);
// 	iiiiiii = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
	
	for(mCont = 0;mCont < Cont;mCont ++)
	{
		//mNum = mNum + GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
		if(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == Val)
		{
			mNum ++;
		}
		vTaskDelay(1);
	}
	
//	mNum = mNum / Cont;
	
	if(mNum >= 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*****************************************************************************
 * @name       :u8 api_Check_PWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 cycle,u8 differ)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :GPIOx��GPIO
				GPIO_Pin��Pin��
				cycle:����
				differ����Χ
 * @parameters :None
 * @retvalue   :0:���ʧ��   1�����ɹ�
******************************************************************************/
u16 mb;
u8 mc = 0;
u8 ma[4];
u8 api_Check_PWM_One(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 cycle,u8 differ)
{
	u8 mGpioPinStatus;
	u32 mTimeOut = 0;
	u32 mCont = 0;
	
	taskENTER_CRITICAL();
	TIM_Cmd(TIM3,ENABLE);
	mGpioPinStatus = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
	while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mGpioPinStatus)
	{
		if(++ mTimeOut > 0xfffff)
		{
			break;
		}
	}
//	iiiiiii = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
	mMaininf.mSystem.mSystem200usTick = 0;
	while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) != mGpioPinStatus)
	{
		if(++ mTimeOut > 0xfffff)
		{
			break;
		}
	}
//	iiiiiii = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
	mTimeOut = 0;
	while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mGpioPinStatus)
	{
		if(++ mTimeOut > 0xfffff)
		{
			break;
		}
	}
	mCont = mMaininf.mSystem.mSystem200usTick;
	TIM_Cmd(TIM3,DISABLE);
	
	taskEXIT_CRITICAL();
	
//	mb = mCont;
//	ma[0] = 0xbb;
//	ma[1] = (mc + 1);
//	ma[2] = mb >> 8;
//	ma[3] = mb & 0xff;
//	
//	api_UART4_SendData(4,&ma[0]);
//	vTaskDelay(200);
	
	if((mCont >= (cycle - differ)) && (mCont <= (cycle + differ)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*****************************************************************************
 * @name       :u8 api_Check_PWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 cycle,u8 differ)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :GPIOx��GPIO
				GPIO_Pin��Pin��
				cycle:����
				differ����Χ
 * @parameters :None
 * @retvalue   :0:���ʧ��   1�����ɹ�
******************************************************************************/
u8 api_Check_PWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 cycle,u8 differ,u8 count)
{
	u8 mCont = 0;
	u8 mStatus = 0;
	
	do
	{
		if(++mCont > count)
		{
			//return;
			break;
		}
		
		if(api_Check_PWM_One(GPIOx,GPIO_Pin,cycle,differ) == 1)
		{
			mStatus = 1;
			break;
		}
		
		vTaskDelay(100);
	}while(mStatus == 0);
	
	return mStatus;
}

/*****************************************************************************
 * @name       :u8 api_Check_Wheel_PWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 cycle,u8 differ)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :GPIOx��GPIO
				GPIO_Pin��Pin��
				cycle:����
				differ����Χ
 * @parameters :None
 * @retvalue   :0:���ʧ��   1�����ɹ�
******************************************************************************/
u8 api_Check_Wheel_PWM(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin,u8 cycle,u8 differ)
{
	u8 mGpioPinStatus;
	u32 mTimeOut = 0;
	u32 mCont = 0;
	
	taskENTER_CRITICAL();
	TIM_Cmd(TIM4,ENABLE);
	mGpioPinStatus = GPIO_ReadInputDataBit(GPIOx,GPIO_Pin);
	while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mGpioPinStatus)
	{
		if(++ mTimeOut > 0xfffff)
		{
			break;
		}
	}
	
	mMaininf.mSystem.mSystem10usTick = 0;
	while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) != mGpioPinStatus)
	{
		if(++ mTimeOut > 0xfffff)
		{
			break;
		}
	}
	
	mTimeOut = 0;
	while(GPIO_ReadInputDataBit(GPIOx,GPIO_Pin) == mGpioPinStatus)
	{
		if(++ mTimeOut > 0xfffff)
		{
			break;
		}
	}
	mCont = mMaininf.mSystem.mSystem10usTick;
	TIM_Cmd(TIM4,DISABLE);
	
	taskEXIT_CRITICAL();
	
	
// 	mb = mCont;
// 	ma[0] = 0xbb;
// 	ma[1] = (mc + 1);
// 	ma[2] = mb >> 8;
// 	ma[3] = mb & 0xff;
// 	
// 	api_UART4_SendData(4,&ma[0]);
// 	vTaskDelay(200);
	
	if((mCont >= (cycle - differ)) && (mCont <= (cycle + differ)))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

/*****************************************************************************
 * @name       :u8 api_Test_ADC_Status(__IO uint16_t *adcval,uint16_t 
				detectval,uint16_t diffval)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :adcval���������
				detectval���Ƚ�ֵ
				diffval��ƫ��
 * @parameters :None
 * @retvalue   :0:���ʧ��   1�����ɹ�
******************************************************************************/
// u16 mb;
// u8 mc = 0;
// u8 ma[4];
u8 api_Test_ADC(__IO uint16_t *adcval,uint16_t detectval,uint16_t diffval)
{
	u8 mCont;
	uint16_t mNum = 0;
// 	if(detectval >= 25)
// 	{
// 		float mValL = ((57.835 - 5.2017*(detectval - diffval)) * 4095) / 33;
// 		float mValH = ((57.835 - 5.2017*(detectval + diffval)) * 4095) / 33;
// 	}
// 	else
// 	{
// 		float mValL = ((24.26 + 7.24*(detectval - diffval)) * 4095) / 33;
// 		float mValH = ((24.26 + 7.24*(detectval + diffval)) * 4095) / 33;
// 	}
// 	mb = *adcval;
// 	ma[0] = 0xbb;
// 	ma[1] = (mc + 1);
// 	ma[2] = mb >> 8;
// 	ma[3] = mb & 0xff;
	
// 	api_UART4_SendData(4,&ma[0]);
// 	vTaskDelay(200);
	
	for(mCont = 0;mCont < 5;mCont ++)
	{
		mNum = mNum + (*adcval & 0x0fff);
		vTaskDelay(10);
	}
	
	mNum = mNum / 5;
	
	if((mNum > (detectval - diffval)) && (mNum < (detectval + diffval)))
	{
		return 1;
	}
	
	return 0;
}

/*****************************************************************************
 * @name       :void api_Guide_Send(u8 mStatus)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :������������
 * @parameters :����״̬
 * @retvalue   :None
******************************************************************************/
void api_Guide_Send(u8 mStatus)
{
	if(mMaininf.mWork.mWorkGuide[0].Flag == 1) PBout(0) = mStatus;//��
	if(mMaininf.mWork.mWorkGuide[1].Flag == 1) PBout(0) = mStatus;//��
	if(mMaininf.mWork.mWorkGuide[2].Flag == 1) PBout(0) = mStatus;//��
	if(mMaininf.mWork.mWorkGuide[3].Flag == 1) PBout(0) = mStatus;//ǰ
	if(mMaininf.mWork.mWorkGuide[4].Flag == 1) PBout(0) = mStatus;//��
}

/*****************************************************************************
 * @name       :u8 api_Check_MainBoard_Mode(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :����Ƿ�ת����������
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
u8 api_Check_MainBoard_Mode(void)
{
	return ((mMaininf.mWork.mWorkI8I9StatusFlag == mMaininf.mWork.mWorkOldI8I9StatusFlag) ? 1 : 0);
}

/*****************************************************************************
 * @name       :char NumToChar(u16 num)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :�ж��ź�״̬
 * @parameters :��Ӧ
 * @retvalue   :None
******************************************************************************/
char NumToChar(u16 num)
{
	char temp;
	
	switch(num)
	{
		case 0 :
			temp = '0';
			break;
		case 1 :
			temp = '1';
			break;
		case 2 :
			temp = '2';
			break;
		case 3 :
			temp = '3';
			break;
		case 4 :
			temp = '4';
			break;
		case 5 :
			temp = '5';
			break;
		case 6 :
			temp = '6';
			break;
		case 7 :
			temp = '7';
			break;
		case 8 :
			temp = '8';
			break;
		case 9 :
			temp = '9';
			break;
		default :
			break;
	}
	
	return temp;
}


/*****************************************************************************
 * @name       :void api_ShortToStr(u8* str,u16 data)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :�ж��ź�״̬
 * @parameters :��Ӧ
 * @retvalue   :None
******************************************************************************/
void api_ShortToStr(u8* str,s16 data)
{
	//s16 sss = 0 - data;
	s16 sss = data;
	
	u16 tempcont;
	
	tempcont = sss;
	*(str + 4) = NumToChar(tempcont % 10);
	tempcont = tempcont / 10;
	*(str + 3) = NumToChar(tempcont % 10);
	tempcont = tempcont / 10;
	*(str + 2) = NumToChar(tempcont % 10);
	tempcont = tempcont / 10;
	*(str + 1) = NumToChar(tempcont % 10);
	tempcont = tempcont / 10;
	*str = NumToChar(tempcont % 10);
}


