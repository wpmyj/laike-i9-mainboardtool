/****************************************************************************************************/
/*			@FileName		:	MYPRINT.h																																		   	*/
/*			@Author			:	zhengbaiqiu																																		*/
/*			@Version		:	v1.0																																					*/
/*			@Date			:	2019.11.12  																																	*/
/****************************************************************************************************/

#ifndef	__MYPRINT_H__
#define	__MYPRINT_H__
#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif

void MyPrint_Start(void);
	
extern int (* printa)(const char *fmt, ...);
extern int (* printe)(const char *fmt, ...);
extern int (* printd)(const char *fmt, ...);
	
#ifdef _cplusplus
extern }
#endif

#endif /*__MYPRINT_H__*/	


