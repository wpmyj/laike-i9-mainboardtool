/****************************************************************************************************/
/*			@FileName		:	TK_DISPLAYCONTROLLER.c															  	*/
/*			@Author			:	zhengbaiqiu															*/
/*			@Version		:	v1.0																*/
/*			@Date			:	2019.11.12  														*/
/****************************************************************************************************/


/* Includes --------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Project ---------------------------------------------------------------------*/
#include "apiLib.h"
#include "lcd_driver.h"	
#include "touch.h"
#include "gui.h"
#include "Picture.h"
#include "display.h"
#include "TK_DisplayController.h"

/* Variable --------------------------------------------------------------------*/
/* Function --------------------------------------------------------------------*/
void TK_DisplayController( void *pvParameters );







/*****************************************************************************
 * @name       :void TK_DisplayController( void *pvParameters )
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :显示任务
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TK_DisplayController( void *pvParameters )
{
//	disp_Pic(30,30,gImage_ad);
	api_MachinePowerOn();
	
	for(;;)
	{
// 		mMaininf.mSystem.mTestStartTime = api_GetCurrentSystemTime();
// 		Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"定位摄像头供电");
// 		mMaininf.mSystem.mTestStartTime = api_GetCurrentSystemTime();
		IWDG_ReloadCounter();
//		Read_Touch();
		Test_Display();
	}
}





