/****************************************************************************************************/
/*			@FileName		:	TK_TIMERCONTROLLER.c											  	*/
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

/* FreeRTOS --------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "FreeRTOSConfig.h"
//#include "death.h"
#include "semphr.h"
#include "projdefs.h"

/* Project ---------------------------------------------------------------------*/
#include "maindef.h"
#include "bsp.h"
#include "gpioredef.h"

#include "apiLib.h"

#include "TK_TimerController.h"


/* Variable --------------------------------------------------------------------*/
u8 smgduan[16]={0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07,
             0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

/* Function --------------------------------------------------------------------*/
void TK_TimerController( void *pvParameters );
void TimerDetection(void);


/*****************************************************************************
 * @name       :void TK_TimerController( void *pvParameters )
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :时间控制任务
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TK_TimerController( void *pvParameters )
{
	u8 mDelay;
	u32 mTickTime;
	
	for(;;)
	{
		/*    获取当前时刻     */
		mTickTime = api_GetCurrentSystemTime();
		
		/*    定时复位看门狗   */
		IWDG_ReloadCounter();
		
		/*    定时检测外设     */
		TimerDetection();
		
		/*    获取运行时间     */
		if(api_GetSystemTimePeriod(mTickTime) < TIMEOUT_50ms) mDelay = 50 - api_GetSystemTimePeriod(mTickTime);
		else mDelay = TIMEOUT_0ms;
		
		/*    进行任务延时     */
		vTaskDelay(mDelay);
	}
}



/*****************************************************************************
 * @name       :void Key_Status_Analyze(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :测试模式解析
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Key_Status_Analyze(void)
{
	mMaininf.mWork.mWorkI8I9StatusFlag = (mMaininf.mWork.mWorkI9KeyPressFlag << 1) | mMaininf.mWork.mWorkI8KeyPressFlag;
}

/*****************************************************************************
 * @name       :void TimerDetection(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :定时检测按键
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TimerDetection(void)
{
 	if(GPIO_ReadInputDataBit(GPIOF,GPIO_Pin_9) == 0)//按键按下进行测试    测试按键
	{
		if(mMaininf.mWork.mWorkKeyPressFlag == 0)
		{
			if((mMaininf.mWork.mWorkOldI8I9StatusFlag == 1) || (mMaininf.mWork.mWorkOldI8I9StatusFlag == 2))
			{
				mMaininf.mWork.mWorkKeyCont ++;
				if(mMaininf.mWork.mWorkKeyCont > 10)
				{
					mMaininf.mWork.mWorkKeyCont = 10;
					
					mMaininf.mWork.mWorkKeyPressFlag = 1;
					
				}
			}
		}
	}
	else
	{
		mMaininf.mWork.mWorkKeyCont = 0;
	}
// 	else
// 	{
// 		if(mMaininf.mWork.mWorkKeyPressFlag1 == 1)
// 		{
// 			mMaininf.mWork.mWorkKeyPressFlag = 1;
// 		}
// 		mMaininf.mWork.mWorkKeyCont = 0;
// 	}

 	if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_3) == 1)//按键按下进入相应模式  i8
	{
		if(mMaininf.mWork.mWorkI8KeyPressFlag == 0)
		{
			mMaininf.mWork.mWorkI8KeyCont ++;
			if(mMaininf.mWork.mWorkI8KeyCont > 10)
			{
				mMaininf.mWork.mWorkI8KeyPressFlag = 1;
			}
		}
		mMaininf.mWork.mWorkI8KeyCont1 = 0;
	}
	else
	{
		if(mMaininf.mWork.mWorkI8KeyPressFlag == 1)
		{
			mMaininf.mWork.mWorkI8KeyCont1 ++;
			if(mMaininf.mWork.mWorkI8KeyCont1 > 10)
			{
				mMaininf.mWork.mWorkI8KeyPressFlag = 0;
			}
		}
		mMaininf.mWork.mWorkI8KeyCont = 0;
	}
	
	if(GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_2) == 1)//按键按下进入相应模式  i9
	{
		if(mMaininf.mWork.mWorkI9KeyPressFlag == 0)
		{
			mMaininf.mWork.mWorkI9KeyCont ++;
			if(mMaininf.mWork.mWorkI9KeyCont > 10)
			{
				mMaininf.mWork.mWorkI9KeyPressFlag = 1;
			}
		}
		mMaininf.mWork.mWorkI9KeyCont1 = 0;
	}
	else
	{
		if(mMaininf.mWork.mWorkI9KeyPressFlag == 1)
		{
			mMaininf.mWork.mWorkI9KeyCont1 ++;
			if(mMaininf.mWork.mWorkI9KeyCont1 > 10)
			{
				mMaininf.mWork.mWorkI9KeyPressFlag = 0;
			}
		}
		mMaininf.mWork.mWorkI9KeyCont = 0;
	}
	
	Key_Status_Analyze();
}






