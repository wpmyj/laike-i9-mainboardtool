/****************************************************************************************************/
/*			@FileName		:	EEPROM.h																																		   	*/
/*			@Author			:	zhengbaiqiu																																		*/
/*			@Version		:	v1.0																																					*/
/*			@Date				:	2019.11.12  																																	*/
/****************************************************************************************************/

#ifndef	__EEPROM_H__
#define	__EEPROM_H__
#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif


void api_EEPROM_EarsePage(uint32_t vWriteAddress);
void api_EEPROM_Write_Buffer(uint32_t vWriteAddress, uint16_t* pBuffer, uint16_t vWriteNum);
	
	
#ifdef _cplusplus
extern }
#endif

#endif /*__EEPROM_H__*/	


