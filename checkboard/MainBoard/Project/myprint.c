/****************************************************************************************************/
/*			@FileName		:	timer.c															  	*/
/*			@Author			:	zhengbaiqiu															*/
/*			@Version		:	v1.0																*/
/*			@Date			:	2019.11.12  														*/
/****************************************************************************************************/


/* Includes --------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>

/* Project ---------------------------------------------------------------------*/
#include "myprint.h"

/* Variable --------------------------------------------------------------------*/
/* Function --------------------------------------------------------------------*/


FunctionalState printfEnable = DISABLE;


/*****************************************************************************
 * @name       :int fputc(int ch, FILE *f)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :fputc
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
// int fputc(int ch, FILE *f)
// {
//   if(printfEnable == ENABLE)USART_SendData(UART4, (uint8_t) ch);
//   /* Loop until the end of transmission */
//   while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET)
//   {}
//   return ch;
// }

/*****************************************************************************
 * @name       :void MyPrint_Start(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :打印使能
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void MyPrint_Start(void)
{
	printfEnable = ENABLE;
}

/*****************************************************************************
 * @name       :int VoidPrintf(const char *fmt, ...)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :空打印
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
int VoidPrintf(const char *fmt, ...)
{
	return 0;
}



#ifdef Print_Level_1
int (* printa)(const char *fmt, ...) = printf;
int (* printe)(const char *fmt, ...) = VoidPrintf;
int (* printd)(const char *fmt, ...) = VoidPrintf;
#elif Print_Level_2
int (* printa)(const char *fmt, ...) = printf;
int (* printe)(const char *fmt, ...) = printf;
int (* printd)(const char *fmt, ...) = VoidPrintf;
#else
int (* printa)(const char *fmt, ...) = printf;
int (* printe)(const char *fmt, ...) = printf;
int (* printd)(const char *fmt, ...) = printf;
#endif











