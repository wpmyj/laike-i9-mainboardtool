/****************************************************************************************************/
/*			@FileName		:	MAIN.c															  	*/
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
#include "touch.h"
#include "gui.h"
#include "apiLib.h"
//#include "Picture.h"
#include "display.h"

#include "TK_TimerController.h"
#include "TK_DisplayController.h"



/* Variable --------------------------------------------------------------------*/
_ST_MAINMANAGER mMaininf;
//ST_MAINMANAGER mMainManager;
//SemaphoreHandle_t InitSD_Semaphore;
TaskHandle_t xTaskTimer,xTaskDisplay;

/* Function --------------------------------------------------------------------*/
void vCreateQueueAndSemphr(void);
void vCreateTaskManager(void);





int main(void)
{
	prvSetupHardware();
	
// 	api_MachinePowerOn();
// 	while(1)
// 	{
// 		IWDG_ReloadCounter();
// 		Read_Touch();
// 		Test_Display();
// 	}
	
/*     Create QueueAndSemphr.    */
	vCreateQueueAndSemphr();
	
/*     Create Task.              */
	vCreateTaskManager();

/*     Start the scheduler.      */
	vTaskStartScheduler();

	return 0;
}


void vCreateQueueAndSemphr(void)
{	
// 	Burn_Semaphore=xSemaphoreCreateBinary();
// 	Version_Semaphore = xSemaphoreCreateBinary();
// 	if(Burn_Semaphore == NULL)
// 	{
// 		/*��ջ�ڴ治�㣬������Ӧ��Ӧ����*/
// //		iossf = 0;
// 	}
// 	{
// 		/*�ź��������ɹ���ǰΪ�ź�����������������API����xSemaphoreTake()����ȡ�ź�����Ȼʧ�ܣ���Ϊ�������ź����ĳ�ʼֵΪ��*/
// //		iossf = 1;
// 	}
}

void vCreateTaskManager(void)
{
	xTaskCreate( TK_TimerController, "TimerTask", mainTIMER_TASK_STACK_SIZE, NULL, mainTIMER_TASK_PRIORITY, &xTaskTimer );
	xTaskCreate( TK_DisplayController, "DisplayTask", mainDISPLAY_TASK_STACK_SIZE, NULL, mainDISPLAY_TASK_PRIORITY, &xTaskDisplay );
//	xTaskCreate( TK_CheckKeyTask, "CheckKeyTask", mainCHECKKEY_TASK_STACK_SIZE, NULL, mainCHECKKEY_TASK_PRIORITY, &xTaskKeyCheck );
//	xTaskCreate( TK_CheckSDTask, "CheckSDTask", mainCHECKSD_TASK_STACK_SIZE, NULL, mainCHECKSD_TASK_PRIORITY, &xTaskSDCheck );
//	xTaskCreate( TK_VersionCheckTask, "VersionCheckTask", mainVERSIONCHECK_TASK_STACK_SIZE, NULL, mainVERSIONCHECK_TASK_PRIORITY, &xTaskVersionCheck );
//	xTaskCreate( TK_PrintTask, "PrintTask", mainPRINT_TASK_STACK_SIZE, NULL, mainPRINT_TASK_PRIORITY, &xTaskPrint );
//	xTaskCreate( TK_BurnTask, "BurnTask", mainBURN_TASK_STACK_SIZE, NULL, mainBURN_TASK_PRIORITY, &xTaskBurn );
//	
//	vTaskSuspend(xTaskPrint);
}



void vApplicationTickHook(void)
{
	
}

































