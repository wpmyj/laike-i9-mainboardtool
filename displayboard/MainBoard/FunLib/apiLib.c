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
//#include "font.h"
#include "gui.h"
#include "lcd_driver.h"
#include "display.h"

#include "apiLib.h"

#include "TK_TimerController.h"


/* Variable --------------------------------------------------------------------*/

/* Function --------------------------------------------------------------------*/
/*  ʱ����ؿ��ƿ�                                                  */
u32 api_GetSystemTimePeriod(u32 StartTime);
u32 api_GetCurrentSystemTime(void);
void api_SendCMDData(u8 mode,u8 cmd,u8 status);
void api_UART1_ReceiveData(u8 vData);
void api_MachinePowerOn(void);






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
	//USART_ITConfig(USART1,USART_IT_RXNE,DISABLE);
	USART_ITConfig(USART1,USART_IT_TC,ENABLE);
}

/*****************************************************************************
 * @name       :void api_SendCMDData(u8 mode,u8 cmd,u8 status)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :send data
 * @parameters :cmd
 * @retvalue   :None
******************************************************************************/
void api_SendCMDData(u8 mode,u8 cmd,u8 status)
{
	mMaininf.mUart1.SendBuf[0] = 0x55;
	mMaininf.mUart1.SendBuf[1] = 0xAA;
	mMaininf.mUart1.SendBuf[2] = mode;
	mMaininf.mUart1.SendBuf[3] = cmd;
	mMaininf.mUart1.SendBuf[4] = status;
	mMaininf.mUart1.SendBuf[5] = mMaininf.mUart1.SendBuf[2] ^ mMaininf.mUart1.SendBuf[3] ^
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
	mMaininf.mUart1.mReceiveStep = ST_0x55;
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
		case ST_0x55 :
			if(vData == 0x55)
			{
				mMaininf.mUart1.mReceiveStep = ST_0xAA;
				mMaininf.mUart1.mReceiveTimeOut = 10;
			}
			else mMaininf.mUart1.mReceiveTimeOut = 0;
			break;
		case ST_0xAA :
			if(vData == 0xAA)
			{
				mMaininf.mUart1.mReceiveStep = ST_MODE;
				mMaininf.mUart1.mReceiveTimeOut = 10;
			}
			else mMaininf.mUart1.mReceiveTimeOut = 0;
			break;
		case ST_MODE :
			mMaininf.mUart1.mReceiveStep = ST_CMD;
			mMaininf.mUart1.mReceiveTimeOut = 10;
			mMaininf.mUart1.RxBuffer[mMaininf.mUart1.mReceiveSize ++] = vData;
			mMaininf.mUart1.mReceiveBCC = mMaininf.mUart1.mReceiveBCC ^ vData;
			break;
		case ST_CMD :
			mMaininf.mUart1.mReceiveStep = ST_STA;
			mMaininf.mUart1.mReceiveTimeOut = 10;
			mMaininf.mUart1.RxBuffer[mMaininf.mUart1.mReceiveSize ++] = vData;
			mMaininf.mUart1.mReceiveBCC = mMaininf.mUart1.mReceiveBCC ^ vData;
			break;
		case ST_STA :
			mMaininf.mUart1.mReceiveStep = ST_BCC;
			mMaininf.mUart1.mReceiveTimeOut = 10;
			mMaininf.mUart1.RxBuffer[mMaininf.mUart1.mReceiveSize ++] = vData;
			mMaininf.mUart1.mReceiveBCC = mMaininf.mUart1.mReceiveBCC ^ vData;
			break;
		case ST_BCC :
			if(mMaininf.mUart1.mReceiveBCC == vData)
			{
				for(mMaininf.mUart1.mReceiveCont = 0;mMaininf.mUart1.mReceiveCont < 3;mMaininf.mUart1.mReceiveCont ++)
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
 * @name       :void api_MachinePowerOn(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :�ϵ�
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
extern u8 mpass[4];
void api_MachinePowerOn(void)
{
	DrawTestPage("I9���幤װ");//���幤װ
	LCD_Fill(0,40,lcddev.width,lcddev.height-20,GRAY0);
	
	Gui_DrawFont_GBK24(140,130,BLUE,GRAY0,"��ʼ��...             ");
	
// 	DisplayButtonUp(305,215,423,278); //x1,y1,x2,y2
// 	Gui_DrawFont_GBK24(316,235,BLACK,GRAY0,"��ʼ����");
// 	
// 	LCD_Clear_Area(305,215,423,278,GRAY0);
	
	mMaininf.mSystem.mPowerOnStartTime = api_GetCurrentSystemTime();
	
	mMaininf.mSystem.mReadUartStatusStartTime = api_GetCurrentSystemTime();
	api_SendCMDData(0,1,0);
	
	while(1)
	{
		if(api_GetSystemTimePeriod(mMaininf.mSystem.mReadUartStatusStartTime) > 500)
		{
			api_SendCMDData(0,1,0);
			mMaininf.mSystem.mReadUartStatusStartTime = api_GetCurrentSystemTime();
			
		}
		
		#ifndef zbq_Debug
		if(mMaininf.mUart1.mReceiveFlag == 1)            //    ���յ�����
		#else
		if(1)
		#endif
		{
			mMaininf.mUart1.mReceiveFlag = 0;
			
			#ifndef zbq_Debug
			if((mMaininf.mUart1.ReceiveBuf[0] == 0) && (mMaininf.mUart1.ReceiveBuf[1] == 1) &&
			   (mMaininf.mUart1.ReceiveBuf[2] == 1))
			#else
			if(1)
			#endif
			{
				Gui_DrawFont_GBK24(140,130,BLUE,GRAY0,"��ʼ��OK              ");
				
// 				DisplayButtonUp(315,238,413,278); //x1,y1,x2,y2
// 				Gui_DrawFont_GBK24(316,245,LIGHTGREEN,GRAY0,"��ʼ����");
				
// 				DisplayButtonUp(305,215,423,278); //x1,y1,x2,y2//zbq
// 				Gui_DrawFont_GBK24(316,235,BLACK,GRAY0,"��ʼ���");
//				Gui_DrawFont_GBK128(116,78,GREEN,GRAY0,mpass);
				
				mMaininf.mWork.mWorkInitFlag = 1;
				break;
			}
		}
		
		if(api_GetSystemTimePeriod(mMaininf.mSystem.mPowerOnStartTime) > 5000)
		{
			Gui_DrawFont_GBK24(140,130,BLUE,GRAY0,"��ʾ������            ");
			
			mMaininf.mWork.mWorkInitFlag = 0;
			break;
		}
	}
}





