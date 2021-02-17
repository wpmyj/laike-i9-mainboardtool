/****************************************************************************************************/
/*			@FileName		:	TK_TestController.c												  	*/
/*			@Author			:	zhengbaiqiu															*/
/*			@Version		:	v1.0																*/
/*			@Date			:	2019.11.12  														*/
/****************************************************************************************************/


/* Includes --------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Project ---------------------------------------------------------------------*/
#include "maindef.h"
#include "apiLib.h"
#include "TK_TestController.h"


/* Variable --------------------------------------------------------------------*/
uint8_t * xMainBoardVersion = (uint8_t *)0x08020000;// i8 i9
//uint8_t * xI8MainBoardVersion = (uint8_t *)0x08020100;//i8
u8 ssss[32];


/* Function --------------------------------------------------------------------*/
void TK_TestController( void *pvParameters );
void api_SendCMD_To_Display(u8 mode,u8 cmd,u8 status, u16 time,u8 count);
u8 api_SendCMD_To_MainBoard(u8 seq,u8 mode,u8 cmd,u16 waittime,u8 type,u8 num,u8 status);
u8 Check_MainBoard_Version(void);


/*****************************************************************************
 * @name       :void TK_TestController( void *pvParameters )
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :时间控制任务
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
u8 sssss = 0;
void TK_TestController( void *pvParameters )
{
	//api_MachinePowerOn();
	for(;;)
	{
		IWDG_ReloadCounter();
		
// 		if(sssss == 0)
// 		{
// 			sssss = 1;
// 			api_Send_Signal(0x03,1);
// 		}
		
		
		
// 		for(iii = 0;iii <32;iii++)
// 		{
// 			ssss[iii] = xMainBoardVersion[iii];
// 		}
// 		PGout(12) = 1;   //压合板子
// 		PAout(12) = 1;
// 		PAout(15) = 1;
// 		PEout(1) = 0;
// 		PDout(4) = 1;

// 		PCout(2) = 0;
// 		PCout(1) = 0;
// 		PCout(0) = 0;
// 		PFout(10) = 0;
// 		PCout(5) = 0;
// 		PCout(4) = 0;
// 		PCout(3) = 0;
// 		mMaininf.mWork.mWorkDropSendFlag = 1;
// 		TIM_Cmd(TIM3,ENABLE);

//  		PGout(12) = 1;   //压合板子
// 		PAout(12) = 1;
// 		PAout(15) = 1;
// 		PEout(1) = 0;
// //		PDout(0) = 1;
		
// 		api_Control_Motor(7,1);
// 		PBout(4) = 1;
// 		PBout(5) = 1;
// 		api_Control_Motor(5,1);
// 		vTaskDelay(20);
// 		PAout(15) = 0;
// 		PAout(12) = 0;

// 		PGout(12) = 1;   //压合板子
// 		api_Send_Signal(0x12,1);
								
		if(mMaininf.mUart4.mReceiveFlag == 1)   //调试
		{
			mMaininf.mUart4.mReceiveFlag = 0;
			PGout(12) = 1;   //压合板子
			api_UART5_Display_SendCMDData(2,1,1);
 			vTaskDelay(1000);
			api_UART4_DEBUG_SendCMDData(1,1,1);//调试
			mMaininf.mWork.mWorkChecking = 1;
			PAout(12) = 1;
			PAout(15) = 1;
			PEout(1) = 0;
			vTaskDelay(10000);
			api_SendCMD_To_MainBoard(0,1,1,100,1,5,1);
			mMaininf.mWork.mWorkStep = mMaininf.mUart4.ReceiveBuf[2];
		}
		
		
		if((mMaininf.mWork.mWorkKeyPressFlag == 1) && (mMaininf.mWork.mWorkChecking == 0))
		{
			PGout(12) = 1;   //压合板子
			api_SendCMD_To_Display(2,1,1,1000,3);
 			vTaskDelay(1000);
			mMaininf.mWork.mWorkChecking = 1;
			mMaininf.mWork.mWorkStep = TEST_START;
		}
		
		
		if(mMaininf.mWork.mWorkChecking == 1)
//		if(mMaininf.mUart1.mReceiveFlag == 1)
		{
//			mMaininf.mWork.mWorkStep = mMaininf.mUart1.ReceiveBuf[2];
			
			if(mMaininf.mWork.mWorkStep != mMaininf.mWork.mWorkStepOld)
			{
				mMaininf.mWork.mWorkStepOld = mMaininf.mWork.mWorkStep;
			//	mMaininf.mWork.mWorkStep = TEST_TOF_POWER;
				
				//api_UART4_DEBUG_SendCMDData(1,mMaininf.mWork.mWorkStep,1);
				//vTaskDelay(1000);
				
				switch(mMaininf.mWork.mWorkStep)
				{
					case TEST_START ://01
						PAout(12) = 1;//放电供电继电器
						PAout(15) = 1;//放电供电继电器
						PEout(1) = 0;//开机键
						vTaskDelay(2000);
						PEout(1) = 1;
						api_UART4_SendData(32,xMainBoardVersion);
						vTaskDelay(4500);
						mMaininf.mWork.mWorkReadErrorFlag = 0;
					
						if(api_SendCMD_To_MainBoard(0,1,1,500,0,5,1) == 1)
						{
							api_SendCMD_To_Display(1,TEST_START,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_START,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(9,"tmep1-1\r\n");
							vTaskDelay(200);
							#endif
						}
 						mMaininf.mWork.mWorkStep = TEST_START_VERSION;
//						vTaskDelay(5000);
//						mMaininf.mWork.mWorkStep = TEST_WIFI;
						break;
					case TEST_START_VERSION ://02
						if(Check_MainBoard_Version() == 1)
						{
							api_SendCMD_To_Display(1,TEST_START_VERSION,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_START_VERSION,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(9,"tmep2-1\r\n");
							vTaskDelay(200);
							#endif
						}
						
						if(mMaininf.mWork.mWorkI8I9StatusFlag == 1)//i8
						{
							mMaininf.mWork.mWorkStep = TEST_SIDE_A_SEND;
						}
						else//i9
						{
							mMaininf.mWork.mWorkStep = TEST_TOF_POWER;
						}
						break;
					case TEST_TOF_POWER ://03
						if(api_SendCMD_To_MainBoard(0,1,3,300,0,5,1) == 1)
						{
							#ifdef zbq_Debug
							api_UART4_SendData(7,"ADC-0\r\n");
							vTaskDelay(50);
							#endif
							
							mMaininf.mWork.mWorkTestADC = ADCValue[0];
							
							api_ShortToStr(&ssss[0],mMaininf.mWork.mWorkTestADC);
							#ifdef zbq_Debug
							api_UART4_SendData(5,&ssss[0]);
							vTaskDelay(200);
							#endif
							
							if(api_Test_ADC(&ADCValue[0],1092,248) == 1)
							{
								api_SendCMD_To_Display(1,TEST_TOF_POWER,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_TOF_POWER,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(9,"tmep3-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_TOF_POWER,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(9,"tmep3-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_TOF_COMMUNICATION;
						break;
					case TEST_TOF_COMMUNICATION ://04
// 						//if(api_SendCMD_To_MainBoard(0,1,3,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,4,300,0,5,2) == 1)
						{
							api_Control_Motor(6,1);
							vTaskDelay(50);
							if(api_SendCMD_To_MainBoard(0,1,4,300,0,5,1) == 1)
							{
								api_SendCMD_To_Display(1,TEST_TOF_COMMUNICATION,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_TOF_COMMUNICATION,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_TOF_COMMUNICATION,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						api_Control_Motor(6,0);
						mMaininf.mWork.mWorkStep = TEST_TOF_RESET;
						break;
					case TEST_TOF_RESET ://05
						api_SendCMD_To_Display(1,TEST_TOF_RESET,1,1000,3);
						mMaininf.mWork.mWorkStep = TEST_SIDE_A_SEND;
						break;
					case TEST_SIDE_A_SEND ://06
						//if(api_SendCMD_To_MainBoard(0,1,6,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,7,300,0,5,1) == 1)
						{
							vTaskDelay(50);
							if(api_Check_PWM(GPIOC,GPIO_Pin_9,10,2,3) == 1)
							{
								api_SendCMD_To_Display(1,TEST_SIDE_A_SEND,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_SIDE_A_SEND,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(9,"tmep6-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_SIDE_A_SEND,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(9,"tmep6-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_SIDE_B_SEND;
						break;
					case TEST_SIDE_B_SEND ://07
						//if(api_SendCMD_To_MainBoard(0,1,7,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,8,300,0,5,1) == 1)
						{
							vTaskDelay(50);
							if(api_Check_PWM(GPIOC,GPIO_Pin_8,10,2,3) == 1)
							{
								api_SendCMD_To_Display(1,TEST_SIDE_B_SEND,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_SIDE_B_SEND,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(9,"tmep7-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_SIDE_B_SEND,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(9,"tmep7-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_LEFT_SIDE_REC;
						break;
					case TEST_LEFT_SIDE_REC ://08
						//if(api_SendCMD_To_MainBoard(0,1,8,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,9,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkAlongSideReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if(mMaininf.mWork.mWorkAlongSideReadVal > 2500)
							{
								api_Send_Signal(0x01,1);
								vTaskDelay(200);
								//if(api_SendCMD_To_MainBoard(0,1,8,100,1,5) == 1)
								if(api_SendCMD_To_MainBoard(0,1,9,300,1,5,1) == 1)
								{
									mMaininf.mWork.mWorkAlongSideReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
									
									if(mMaininf.mWork.mWorkAlongSideReadVal < 500)
									{
										api_SendCMD_To_Display(1,TEST_LEFT_SIDE_REC,1,1000,3);
									}
									else
									{
										api_SendCMD_To_Display(1,TEST_LEFT_SIDE_REC,0,1000,3);
										mMaininf.mWork.mWorkCheckErrorFlag = 1;
										#ifdef zbq_Debug
										api_UART4_SendData(9,"tmep8-4\r\n");
										vTaskDelay(200);
										#endif
									}
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_LEFT_SIDE_REC,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(9,"tmep8-3\r\n");
									vTaskDelay(200);
									#endif
								}
								api_Send_Signal(0x01,0);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_LEFT_SIDE_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(9,"tmep8-2\r\n");
								vTaskDelay(200);
								#endif
								
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_LEFT_SIDE_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(9,"tmep8-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_RIGHT_SIDE_REC;
						break;
					case TEST_RIGHT_SIDE_REC ://09
						//if(api_SendCMD_To_MainBoard(0,1,9,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,10,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkAlongSideReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if(mMaininf.mWork.mWorkAlongSideReadVal > 2500)
							{
								api_Send_Signal(0x02,1);
								vTaskDelay(200);
								//if(api_SendCMD_To_MainBoard(0,1,9,100,1,5) == 1)
								if(api_SendCMD_To_MainBoard(0,1,10,300,1,5,1) == 1)
								{
									mMaininf.mWork.mWorkAlongSideReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
									
									if(mMaininf.mWork.mWorkAlongSideReadVal < 500)
									{
										api_SendCMD_To_Display(1,TEST_RIGHT_SIDE_REC,1,1000,3);
									}
									else
									{
										api_SendCMD_To_Display(1,TEST_RIGHT_SIDE_REC,0,1000,3);
										mMaininf.mWork.mWorkCheckErrorFlag = 1;
										#ifdef zbq_Debug
										api_UART4_SendData(9,"tmep9-4\r\n");
										vTaskDelay(200);
										#endif
									}
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_RIGHT_SIDE_REC,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(9,"tmep9-3\r\n");
									vTaskDelay(200);
									#endif
								}
								api_Send_Signal(0x02,0);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_SIDE_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(9,"tmep9-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_SIDE_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(9,"tmep9-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_LEFT_GUIDE;
						break;
					case TEST_LEFT_GUIDE ://10
						api_Send_Signal(0x03,1);
						vTaskDelay(300);
						//if(api_SendCMD_To_MainBoard(0,1,10,1200,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,11,500,0,5,4) == 1)
						{
							api_Send_Signal(0x03,0);
							api_SendCMD_To_Display(1,TEST_LEFT_GUIDE,1,1000,3);
						}
						else
						{
							api_Send_Signal(0x03,0);
							api_SendCMD_To_Display(1,TEST_LEFT_GUIDE,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						//api_Send_Signal(0x03,0);
						mMaininf.mWork.mWorkStep = TEST_RIGHT_GUIDE;
						break;
					case TEST_RIGHT_GUIDE ://11
						api_Send_Signal(0x04,1);
						vTaskDelay(300);
						//if(api_SendCMD_To_MainBoard(0,1,11,1200,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,12,500,0,5,2) == 1)
						{
							api_Send_Signal(0x04,0);
							api_SendCMD_To_Display(1,TEST_RIGHT_GUIDE,1,1000,3);
						}
						else
						{
							api_Send_Signal(0x04,0);
							api_SendCMD_To_Display(1,TEST_RIGHT_GUIDE,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
// 						api_Send_Signal(0x04,0);
						mMaininf.mWork.mWorkStep = TEST_TOP_GUIDE;
						break;
					case TEST_TOP_GUIDE ://12
						api_Send_Signal(0x05,1);
						vTaskDelay(300);
						//if(api_SendCMD_To_MainBoard(0,1,12,1200,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,13,500,0,5,8) == 1)
						{
							api_Send_Signal(0x05,0);
							api_SendCMD_To_Display(1,TEST_TOP_GUIDE,1,1000,3);
						}
						else
						{
							api_Send_Signal(0x05,0);
							api_SendCMD_To_Display(1,TEST_TOP_GUIDE,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
// 						api_Send_Signal(0x05,0);
						mMaininf.mWork.mWorkStep = TEST_FRONT_GUIDE;
						break;
					case TEST_FRONT_GUIDE ://13
						api_Send_Signal(0x06,1);
						vTaskDelay(300);
						//if(api_SendCMD_To_MainBoard(0,1,13,1200,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,14,500,0,5,16) == 1)
						{
							api_Send_Signal(0x06,0);
							api_SendCMD_To_Display(1,TEST_FRONT_GUIDE,1,1000,3);
						}
						else
						{
							api_Send_Signal(0x06,0);
							api_SendCMD_To_Display(1,TEST_FRONT_GUIDE,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
// 						api_Send_Signal(0x06,0);
						mMaininf.mWork.mWorkStep = TEST_LATE_GUIDE;
						break;
					case TEST_LATE_GUIDE ://14
						api_Send_Signal(0x07,1);
						vTaskDelay(300);
						//if(api_SendCMD_To_MainBoard(0,1,14,1200,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,15,500,0,5,1) == 1)
						{
							api_Send_Signal(0x07,0);
							api_SendCMD_To_Display(1,TEST_LATE_GUIDE,1,1000,3);
						}
						else
						{
							api_Send_Signal(0x07,0);
							api_SendCMD_To_Display(1,TEST_LATE_GUIDE,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
// 						api_Send_Signal(0x07,0);
						mMaininf.mWork.mWorkStep = TEST_GUIDE_POWER;
						break;
					case TEST_GUIDE_POWER :
						if(api_ReadGpioInputStauts(GPIOE,GPIO_Pin_15,1,10) == 1)
						{
							api_SendCMD_To_Display(1,TEST_GUIDE_POWER,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_GUIDE_POWER,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_AVOIDBUMP_A_SEND;
						break;
					case TEST_AVOIDBUMP_A_SEND ://15
						//if(api_SendCMD_To_MainBoard(0,1,15,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,16,300,0,5,1) == 1)
						{
							if(api_Check_PWM(GPIOC,GPIO_Pin_7,10,2,3) == 1)
							{
								api_SendCMD_To_Display(1,TEST_AVOIDBUMP_A_SEND,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_AVOIDBUMP_A_SEND,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep16-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_AVOIDBUMP_A_SEND,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep16-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_AVOIDBUMP_B_SEND;
						break;
					case TEST_AVOIDBUMP_B_SEND ://16
						//if(api_SendCMD_To_MainBoard(0,1,16,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,17,300,0,5,1) == 1)
						{
							if(api_Check_PWM(GPIOC,GPIO_Pin_6,10,2,3) == 1)
							{
								api_SendCMD_To_Display(1,TEST_AVOIDBUMP_B_SEND,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_AVOIDBUMP_B_SEND,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep17-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_AVOIDBUMP_B_SEND,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep17-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_LEFT_AVOIDBUMP_REC;
						break;
					case TEST_LEFT_AVOIDBUMP_REC ://17
						//if(api_SendCMD_To_MainBoard(0,1,17,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,18,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkAvoidBumpReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if(mMaininf.mWork.mWorkAvoidBumpReadVal > 3102)
							{
								api_Send_Signal(0x16,1);
								vTaskDelay(200);
								//if(api_SendCMD_To_MainBoard(0,1,17,100,1,5) == 1)
								if(api_SendCMD_To_MainBoard(0,1,18,300,1,5,1) == 1)
								{
									mMaininf.mWork.mWorkAvoidBumpReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
									
									//if((mMaininf.mWork.mWorkAvoidBumpReadVal >= 1000) && (mMaininf.mWork.mWorkAvoidBumpReadVal <= 1400))
									if(mMaininf.mWork.mWorkAvoidBumpReadVal < 620)
									{
										api_SendCMD_To_Display(1,TEST_LEFT_AVOIDBUMP_REC,1,1000,3);
									}
									else
									{
										api_SendCMD_To_Display(1,TEST_LEFT_AVOIDBUMP_REC,0,1000,3);
										mMaininf.mWork.mWorkCheckErrorFlag = 1;
										#ifdef zbq_Debug
										api_UART4_SendData(10,"tmep18-4\r\n");
										vTaskDelay(200);
										#endif
									}
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_LEFT_AVOIDBUMP_REC,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep18-3\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_LEFT_AVOIDBUMP_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep18-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_LEFT_AVOIDBUMP_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep18-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x16,0);
						mMaininf.mWork.mWorkStep = TEST_RIGHT_AVOIDBUMP_REC;
						break;
					case TEST_RIGHT_AVOIDBUMP_REC ://18
						//api_Send_Signal(0x17,1);
						//if(api_SendCMD_To_MainBoard(0,1,18,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,19,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkAvoidBumpReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if(mMaininf.mWork.mWorkAvoidBumpReadVal > 3102)
							{
								api_Send_Signal(0x17,1);
								vTaskDelay(200);
								//if(api_SendCMD_To_MainBoard(0,1,18,100,1,5) == 1)
								if(api_SendCMD_To_MainBoard(0,1,19,300,1,5,1) == 1)
								{
									mMaininf.mWork.mWorkAvoidBumpReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
									
									if(mMaininf.mWork.mWorkAvoidBumpReadVal < 620)
									{
										api_SendCMD_To_Display(1,TEST_RIGHT_AVOIDBUMP_REC,1,1000,3);
									}
									else
									{
										api_SendCMD_To_Display(1,TEST_RIGHT_AVOIDBUMP_REC,0,1000,3);
										mMaininf.mWork.mWorkCheckErrorFlag = 1;
										#ifdef zbq_Debug
										api_UART4_SendData(10,"tmep19-4\r\n");
										vTaskDelay(200);
										#endif
									}
									
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_RIGHT_AVOIDBUMP_REC,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep19-3\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_AVOIDBUMP_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep19-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_AVOIDBUMP_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep19-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x17,0);
						mMaininf.mWork.mWorkStep = TEST_FRONT_AVOIDBUMP_REC;
						break;
					case TEST_FRONT_AVOIDBUMP_REC ://19
						//api_Send_Signal(0x18,1);
						//if(api_SendCMD_To_MainBoard(0,1,19,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,20,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkAvoidBumpReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if(mMaininf.mWork.mWorkAvoidBumpReadVal > 3102)
							{
								api_Send_Signal(0x18,1);
								vTaskDelay(200);
								//if(api_SendCMD_To_MainBoard(0,1,19,100,1,5) == 1)
								if(api_SendCMD_To_MainBoard(0,1,20,300,1,5,1) == 1)
								{
									mMaininf.mWork.mWorkAvoidBumpReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
									
									if(mMaininf.mWork.mWorkAvoidBumpReadVal < 620)
									{
										api_SendCMD_To_Display(1,TEST_FRONT_AVOIDBUMP_REC,1,1000,3);
									}
									else
									{
										api_SendCMD_To_Display(1,TEST_FRONT_AVOIDBUMP_REC,0,1000,3);
										mMaininf.mWork.mWorkCheckErrorFlag = 1;
										#ifdef zbq_Debug
										api_UART4_SendData(10,"tmep20-4\r\n");
										vTaskDelay(200);
										#endif
									}
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_FRONT_AVOIDBUMP_REC,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep20-3\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_FRONT_AVOIDBUMP_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep20-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_FRONT_AVOIDBUMP_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep20-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x18,0);
						mMaininf.mWork.mWorkStep = TEST_GYRO;
						break;
					case TEST_GYRO ://20
						if(api_SendCMD_To_MainBoard(0,1,22,300,0,5,1) == 1)
						{
							api_SendCMD_To_Display(1,TEST_GYRO,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_GYRO,0,1000,3);
 							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_KEY1;
						break;
					case TEST_KEY1 ://21
						if(api_SendCMD_To_MainBoard(0,1,23,300,0,5,0) == 1)
						{
							api_Control_Motor(1,1);
							vTaskDelay(1000);
							//if(api_SendCMD_To_MainBoard(0,1,22,100,0,5) == 1)
							if(api_SendCMD_To_MainBoard(0,1,23,300,0,5,1) == 1)
							{
								api_SendCMD_To_Display(1,TEST_KEY1,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_KEY1,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep22-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_KEY1,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep22-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Control_Motor(1,0);
						vTaskDelay(500);
						mMaininf.mWork.mWorkStep = TEST_KEY2;
						break;
					case TEST_KEY2 ://22
						if(api_SendCMD_To_MainBoard(0,1,24,300,0,5,0) == 1)
						{
							api_Control_Motor(2,1);
							vTaskDelay(1000);
							//if(api_SendCMD_To_MainBoard(0,1,23,100,0,5) == 1)
							if(api_SendCMD_To_MainBoard(0,1,24,300,0,5,2) == 1)
							{
								api_SendCMD_To_Display(1,TEST_KEY2,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_KEY2,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep23-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_KEY2,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep23-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Control_Motor(2,0);
						vTaskDelay(500);
						mMaininf.mWork.mWorkStep = TEST_KEY3;
						break;
					case TEST_KEY3 ://23
						if(api_SendCMD_To_MainBoard(0,1,25,300,0,5,0) == 1)
						{
							api_Control_Motor(3,1);
							vTaskDelay(1000);
							//if(api_SendCMD_To_MainBoard(0,1,24,100,0,5) == 1)
							if(api_SendCMD_To_MainBoard(0,1,25,300,0,5,4) == 1)
							{
								api_SendCMD_To_Display(1,TEST_KEY3,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_KEY3,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep24-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_KEY3,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep24-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Control_Motor(3,0);
						mMaininf.mWork.mWorkStep = TEST_DROP_SEND_LEFT;
						break;
					case TEST_DROP_SEND_LEFT ://24
						//if(api_SendCMD_To_MainBoard(0,1,25,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,26,300,0,5,1) == 1)
						{
							vTaskDelay(200);
							if(api_Check_PWM(GPIOG,GPIO_Pin_8,10,2,3) == 1)
							{
								api_SendCMD_To_Display(1,TEST_DROP_SEND_LEFT,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_DROP_SEND_LEFT,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep25-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_DROP_SEND_LEFT,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep25-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_DROP_SEND_RIGHT;
						break;
					case TEST_DROP_SEND_RIGHT :
						//vTaskDelay(200);
						if(api_Check_PWM(GPIOG,GPIO_Pin_7,10,2,3) == 1)
						{
							api_SendCMD_To_Display(1,TEST_DROP_SEND_RIGHT,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_DROP_SEND_RIGHT,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_DROP_SEND_FRONT;
						break;
					case TEST_DROP_SEND_FRONT :
						//vTaskDelay(200);
						if(api_Check_PWM(GPIOG,GPIO_Pin_6,10,2,3) == 1)
						{
							api_SendCMD_To_Display(1,TEST_DROP_SEND_FRONT,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_DROP_SEND_FRONT,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_DROP_SEND_LATE;
						break;
					case TEST_DROP_SEND_LATE :
						//vTaskDelay(200);
						if(api_Check_PWM(GPIOG,GPIO_Pin_5,10,2,3) == 1)
						{
							api_SendCMD_To_Display(1,TEST_DROP_SEND_LATE,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_DROP_SEND_LATE,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_LEFT_DROP_REC;
						break;
					case TEST_LEFT_DROP_REC ://25
						mMaininf.mWork.mWorkChangePhaseFlag = 0;
						api_Send_Signal(0x08,1);
						vTaskDelay(200);
						//if(api_SendCMD_To_MainBoard(0,1,27,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,28,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkDropReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							mMaininf.mWork.mWorkDropReadVal1 = (mMaininf.mUart1.ReceiveBuf[6] << 8) | mMaininf.mUart1.ReceiveBuf[7];
							
							if(mMaininf.mWork.mWorkDropReadVal > mMaininf.mWork.mWorkDropReadVal1)
							{
								mMaininf.mWork.mWorkDropReadVal2 = mMaininf.mWork.mWorkDropReadVal;
								mMaininf.mWork.mWorkDropReadVal = mMaininf.mWork.mWorkDropReadVal1;
								mMaininf.mWork.mWorkDropReadVal1 = mMaininf.mWork.mWorkDropReadVal2;
							}
							
							mMaininf.mWork.mWorkChangePhaseFlag = 1;
							vTaskDelay(200);
							//if(api_SendCMD_To_MainBoard(0,1,27,100,1,5) == 1)
							if(api_SendCMD_To_MainBoard(0,1,28,300,1,5,1) == 1)
							{
								mMaininf.mWork.mWorkDropPhaseReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
								mMaininf.mWork.mWorkDropPhaseReadVal1 = (mMaininf.mUart1.ReceiveBuf[6] << 8) | mMaininf.mUart1.ReceiveBuf[7];
								
								if(mMaininf.mWork.mWorkDropPhaseReadVal > mMaininf.mWork.mWorkDropPhaseReadVal1)
								{
									mMaininf.mWork.mWorkDropReadVal2 = mMaininf.mWork.mWorkDropPhaseReadVal;
									mMaininf.mWork.mWorkDropPhaseReadVal = mMaininf.mWork.mWorkDropPhaseReadVal1;
									mMaininf.mWork.mWorkDropPhaseReadVal1 = mMaininf.mWork.mWorkDropReadVal2;
								}
								
								if(((mMaininf.mWork.mWorkDropReadVal1 - mMaininf.mWork.mWorkDropReadVal > 248) && 
									(mMaininf.mWork.mWorkDropReadVal1 - mMaininf.mWork.mWorkDropReadVal < 3102)) || 
									((mMaininf.mWork.mWorkDropPhaseReadVal1 - mMaininf.mWork.mWorkDropPhaseReadVal > 248) && 
									(mMaininf.mWork.mWorkDropPhaseReadVal1 - mMaininf.mWork.mWorkDropPhaseReadVal < 3102)))
								{
									api_SendCMD_To_Display(1,TEST_LEFT_DROP_REC,1,1000,3);
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_LEFT_DROP_REC,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep29-3\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_LEFT_DROP_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep29-2\r\n");
								vTaskDelay(200);
								#endif
							}
							
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_LEFT_DROP_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep29-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkChangePhaseFlag = 0;
						api_Send_Signal(0x08,0);
						mMaininf.mWork.mWorkStep = TEST_RIGHT_DROP_REC;
						break;
					case TEST_RIGHT_DROP_REC ://26
						api_Send_Signal(0x09,1);
						vTaskDelay(200);
						//if(api_SendCMD_To_MainBoard(0,1,26,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,27,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkDropReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							mMaininf.mWork.mWorkDropReadVal1 = (mMaininf.mUart1.ReceiveBuf[6] << 8) | mMaininf.mUart1.ReceiveBuf[7];
							
							if(mMaininf.mWork.mWorkDropReadVal > mMaininf.mWork.mWorkDropReadVal1)
							{
								mMaininf.mWork.mWorkDropReadVal2 = mMaininf.mWork.mWorkDropReadVal;
								mMaininf.mWork.mWorkDropReadVal = mMaininf.mWork.mWorkDropReadVal1;
								mMaininf.mWork.mWorkDropReadVal1 = mMaininf.mWork.mWorkDropReadVal2;
							}
							
							mMaininf.mWork.mWorkChangePhaseFlag = 1;
							vTaskDelay(200);
							//if(api_SendCMD_To_MainBoard(0,1,26,100,1,5) == 1)
							if(api_SendCMD_To_MainBoard(0,1,27,300,1,5,1) == 1)
							{
							
								mMaininf.mWork.mWorkDropPhaseReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
								mMaininf.mWork.mWorkDropPhaseReadVal1 = (mMaininf.mUart1.ReceiveBuf[6] << 8) | mMaininf.mUart1.ReceiveBuf[7];
								
								if(mMaininf.mWork.mWorkDropPhaseReadVal > mMaininf.mWork.mWorkDropPhaseReadVal1)
								{
									mMaininf.mWork.mWorkDropReadVal2 = mMaininf.mWork.mWorkDropPhaseReadVal;
									mMaininf.mWork.mWorkDropPhaseReadVal = mMaininf.mWork.mWorkDropPhaseReadVal1;
									mMaininf.mWork.mWorkDropPhaseReadVal1 = mMaininf.mWork.mWorkDropReadVal2;
								}
								
								if(((mMaininf.mWork.mWorkDropReadVal1 - mMaininf.mWork.mWorkDropReadVal > 248) && 
									(mMaininf.mWork.mWorkDropReadVal1 - mMaininf.mWork.mWorkDropReadVal < 3102)) || 
									((mMaininf.mWork.mWorkDropPhaseReadVal1 - mMaininf.mWork.mWorkDropPhaseReadVal > 248) && 
									(mMaininf.mWork.mWorkDropPhaseReadVal1 - mMaininf.mWork.mWorkDropPhaseReadVal < 3102)))
								{
									api_SendCMD_To_Display(1,TEST_RIGHT_DROP_REC,1,1000,3);
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_RIGHT_DROP_REC,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep30-3\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_DROP_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep30-2\r\n");
								vTaskDelay(200);
								#endif
							}
							
							
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_DROP_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep30-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkChangePhaseFlag = 0;
						api_Send_Signal(0x09,0);
						mMaininf.mWork.mWorkStep = TEST_FRONT_DROP_REC;
						break;
					case TEST_FRONT_DROP_REC ://27
						api_Send_Signal(0x0a,1);
						vTaskDelay(200);
						//if(api_SendCMD_To_MainBoard(0,1,28,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,29,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkDropReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							mMaininf.mWork.mWorkDropReadVal1 = (mMaininf.mUart1.ReceiveBuf[6] << 8) | mMaininf.mUart1.ReceiveBuf[7];
							
							if(mMaininf.mWork.mWorkDropReadVal > mMaininf.mWork.mWorkDropReadVal1)
							{
								mMaininf.mWork.mWorkDropReadVal2 = mMaininf.mWork.mWorkDropReadVal;
								mMaininf.mWork.mWorkDropReadVal = mMaininf.mWork.mWorkDropReadVal1;
								mMaininf.mWork.mWorkDropReadVal1 = mMaininf.mWork.mWorkDropReadVal2;
							}
							
							mMaininf.mWork.mWorkChangePhaseFlag = 1;
							vTaskDelay(200);
							//if(api_SendCMD_To_MainBoard(0,1,28,100,1,5) == 1)
							if(api_SendCMD_To_MainBoard(0,1,29,300,1,5,1) == 1)
							{
							
								mMaininf.mWork.mWorkDropPhaseReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
								mMaininf.mWork.mWorkDropPhaseReadVal1 = (mMaininf.mUart1.ReceiveBuf[6] << 8) | mMaininf.mUart1.ReceiveBuf[7];
								
								if(mMaininf.mWork.mWorkDropPhaseReadVal > mMaininf.mWork.mWorkDropPhaseReadVal1)
								{
									mMaininf.mWork.mWorkDropReadVal2 = mMaininf.mWork.mWorkDropPhaseReadVal;
									mMaininf.mWork.mWorkDropPhaseReadVal = mMaininf.mWork.mWorkDropPhaseReadVal1;
									mMaininf.mWork.mWorkDropPhaseReadVal1 = mMaininf.mWork.mWorkDropReadVal2;
								}
								
								if(((mMaininf.mWork.mWorkDropReadVal1 - mMaininf.mWork.mWorkDropReadVal > 248) && 
									(mMaininf.mWork.mWorkDropReadVal1 - mMaininf.mWork.mWorkDropReadVal < 3102)) || 
									((mMaininf.mWork.mWorkDropPhaseReadVal1 - mMaininf.mWork.mWorkDropPhaseReadVal > 248) && 
									(mMaininf.mWork.mWorkDropPhaseReadVal1 - mMaininf.mWork.mWorkDropPhaseReadVal < 3102)))
								{
									api_SendCMD_To_Display(1,TEST_FRONT_DROP_REC,1,1000,3);
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_FRONT_DROP_REC,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep31-3\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_FRONT_DROP_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep31-2\r\n");
								vTaskDelay(200);
								#endif
							}
							
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_FRONT_DROP_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep31-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkChangePhaseFlag = 0;
						api_Send_Signal(0x0a,0);
						mMaininf.mWork.mWorkStep = TEST_LATE_DROP_REC;
						break;
					case TEST_LATE_DROP_REC ://28
						api_Send_Signal(0x0b,1);
						vTaskDelay(200);
						//if(api_SendCMD_To_MainBoard(0,1,29,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,30,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkDropReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							mMaininf.mWork.mWorkDropReadVal1 = (mMaininf.mUart1.ReceiveBuf[6] << 8) | mMaininf.mUart1.ReceiveBuf[7];
							
							if(mMaininf.mWork.mWorkDropReadVal > mMaininf.mWork.mWorkDropReadVal1)
							{
								mMaininf.mWork.mWorkDropReadVal2 = mMaininf.mWork.mWorkDropReadVal;
								mMaininf.mWork.mWorkDropReadVal = mMaininf.mWork.mWorkDropReadVal1;
								mMaininf.mWork.mWorkDropReadVal1 = mMaininf.mWork.mWorkDropReadVal2;
							}
							
							mMaininf.mWork.mWorkChangePhaseFlag = 1;
							vTaskDelay(200);
							//if(api_SendCMD_To_MainBoard(0,1,29,100,1,5) == 1)
							if(api_SendCMD_To_MainBoard(0,1,30,300,1,5,1) == 1)
							{
							
								mMaininf.mWork.mWorkDropPhaseReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
								mMaininf.mWork.mWorkDropPhaseReadVal1 = (mMaininf.mUart1.ReceiveBuf[6] << 8) | mMaininf.mUart1.ReceiveBuf[7];
								
								if(mMaininf.mWork.mWorkDropPhaseReadVal > mMaininf.mWork.mWorkDropPhaseReadVal1)
								{
									mMaininf.mWork.mWorkDropReadVal2 = mMaininf.mWork.mWorkDropPhaseReadVal;
									mMaininf.mWork.mWorkDropPhaseReadVal = mMaininf.mWork.mWorkDropPhaseReadVal1;
									mMaininf.mWork.mWorkDropPhaseReadVal1 = mMaininf.mWork.mWorkDropReadVal2;
								}
								
								if(((mMaininf.mWork.mWorkDropReadVal1 - mMaininf.mWork.mWorkDropReadVal > 248) && 
									(mMaininf.mWork.mWorkDropReadVal1 - mMaininf.mWork.mWorkDropReadVal < 3102)) || 
									((mMaininf.mWork.mWorkDropPhaseReadVal1 - mMaininf.mWork.mWorkDropPhaseReadVal > 248) && 
									(mMaininf.mWork.mWorkDropPhaseReadVal1 - mMaininf.mWork.mWorkDropPhaseReadVal < 3102)))
								{
									api_SendCMD_To_Display(1,TEST_LATE_DROP_REC,1,1000,3);
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_LATE_DROP_REC,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep32-3\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_LATE_DROP_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep32-2\r\n");
								vTaskDelay(200);
								#endif
							}
							
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_LATE_DROP_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep32-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkChangePhaseFlag = 0;
						api_Send_Signal(0x0b,0);
						mMaininf.mWork.mWorkStep = TEST_LEFT_BUMP;
						break;
					case TEST_LEFT_BUMP ://29
						//if(api_SendCMD_To_MainBoard(0,1,31,100,0,2) == 1)
						if(api_SendCMD_To_MainBoard(0,1,32,300,0,5,1) == 1)
						{
							api_Send_Signal(0x0c,1);
							vTaskDelay(100);
							//if(api_SendCMD_To_MainBoard(0,1,31,100,0,5) == 0)
							if(api_SendCMD_To_MainBoard(0,1,32,300,0,5,0) == 1)
							{
								api_SendCMD_To_Display(1,TEST_LEFT_BUMP,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_LEFT_BUMP,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep33-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_LEFT_BUMP,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep33-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x0c,0);
						mMaininf.mWork.mWorkStep = TEST_LEFT_BUMP_POWER;
						break;
					case TEST_LEFT_BUMP_POWER :
						if(api_ReadGpioInputStauts(GPIOE,GPIO_Pin_14,1,10) == 1)
						{
							api_SendCMD_To_Display(1,TEST_LEFT_BUMP_POWER,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_LEFT_BUMP_POWER,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_RIGHT_BUMP;
						break;
					case TEST_RIGHT_BUMP ://30
						//if(api_SendCMD_To_MainBoard(0,1,30,100,0,2) == 1)
						if(api_SendCMD_To_MainBoard(0,1,31,300,0,5,1) == 1)
						{
							api_Send_Signal(0x0d,1);
							vTaskDelay(100);
							//if(api_SendCMD_To_MainBoard(0,1,30,100,0,5) == 0)
							if(api_SendCMD_To_MainBoard(0,1,31,300,0,5,0) == 1)
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_BUMP,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_BUMP,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep35-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_BUMP,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep35-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x0d,0);
						mMaininf.mWork.mWorkStep = TEST_RIGHT_BUMP_POWER;
						break;
					case TEST_RIGHT_BUMP_POWER :
						if(api_ReadGpioInputStauts(GPIOE,GPIO_Pin_13,1,10) == 1)
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_BUMP_POWER,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_BUMP_POWER,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_LEFT_LEAVELAND;
						break;
					case TEST_LEFT_LEAVELAND ://31
						//if(api_SendCMD_To_MainBoard(0,1,33,100,0,2) == 1)
						if(api_SendCMD_To_MainBoard(0,1,34,300,0,5,1) == 1)
						{
							api_Send_Signal(0x0e,1);
							vTaskDelay(100);
							//if(api_SendCMD_To_MainBoard(0,1,33,100,0,5) == 0)
							if(api_SendCMD_To_MainBoard(0,1,34,300,0,5,0) == 1)
							{
								api_SendCMD_To_Display(1,TEST_LEFT_LEAVELAND,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_LEFT_LEAVELAND,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep37-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_LEFT_LEAVELAND,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep37-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x0e,0);
						mMaininf.mWork.mWorkStep = TEST_RIGHT_LEAVELAND;
						break;
					case TEST_RIGHT_LEAVELAND ://32
						//if(api_SendCMD_To_MainBoard(0,1,32,100,0,2) == 1)
						if(api_SendCMD_To_MainBoard(0,1,33,300,0,5,1) == 1)
						{
							api_Send_Signal(0x0f,1);
							vTaskDelay(100);
							//if(api_SendCMD_To_MainBoard(0,1,32,100,0,5) == 0)
							if(api_SendCMD_To_MainBoard(0,1,33,300,0,5,0) == 1)
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_LEAVELAND,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_LEAVELAND,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep38-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_LEAVELAND,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep38-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x0f,0);
						mMaininf.mWork.mWorkStep = TEST_LEFT_WHEEL_FEEDBACK;
						break;
					case TEST_LEFT_WHEEL_FEEDBACK ://33
						api_Send_Signal(0x10,1);
						vTaskDelay(1000);
						//if(api_SendCMD_To_MainBoard(0,1,35,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,36,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkCodeReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if((mMaininf.mWork.mWorkCodeReadVal > 900) && (mMaininf.mWork.mWorkCodeReadVal < 1100))
							{
								api_SendCMD_To_Display(1,TEST_LEFT_WHEEL_FEEDBACK,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_LEFT_WHEEL_FEEDBACK,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep39-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_LEFT_WHEEL_FEEDBACK,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep39-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x10,0);
						mMaininf.mWork.mWorkStep = TEST_LEFT_WHEEL_FEEDBACK_POWER;
						break;
					case TEST_LEFT_WHEEL_FEEDBACK_POWER :
						if(api_ReadGpioInputStauts(GPIOE,GPIO_Pin_12,1,10) == 1)
						{
							api_SendCMD_To_Display(1,TEST_LEFT_WHEEL_FEEDBACK_POWER,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_LEFT_WHEEL_FEEDBACK_POWER,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_RIGHT_WHEEL_FEEDBACK;
						break;
					case TEST_RIGHT_WHEEL_FEEDBACK ://34
						api_Send_Signal(0x11,1);
						vTaskDelay(1000);
						//if(api_SendCMD_To_MainBoard(0,1,34,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,35,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkCodeReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if((mMaininf.mWork.mWorkCodeReadVal > 900) && (mMaininf.mWork.mWorkCodeReadVal < 1100))
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_WHEEL_FEEDBACK,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_WHEEL_FEEDBACK,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep41-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_WHEEL_FEEDBACK,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep41-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x11,0);
						mMaininf.mWork.mWorkStep = TEST_RIGHT_WHEEL_FEEDBACK_POWER;
						break;
					case TEST_RIGHT_WHEEL_FEEDBACK_POWER :
						if(api_ReadGpioInputStauts(GPIOE,GPIO_Pin_11,1,10) == 1)
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_WHEEL_FEEDBACK_POWER,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_WHEEL_FEEDBACK_POWER,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_LEFT_WHEEL;
						break;
					case TEST_LEFT_WHEEL ://35
						//if(api_SendCMD_To_MainBoard(0,1,37,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,38,300,0,5,1) == 1)
						{
							vTaskDelay(200);
							//if((api_ReadGpioInputStauts(GPIOE,GPIO_Pin_10,1,10) == 1) && (api_ReadGpioInputStauts(GPIOE,GPIO_Pin_9,0,10) == 1))
							if((api_ReadWheelGpioInputStauts(GPIOE,GPIO_Pin_10,0,10) == 1) && (api_ReadWheelGpioInputStauts(GPIOE,GPIO_Pin_9,1,10) == 1))
							{
								api_SendCMD_To_Display(1,TEST_LEFT_WHEEL,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_LEFT_WHEEL,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep43-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_LEFT_WHEEL,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep43-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_RIGHT_WHEEL;
						break;
					case TEST_RIGHT_WHEEL ://36
						//if(api_SendCMD_To_MainBoard(0,1,36,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,37,300,0,5,1) == 1)
						{
							vTaskDelay(200);
							//if((api_ReadGpioInputStauts(GPIOE,GPIO_Pin_8,1,10) == 1) && (api_ReadGpioInputStauts(GPIOE,GPIO_Pin_7,0,10) == 1))
							if((api_ReadWheelGpioInputStauts(GPIOE,GPIO_Pin_7,0,10) == 1) && (api_ReadWheelGpioInputStauts(GPIOE,GPIO_Pin_8,1,10) == 1))
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_WHEEL,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_RIGHT_WHEEL,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep44-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_RIGHT_WHEEL,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep44-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_ROLLBURSH_CUR_FEEDBACK;
						break;
					case TEST_ROLLBURSH_CUR_FEEDBACK ://37
						api_Control_Motor(4,1);
						vTaskDelay(200);
						//if(api_SendCMD_To_MainBoard(0,1,38,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,39,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkRollBrushCurrentVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if((mMaininf.mWork.mWorkRollBrushCurrentVal > 50) && (mMaininf.mWork.mWorkRollBrushCurrentVal < 150))
							{
								api_SendCMD_To_Display(1,TEST_ROLLBURSH_CUR_FEEDBACK,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_ROLLBURSH_CUR_FEEDBACK,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep45-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_ROLLBURSH_CUR_FEEDBACK,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep45-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Control_Motor(4,0);
						mMaininf.mWork.mWorkStep = TEST_VACUUM_FEEDBACK;
						break;
					case TEST_VACUUM_FEEDBACK ://38
						PBout(6) = 1;
						PBout(7) = 1;
						vTaskDelay(50);
						api_Control_Motor(5,1);
						vTaskDelay(200);
						//if(api_SendCMD_To_MainBoard(0,1,39,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,40,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkVacuumCurrentVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							api_ShortToStr(&ssss[0],mMaininf.mWork.mWorkVacuumCurrentVal);
							#ifdef zbq_Debug
							api_UART4_SendData(5,&ssss[0]);
							vTaskDelay(200);
							#endif
							
							if((mMaininf.mWork.mWorkVacuumCurrentVal > 135) && (mMaininf.mWork.mWorkVacuumCurrentVal < 235))
							{
								api_SendCMD_To_Display(1,TEST_VACUUM_FEEDBACK,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_VACUUM_FEEDBACK,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep46-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_VACUUM_FEEDBACK,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep46-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Control_Motor(5,0);
						vTaskDelay(50);
						PBout(6) = 0;
						PBout(7) = 0;
						mMaininf.mWork.mWorkStep = TEST_VACUUM_CONTROL;
						break;
					case TEST_VACUUM_CONTROL ://39
						//if(api_SendCMD_To_MainBoard(0,1,40,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,41,300,0,5,1) == 1)
						{
							//if(api_Check_PWM(GPIOG,GPIO_Pin_4,50,10) == 1)
							if(api_Check_PWM(GPIOF,GPIO_Pin_13,50,10,3) == 1)
							{
								api_SendCMD_To_Display(1,TEST_VACUUM_CONTROL,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_VACUUM_CONTROL,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep47-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_VACUUM_CONTROL,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep47-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_DISCHARGE_CUR_FEEDBACK;
						break;
					case TEST_DISCHARGE_CUR_FEEDBACK ://40
						api_SendCMD_To_Display(1,TEST_DISCHARGE_CUR_FEEDBACK,1,1000,3);
						mMaininf.mWork.mWorkStep = TEST_POWER_NTC;
						break;
					case TEST_POWER_NTC ://41
						//if(api_SendCMD_To_MainBoard(0,1,42,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,43,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkNTCVoltageVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if((mMaininf.mWork.mWorkNTCVoltageVal > 500) && (mMaininf.mWork.mWorkNTCVoltageVal < 900))
							{
								api_SendCMD_To_Display(1,TEST_POWER_NTC,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_POWER_NTC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep49-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_POWER_NTC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep49-1\r\n");
							vTaskDelay(200);
							#endif
						}
						mMaininf.mWork.mWorkStep = TEST_OPEN_KEY;
						break;
					case TEST_OPEN_KEY ://42
						api_SendCMD_To_Display(1,TEST_OPEN_KEY,1,1000,3);
						mMaininf.mWork.mWorkStep = TEST_DUST_REC;
						break;
					case TEST_DUST_REC ://43
						//if(api_SendCMD_To_MainBoard(0,1,45,100,1,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,46,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkDustReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if(mMaininf.mWork.mWorkDustReadVal > 3000)
							{
								api_Send_Signal(0x14,1);
								vTaskDelay(300);
								//if(api_SendCMD_To_MainBoard(0,1,45,100,1,5) == 1)
								if(api_SendCMD_To_MainBoard(0,1,46,300,1,5,1) == 1)
								{
									mMaininf.mWork.mWorkDustReadVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
									
									if(mMaininf.mWork.mWorkDustReadVal < 500)
									{
										api_SendCMD_To_Display(1,TEST_DUST_REC,1,1000,3);
									}
									else
									{
										api_SendCMD_To_Display(1,TEST_DUST_REC,0,1000,3);
										mMaininf.mWork.mWorkCheckErrorFlag = 1;
										#ifdef zbq_Debug
										api_UART4_SendData(10,"tmep51-4\r\n");
										vTaskDelay(200);
										#endif
									}
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_DUST_REC,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep51-3\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_DUST_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep51-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_DUST_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep51-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x14,0);
						mMaininf.mWork.mWorkStep = TEST_DUST_POWER;
						break;
					case TEST_DUST_POWER :
						if(api_ReadGpioInputStauts(GPIOG,GPIO_Pin_0,1,10) == 1)
						{
							api_SendCMD_To_Display(1,TEST_DUST_POWER,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_DUST_POWER,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_DUSTCUP_REC;
						break;
					case TEST_DUSTCUP_REC ://44
						//if(api_SendCMD_To_MainBoard(0,1,46,100,0,2) == 1)
						if(api_SendCMD_To_MainBoard(0,1,47,300,0,5,1) == 1)
						{
							api_Send_Signal(0x15,1);
							vTaskDelay(100);
							//if(api_SendCMD_To_MainBoard(0,1,46,100,0,3) == 0)
							if(api_SendCMD_To_MainBoard(0,1,47,300,0,5,0) == 1)
							{
								api_SendCMD_To_Display(1,TEST_DUSTCUP_REC,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_DUSTCUP_REC,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep53-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_DUSTCUP_REC,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep53-1\r\n");
							vTaskDelay(200);
							#endif
						}
						api_Send_Signal(0x15,0);
						mMaininf.mWork.mWorkStep = TEST_DUSTCUP_POWER;
						break;
					case TEST_DUSTCUP_POWER :
						if(api_ReadGpioInputStauts(GPIOF,GPIO_Pin_15,1,10) == 1)
						{
							api_SendCMD_To_Display(1,TEST_DUSTCUP_POWER,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_DUSTCUP_POWER,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_WATERTANK;
						break;
					case TEST_WATERTANK ://45
						if(api_SendCMD_To_MainBoard(0,1,48,300,1,3,1) == 1)
						{
							mMaininf.mWork.mWorkWaterTankVoltageVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if(mMaininf.mWork.mWorkWaterTankVoltageVal < 248)
							{
								api_Control_Motor(8,1);
								vTaskDelay(200);
								//if(api_SendCMD_To_MainBoard(0,1,47,100,1,3) == 1)
								if(api_SendCMD_To_MainBoard(0,1,48,300,1,3,1) == 1)
								{
									mMaininf.mWork.mWorkWaterTankVoltageVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
									
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep54-a\r\n");
									vTaskDelay(50);
									#endif
									
									api_ShortToStr(&ssss[0],mMaininf.mWork.mWorkWaterTankVoltageVal);
									#ifdef zbq_Debug
									api_UART4_SendData(5,&ssss[0]);
									vTaskDelay(200);
									#endif
									
									//if((mMaininf.mWork.mWorkWaterTankVoltageVal > 1700) && (mMaininf.mWork.mWorkWaterTankVoltageVal < 2300))
									if((mMaininf.mWork.mWorkWaterTankVoltageVal > 1240) && (mMaininf.mWork.mWorkWaterTankVoltageVal < 1861))
									{
										api_SendCMD_To_Display(1,TEST_WATERTANK,1,1000,3);
									}
									else
									{
										api_SendCMD_To_Display(1,TEST_WATERTANK,0,1000,3);
										mMaininf.mWork.mWorkCheckErrorFlag = 1;
										#ifdef zbq_Debug
										api_UART4_SendData(10,"tmep54-2\r\n");
										vTaskDelay(200);
										#endif
									}
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_WATERTANK,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep54-1\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_WATERTANK,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_WATERTANK,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						api_Control_Motor(8,0);
						mMaininf.mWork.mWorkStep = TEST_POSITION_CAMERA;
						break;
					case TEST_POSITION_CAMERA ://46
						//if(api_SendCMD_To_MainBoard(0,1,48,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,49,300,0,5,1) == 1)
						{
							api_SendCMD_To_Display(1,TEST_POSITION_CAMERA,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_POSITION_CAMERA,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_POSITION_CAMERA_POWER;
						break;
					case TEST_POSITION_CAMERA_POWER :
						#ifdef zbq_Debug
						api_UART4_SendData(7,"ADC-1\r\n");
						vTaskDelay(50);
						#endif
						
						mMaininf.mWork.mWorkTestADC = ADCValue[1];
						
						api_ShortToStr(&ssss[0],mMaininf.mWork.mWorkTestADC);
						#ifdef zbq_Debug
						api_UART4_SendData(5,&ssss[0]);
						vTaskDelay(200);
						#endif
					
						if(api_Test_ADC(&ADCValue[1],2673,124) == 1)
						{
							api_SendCMD_To_Display(1,TEST_POSITION_CAMERA_POWER,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_POSITION_CAMERA_POWER,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_DC5V;
						break;
					case TEST_DC5V :
						#ifdef zbq_Debug
						api_UART4_SendData(7,"ADC-2\r\n");
						vTaskDelay(50);
						#endif
						
						mMaininf.mWork.mWorkTestADC = ADCValue[2];
						
						api_ShortToStr(&ssss[0],mMaininf.mWork.mWorkTestADC);
						#ifdef zbq_Debug
						api_UART4_SendData(5,&ssss[0]);
						vTaskDelay(200);
						#endif
					
						if(api_Test_ADC(&ADCValue[2],1630,124) == 1)
						{
							api_SendCMD_To_Display(1,TEST_DC5V,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_DC5V,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						
						if(mMaininf.mWork.mWorkI8I9StatusFlag == 1)//i8
						{
							mMaininf.mWork.mWorkStep = TEST_DC5V_I8;
						}
						else//i9
						{
							mMaininf.mWork.mWorkStep = TEST_PATHPLAN_UART;
						}
						break;
					case TEST_DC5V_I8 :
						if(api_ReadGpioInputStauts(GPIOF,GPIO_Pin_14,1,5) == 1)
						{
							api_SendCMD_To_Display(1,TEST_DC5V_I8,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_DC5V_I8,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_PATHPLAN_UART;
						break;
					case TEST_PATHPLAN_UART ://47
						if(mMaininf.mWork.mWorkBigUartFlag == 1)
						{
							api_SendCMD_To_Display(1,TEST_PATHPLAN_UART,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_PATHPLAN_UART,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_WIFI;
						break;
					case TEST_WIFI ://48
						//if(api_SendCMD_To_MainBoard(0,1,5,100,0,5) == 1)
						if(api_SendCMD_To_MainBoard(0,1,6,300,0,5,1) == 1)
						{
							api_SendCMD_To_Display(1,TEST_WIFI,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_WIFI,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_BATTERY;
						//mMaininf.mWork.mWorkStep = TEST_LEST;
						break;
					case TEST_BATTERY ://49
						if(api_SendCMD_To_MainBoard(0,1,50,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkBatteryPowerVoltageVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							if((mMaininf.mWork.mWorkBatteryPowerVoltageVal > 1350) && 
								(mMaininf.mWork.mWorkBatteryPowerVoltageVal < 1650))
							{
								api_SendCMD_To_Display(1,TEST_BATTERY,1,1000,3);
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_BATTERY,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_BATTERY,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						mMaininf.mWork.mWorkStep = TEST_CHARGE;
						break;
					case TEST_CHARGE ://50
// 						PBout(4) = 1;
// 						PBout(5) = 1;
// 						api_Control_Motor(5,1);
// 						vTaskDelay(20);
						api_Control_Motor(7,1);
						vTaskDelay(200);
						//PAout(15) = 0;
						/*if(api_ReadGpioInputStauts(GPIOG,GPIO_Pin_1,1,10) == 1)
						{
							PBout(4) = 1;
							PBout(5) = 1;
							api_Control_Motor(5,1);
							vTaskDelay(20);
							PAout(15) = 0;
							PAout(12) = 0;
							vTaskDelay(1000);
							//检主板1A电流
							if(api_SendCMD_To_MainBoard(0,1,44,300,1,5,1) == 1)
							{
								mMaininf.mWork.mWorkChargeVoltageVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
								
								api_ShortToStr(&ssss[0],mMaininf.mWork.mWorkChargeVoltageVal);
								#ifdef zbq_Debug
								api_UART4_SendData(5,&ssss[0]);
								vTaskDelay(200);
								#endif
								
								if((mMaininf.mWork.mWorkChargeVoltageVal > -1250) && (mMaininf.mWork.mWorkChargeVoltageVal < -750))
								{
									api_SendCMD_To_Display(1,TEST_CHARGE,1,1000,3);
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_CHARGE,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									
									#ifdef zbq_Debug
									api_UART4_SendData(10,"tmep60-1\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_CHARGE,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep60-2\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_CHARGE,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep60-3\r\n");
							vTaskDelay(200);
							#endif
						}*/
						
						PBout(4) = 1;
						PBout(5) = 1;
						api_Control_Motor(5,1);
						vTaskDelay(20);
						PAout(15) = 0;
						PAout(12) = 0;
						vTaskDelay(1000);
						if(api_ReadGpioInputStauts(GPIOG,GPIO_Pin_1,1,10) == 1)
						{
							mMaininf.mWork.mWorkChargeCheckFlag = 1;
						}
						else
						{
							mMaininf.mWork.mWorkChargeCheckFlag = 0;
						}
						
						//检主板1A电流
						if(api_SendCMD_To_MainBoard(0,1,44,300,1,5,1) == 1)
						{
							mMaininf.mWork.mWorkChargeVoltageVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
							
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep60-a\r\n");
							vTaskDelay(50);
							#endif
							
							api_ShortToStr(&ssss[0],mMaininf.mWork.mWorkChargeVoltageVal);
							#ifdef zbq_Debug
							api_UART4_SendData(5,&ssss[0]);
							vTaskDelay(200);
							#endif
							
							if((mMaininf.mWork.mWorkChargeVoltageVal > -1250) && (mMaininf.mWork.mWorkChargeVoltageVal < -750))
							{
								mMaininf.mWork.mWorkChargeCheckCurFlag = 1;
								//api_SendCMD_To_Display(1,TEST_CHARGE,1,1000,3);
							}
							else
							{
								mMaininf.mWork.mWorkChargeCheckCurFlag = 0;
//								api_SendCMD_To_Display(1,TEST_CHARGE,0,1000,3);
//								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								
								#ifdef zbq_Debug
								api_UART4_SendData(10,"tmep60-1\r\n");
								vTaskDelay(200);
								#endif
							}
						}
						else
						{
							mMaininf.mWork.mWorkChargeCheckCurFlag = 0;
//							api_SendCMD_To_Display(1,TEST_CHARGE,0,1000,3);
//							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							
							#ifdef zbq_Debug
							api_UART4_SendData(10,"tmep60-2\r\n");
							vTaskDelay(200);
							#endif
						}
						
						if((mMaininf.mWork.mWorkChargeCheckFlag == 1) || (mMaininf.mWork.mWorkChargeCheckCurFlag == 1))
						{
							api_SendCMD_To_Display(1,TEST_CHARGE,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_CHARGE,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
						}
						
						mMaininf.mWork.mWorkStep = TEST_POWER_POWER;
						break;
					case TEST_POWER_POWER :
						vTaskDelay(50);
						api_Send_Signal(0x12,1);
						vTaskDelay(200);
// 						api_Control_Motor(7,0);
// 						vTaskDelay(1000);
						if(api_ReadGpioInputStauts(GPIOG,GPIO_Pin_1,0,10) == 1)
						{
							/*//电流0
							if(api_SendCMD_To_MainBoard(0,1,44,300,1,5,1) == 1)
							{
								mMaininf.mWork.mWorkChargeVoltageVal = (mMaininf.mUart1.ReceiveBuf[4] << 8) | mMaininf.mUart1.ReceiveBuf[5];
								
								if(mMaininf.mWork.mWorkChargeVoltageVal <= 0)
								{
									api_ShortToStr(&ssss[0],mMaininf.mWork.mWorkChargeVoltageVal);
									#ifdef zbq_Debug
									api_UART4_SendData(5,&ssss[0]);
									vTaskDelay(200);
									#endif
								}
								
								
								if((mMaininf.mWork.mWorkChargeVoltageVal > -200) && (mMaininf.mWork.mWorkChargeVoltageVal <= 0))
								{
									api_SendCMD_To_Display(1,TEST_POWER_POWER,1,1000,3);
								}
								else
								{
									api_SendCMD_To_Display(1,TEST_POWER_POWER,0,1000,3);
									mMaininf.mWork.mWorkCheckErrorFlag = 1;
									
									#ifdef zbq_Debug
									api_UART4_SendData(10,"61-1\r\n");
									vTaskDelay(200);
									#endif
								}
							}
							else
							{
								api_SendCMD_To_Display(1,TEST_POWER_POWER,0,1000,3);
								mMaininf.mWork.mWorkCheckErrorFlag = 1;
								
								#ifdef zbq_Debug
								api_UART4_SendData(10,"61-2\r\n");
								vTaskDelay(200);
								#endif
							}*/
							
							api_SendCMD_To_Display(1,TEST_POWER_POWER,1,1000,3);
						}
						else
						{
							api_SendCMD_To_Display(1,TEST_POWER_POWER,0,1000,3);
							mMaininf.mWork.mWorkCheckErrorFlag = 1;
							
							#ifdef zbq_Debug
							api_UART4_SendData(10,"61-3\r\n");
							vTaskDelay(200);
							#endif
						}
						PBout(4) = 0;
						PBout(5) = 0;
						api_Control_Motor(5,0);
						api_Send_Signal(0x12,0);
						api_Control_Motor(7,0);
//						PBout(4) = 0;
//						PBout(5) = 0;
						
						mMaininf.mWork.mWorkStep = TEST_LEST;
						break;
					
					
					case TEST_LEST :
						if(mMaininf.mWork.mWorkCheckErrorFlag == 0)
						{
							api_SendCMD_To_Display(1,0xfe,1,1500,3);
						}
						mMaininf.mWork.mWorkCheckErrorFlag = 0;
						api_Control_Motor(7,0);
						PAout(12) = 0;
						PAout(15) = 0;
						//PEout(1) = 1;
						vTaskDelay(100);
						PGout(12) = 0;   //抬起板子
						mMaininf.mWork.mWorkKeyPressFlag = 0;
						mMaininf.mWork.mWorkChecking = 0;
						mMaininf.mWork.mWorkCheckStatus = 0;
						mMaininf.mWork.mWorkStep = 0;
						mMaininf.mWork.mWorkStepOld = 0;
						mMaininf.mWork.mWorkFileStep = 0;
						mMaininf.mWork.mWorkBigUartFlag = 0;
// 						api_Control_Motor(6,0);
						break;
					
// 					case TEST_FILE ://test file
// 						api_Control_Motor(7,0);
// 						PAout(12) = 0;
// 						PAout(15) = 0;
// 						PEout(1) = 1;
// 						vTaskDelay(100);
// 						PGout(12) = 0;   //抬起板子
// 						mMaininf.mWork.mWorkKeyPressFlag = 0;
// 						mMaininf.mWork.mWorkChecking = 0;
// 						mMaininf.mWork.mWorkCheckStatus = 0;
// 						//api_UART5_Display_SendCMDData(1,mMaininf.mWork.mWorkFileStep,0);
// 						api_SendCMD_To_Display(1,mMaininf.mWork.mWorkFileStep,0);
// 						mMaininf.mWork.mWorkFileStep = 0;
// 						mMaininf.mWork.mWorkBigUartFlag = 0;
// 						api_Control_Motor(6,0);
// 						break;
// 					case TEST_OK ://test ok
// 						api_Control_Motor(7,0);
// 						PAout(12) = 0;
// 						PAout(15) = 0;
// 						PEout(1) = 1;
// 						vTaskDelay(100);
// 						PGout(12) = 0;   //抬起板子
// 						mMaininf.mWork.mWorkKeyPressFlag = 0;
// 						mMaininf.mWork.mWorkChecking = 0;
// 						mMaininf.mWork.mWorkCheckStatus = 0;
// 						//api_UART5_Display_SendCMDData(1,0xfe,1);
// 						api_SendCMD_To_Display(1,0xfe,1);
// 						mMaininf.mWork.mWorkFileStep = 0;
// 						mMaininf.mWork.mWorkBigUartFlag = 0;
// 						api_Control_Motor(6,0);
// 						break;
					default :
						break;
				}
			}
			
	// 		if(mMaininf.mWork.mWorkCheckStatus == 1)
	// 		{
	// 			mMaininf.mWork.mWorkCheckStatus = 0;
	// 			api_UART5_Display_SendCMDData(1,0xfe,1);
	// 		}
	// 		else if(mMaininf.mWork.mWorkCheckStatus == 2)
	// 		{
	// 			mMaininf.mWork.mWorkCheckStatus = 0;
	// 			api_UART5_Display_SendCMDData(1,mMaininf.mWork.mWorkStep,0);
	// 		}
		}
		else
		{
			if(api_Check_MainBoard_Mode() == 0)
			{
				mMaininf.mWork.mWorkOldI8I9StatusFlag = mMaininf.mWork.mWorkI8I9StatusFlag;
				
				if(mMaininf.mWork.mWorkI8I9StatusFlag == 1)//i8
				{
					api_SendCMD_To_Display(2,2,1,1000,3);
				}
				else if(mMaininf.mWork.mWorkI8I9StatusFlag == 2)//i9
				{
					api_SendCMD_To_Display(2,3,1,1000,3);
				}
			}
		}
	
	}
}

/*****************************************************************************
 * @name       :void api_SendCMD_To_Display(u8 mode,u8 cmd,u8 status)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :send data
 * @parameters :cmd
 * @retvalue   :None
******************************************************************************/
void api_SendCMD_To_Display(u8 mode,u8 cmd,u8 status, u16 waittime,u8 count)
{
	u8 mCont = 0;
	u8 mStatus = 0;
	
	do
	{
		if(++mCont > count)
		{
			return;
		}
		
		api_UART5_Display_SendCMDData(mode,cmd,status);
		mMaininf.mSystem.mDisplayStartTime = api_GetCurrentSystemTime();
		
		while(api_GetSystemTimePeriod(mMaininf.mSystem.mDisplayStartTime) < waittime)
		{
			if((mMaininf.mUart5.mReceiveFlag == 1) && (mMaininf.mUart5.ReceiveBuf[0] == mode) && 
				(mMaininf.mUart5.ReceiveBuf[1] == cmd) && (mMaininf.mUart5.ReceiveBuf[2] == 1))
			{
				mStatus = 1;
				break;
			}
		}
		
		mMaininf.mUart5.mReceiveFlag = 0;
		
	}while(mStatus == 0);
	
	//mMaininf.mUart5.mReceiveFlag = 0;
	
}

/*****************************************************************************
 * @name       :void api_SendCMD_To_MainBoard(u8 seq,u8 mode,u8 cmd,u16 waittime)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :发送命令到主板
 * @parameters :testtype : 0:读取数据   1:检测发射    2:检测接收   waittime:单次检查时间  
				type:类型0：状态  1：数据     num:重发次数   status:检测返回状态  0：检测返回0   1：检测返回1
 * @retvalue   :0:主板无数据返回     1：主板有数据返回
******************************************************************************/
u8 iii;
u8 api_SendCMD_To_MainBoard(u8 seq,u8 mode,u8 cmd,u16 waittime,u8 type,u8 num,u8 status)
{
	u8 mCont = 0;
	u8 mStatus = 0;
	
	mMaininf.mUart1.mReceiveFlag = 0;
	mMaininf.mUart1.ReceiveBuf[4] = 0;
	
	if(type == 0)
	{
		do{
			if(++mCont > num) return 0;//未接收到数据
			api_UART1_MainBoard_SendCMDData(seq,mode,cmd);
			
			mMaininf.mSystem.mMainBoardStartTime = api_GetCurrentSystemTime();
			//vTaskDelay(waittime);
			while(api_GetSystemTimePeriod(mMaininf.mSystem.mMainBoardStartTime) < waittime)
			{
//				if(mMaininf.mUart1.mReceiveFlag == 1)
//				{
//					iii = 1;
//				}
				if((mMaininf.mUart1.mReceiveFlag == 1) && (mMaininf.mUart1.ReceiveBuf[4] == status))
				{
					mStatus = 1;
					break;
				}
			}
			mMaininf.mUart1.mReceiveFlag = 0;
			
// 			#ifndef zbq_Debug
// 			api_UART4_SendData(10,"tmep54-1\r\n");
// 			vTaskDelay(200);
// 			#endif
		}while(mStatus == 0);
		//}while((mMaininf.mUart1.mReceiveFlag == 0) || ((mMaininf.mUart1.mReceiveFlag == 1) && (mMaininf.mUart1.ReceiveBuf[4] == 0)));
		
	}
	else
	{
		do{
			if(++mCont > num) return 0;//未接收到数据
			api_UART1_MainBoard_SendCMDData(seq,mode,cmd);
			mMaininf.mSystem.mMainBoardStartTime = api_GetCurrentSystemTime();
			//vTaskDelay(waittime);
			while(api_GetSystemTimePeriod(mMaininf.mSystem.mMainBoardStartTime) < waittime)
			{
				if(mMaininf.mUart1.mReceiveFlag == 1)
				{
					mStatus = 1;
					break;
				}
			}
			mMaininf.mUart1.mReceiveFlag = 0;
		}while(mStatus == 0);
		
	}
	
	mMaininf.mUart1.mReceiveFlag = 0;
	
	return 1;//接收到数据
}

/*****************************************************************************
 * @name       :u8 Check_MainBoard_Version(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :检测主板版本号
 * @parameters :None
 * @retvalue   :0:读取失败   1:读取成功   
******************************************************************************/
u8 Check_MainBoard_Version(void)
{
	u8 iCont;
	
	for(iCont = 0;iCont < 5;iCont ++)
	{
		mMaininf.mWork.mWorkReadErrorFlag = 0;
		
		if(api_SendCMD_To_MainBoard(0,1,2,500,1,5,1) == 1)
		{
			for(mMaininf.mWork.mWorkReadErrorCont = 0;mMaininf.mWork.mWorkReadErrorCont < 8;mMaininf.mWork.mWorkReadErrorCont++)
			{
				if(mMaininf.mWork.mWorkI8I9StatusFlag == 1)
				{
					mMaininf.mWork.mWorkReadErrorFlag = mMaininf.mWork.mWorkReadErrorFlag | (mMaininf.mUart1.ReceiveBuf[mMaininf.mWork.mWorkReadErrorCont + 4] != xMainBoardVersion[mMaininf.mWork.mWorkReadErrorCont]);
				}
				else
				{
					mMaininf.mWork.mWorkReadErrorFlag = mMaininf.mWork.mWorkReadErrorFlag | (mMaininf.mUart1.ReceiveBuf[mMaininf.mWork.mWorkReadErrorCont + 4] != xMainBoardVersion[mMaininf.mWork.mWorkReadErrorCont + 16]);
				}
			}
			
//			for(mMaininf.mWork.mWorkReadErrorCont = 0;mMaininf.mWork.mWorkReadErrorCont < 4;mMaininf.mWork.mWorkReadErrorCont++)
//			{
//				if(mMaininf.mWork.mWorkI8I9StatusFlag == 1)
//				{
//					mMaininf.mWork.mWorkReadErrorFlag = mMaininf.mWork.mWorkReadErrorFlag | (mMaininf.mUart1.ReceiveBuf[mMaininf.mWork.mWorkReadErrorCont + 16] != xMainBoardVersion[mMaininf.mWork.mWorkReadErrorCont + 12]);
//				}
//				else
//				{
//					mMaininf.mWork.mWorkReadErrorFlag = mMaininf.mWork.mWorkReadErrorFlag | (mMaininf.mUart1.ReceiveBuf[mMaininf.mWork.mWorkReadErrorCont + 16] != xMainBoardVersion[mMaininf.mWork.mWorkReadErrorCont + 28]);
//				}
//			}
			
			if(mMaininf.mWork.mWorkReadErrorFlag == 0)
			{
				return 1;
// 				if(mMaininf.mWork.mWorkI8I9StatusFlag == 1)//i8
// 				{
// 					mMaininf.mWork.mWorkStep = TEST_SIDE_A_SEND;
// 				}
// 				else//i9
// 				{
// 					mMaininf.mWork.mWorkStep = TEST_TOF_POWER;
// 				}
// 				//mMaininf.mWork.mWorkStep = 0;
			}
		}
		vTaskDelay(1000);
	}
	
	return 0;
}


