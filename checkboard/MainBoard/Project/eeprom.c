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


/* Project ---------------------------------------------------------------------*/
#include "eeprom.h"



void api_EEPROM_EarsePage(uint32_t vWriteAddress);
void api_EEPROM_Write_Buffer(uint32_t vWriteAddress, uint16_t* pBuffer, uint16_t vWriteNum);





uint16_t EEPROM_Read_HalfWord(uint32_t vReadAddress)
{
	return (*(volatile uint16_t*)vReadAddress);
}

void EEPROM_Write_NoCheck(uint32_t vWriteAddress, uint16_t* pBuffer, uint16_t vWriteNum)
{
	uint16_t iCnt;
	for(iCnt = 0; iCnt < vWriteNum; iCnt++)
	{
		FLASH_ProgramHalfWord(vWriteAddress, pBuffer[iCnt]);
		vWriteAddress += 2;
	}
}

void api_EEPROM_Write_Buffer(uint32_t vWriteAddress, uint16_t* pBuffer, uint16_t vWriteNum)
{
	__set_PRIMASK(1);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, DISABLE);

	FLASH_Unlock();

	EEPROM_Write_NoCheck(vWriteAddress, pBuffer, vWriteNum);

	FLASH_Lock();

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

	__set_PRIMASK(0);
}

void api_EEPROM_EarsePage(uint32_t vWriteAddress)
{
	__set_PRIMASK(1);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, DISABLE);

	FLASH_Unlock();

	FLASH_ErasePage(vWriteAddress);

	FLASH_Lock();

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_WWDG, ENABLE);

	__set_PRIMASK(0);
}
