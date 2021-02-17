/****************************************************************************************************/
/*			@FileName		:	bsp.c														    	*/
/*			@Author			:	zhengbaiqiu															*/
/*			@Version		:	v1.0																*/
/*			@Date			:	2019.11.12  														*/
/****************************************************************************************************/


/* Includes --------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include <string.h>

/* Project ---------------------------------------------------------------------*/
#include "bsp.h"
//#include "delay.h"
#include "apiLib.h"

/* Variable --------------------------------------------------------------------*/

/* Function --------------------------------------------------------------------*/
void prvSetupHardware(void);
void TIM1_PWM_Configure(u16 arr,u16 pre);




/*****************************************************************************
 * @name       :void NVIC_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :nvic configuration
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void NVIC_Configure(void)
{
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);            //  16�������ȼ�    0��Ӧ���ȼ�
}

/*****************************************************************************
 * @name       :u8 HSI_SystemClock(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :HSI SystemClock configuration
 * @parameters :None
 * @retvalue   :0:fail    1:pass      
******************************************************************************/
u8 HSI_SystemClock(void)
{
	u8 sta;
	RCC_HSICmd(ENABLE);
	sta=RCC_GetFlagStatus(RCC_FLAG_HSIRDY);
	if(sta==RESET)return 0;
	else
	{
		RCC_PLLConfig(RCC_PLLSource_HSI_Div2,RCC_PLLMul_9);         //PLL36MHz
		RCC_PLLCmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
		{
		}
		sta=RCC_GetFlagStatus(RCC_FLAG_PLLRDY);
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);                  //SYSCLK36MHz
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);                            //AHBʱ�ӵ���ϵͳʱ��                  36M
		RCC_PCLK1Config(RCC_HCLK_Div1);                             //����AHBʱ��APB1����AHBʱ�ӵ�һ��     36M
		RCC_PCLK2Config(RCC_HCLK_Div1);                             //����AHBʱ��APB2����AHBʱ��           36M
		return 1;
	}
		
}

/*****************************************************************************
 * @name       :void HSE_SystemClock(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :HSE SystemClock configuration
 * @parameters :None
 * @retvalue   :None  
******************************************************************************/
void HSE_SystemClock(void)
{
	RCC_DeInit();
	
	RCC_HSEConfig(RCC_HSE_ON);
	HSEStartUpStatus=RCC_WaitForHSEStartUp();
	if(HSEStartUpStatus==0)
	{
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1,RCC_PLLMul_9);               //            72M        
		RCC_PLLCmd(ENABLE);
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY)==RESET)
		{
		}
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
		
		RCC_HCLKConfig(RCC_SYSCLK_Div1);         //AHBʱ�ӵ���ϵͳʱ��                  72M
		RCC_PCLK1Config(RCC_HCLK_Div2);          //����AHBʱ��APB1����AHBʱ�ӵ�һ��     36M
		RCC_PCLK2Config(RCC_HCLK_Div1);          //����AHBʱ��APB2����AHBʱ��           72M
	}
	
}

/*****************************************************************************
 * @name       :void RCC_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :RCC configuration
 * @parameters :None
 * @retvalue   :None  
******************************************************************************/
void RCC_Configure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable peripheral clocks ------------------------------------------------*/
	/* Enable AHB clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);

	/* Enable APB1 clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 | RCC_APB1Periph_TIM3 | RCC_APB1Periph_TIM4 | 
												 RCC_APB1Periph_TIM6 | RCC_APB1Periph_USART2 | RCC_APB1Periph_USART3 | 
												 RCC_APB1Periph_UART4 | RCC_APB1Periph_UART5 | RCC_APB1Periph_WWDG,ENABLE);
	
	/* Enable APB2 clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC | 
												  RCC_APB2Periph_GPIOD | RCC_APB2Periph_GPIOE | 
												  RCC_APB2Periph_GPIOF | RCC_APB2Periph_GPIOG | 
												  RCC_APB2Periph_AFIO | RCC_APB2Periph_TIM1 | RCC_APB2Periph_USART1, ENABLE);
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	/* Enable GPIO */
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_All;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_Init(GPIOC, &GPIO_InitStructure);
	GPIO_Init(GPIOD, &GPIO_InitStructure);
	GPIO_Init(GPIOE, &GPIO_InitStructure);
	GPIO_Init(GPIOF, &GPIO_InitStructure);
	GPIO_Init(GPIOG, &GPIO_InitStructure);
}

/*****************************************************************************
 * @name       :void IWDG_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :IWDG configuration
 * @parameters :None
 * @retvalue   :None  
******************************************************************************/
void IWDG_Configure(void)
{
	IWDG_WriteAccessCmd(IWDG_WriteAccess_Enable);
	IWDG_SetPrescaler(IWDG_Prescaler_256);
	IWDG_SetReload(0xFFF);
	IWDG_Enable();
}

/*****************************************************************************
 * @name       :void Systick_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :Systick configuration
 * @parameters :None
 * @retvalue   :None  
******************************************************************************/
void Systick_Configure(void)                             //1ms
{
	if(SysTick_Config(SystemCoreClock/1000))
	while(1);
}

/*****************************************************************************
 * @name       :void TIM2_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :TIM2 configuration
 * @parameters :None
 * @retvalue   :None  
******************************************************************************/
void TIM2_Configure(void)                                      //1ms interrupt
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_TimeBaseStructure.TIM_Period =99;
	TIM_TimeBaseStructure.TIM_Prescaler =(720-1);
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =TIM2_TIME_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
	
	TIM_Cmd(TIM2,ENABLE);
}

/*****************************************************************************
 * @name       :void TIM3_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :TIM3 configuration
 * @parameters :None
 * @retvalue   :None  
******************************************************************************/
void TIM3_Configure(void)                                //TIME interupt          200us
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_TimeBaseStructure.TIM_Period =19;
	TIM_TimeBaseStructure.TIM_Prescaler =(720-1);
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3,&TIM_TimeBaseStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =TIM3_TIME_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM3,TIM_IT_Update,ENABLE);
	
//	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM3,DISABLE);
}

/*****************************************************************************
 * @name       :void TIM4_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :TIM3 configuration
 * @parameters :None
 * @retvalue   :None  
******************************************************************************/
void TIM4_Configure(void)                                //TIME interupt          10us
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	TIM_TimeBaseStructure.TIM_Period =9;
	TIM_TimeBaseStructure.TIM_Prescaler =71;
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =TIM4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =TIM4_TIME_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	TIM_ITConfig(TIM4,TIM_IT_Update,ENABLE);
	
//	TIM_Cmd(TIM4,ENABLE);
	TIM_Cmd(TIM4,DISABLE);
}

/*****************************************************************************
 * @name       :void GPIO_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :gpio configuration
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void GPIO_Configure(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/******************system configure*******************/
 	GPIO_InitStructure.GPIO_Pin = /*GPIO_Pin_0 | */GPIO_Pin_8;//tof power reset
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_15;//������
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA, &GPIO_InitStructure);
	PAout(11) = 0;
	PAout(12) = 0;
	PAout(15) = 0;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_9;//���ر߽���
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	PBout(4) = 0;
	PBout(5) = 0;
	PBout(6) = 0;
	PBout(7) = 0;
	PBout(9) = 0;
	PBout(1) = 1;
	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9;//����ײB�ź� ����ײA�ź� �ر�B�ź� �ر�A�ź�
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_13;//����ײ�������ҡ�ǰ
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOC, &GPIO_InitStructure);
	PCout(0) = 1;
	PCout(1) = 1;
	PCout(2) = 1;
	PCout(3) = 1;
	PCout(4) = 1;
	PCout(5) = 1;
	PCout(13) = 1;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_7;//ˮ����� �ŵ���� ����������� ��ˢ����  �����Ǽ̵���
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure);
	PDout(0) = 0;
	PDout(1) = 0;
	PDout(3) = 0;
	PDout(4) = 0;
	PDout(7) = 0;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | //�ҡ��������ּ��
								  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;//�ҡ������̹����� �ҡ�����ײ���硢�ر߹���
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6;//���м�� ��������� ����ҡ���  ��ײ�ҡ�����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure);
	PEout(0) = 1;
	PEout(1) = 0;
	PEout(2) = 0;//zbq�Ժ�Ҫ��
	PEout(3) = 1;
	PEout(4) = 1;
	PEout(5) = 1;
	PEout(6) = 1;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15 | GPIO_Pin_9 | GPIO_Pin_13 | GPIO_Pin_14;//���й���   ����  �������PWM����  i8 DC5V
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOF, &GPIO_InitStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | 
								  GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_10 | GPIO_Pin_11;//
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOF, &GPIO_InitStructure);
	PFout(1) = 1;
	PFout(2) = 1;
	PFout(3) = 1;
	PFout(4) = 1;
	PFout(5) = 1;
	PFout(6) = 1;
	PFout(7) = 1;
	PFout(8) = 1;
	PFout(10) = 1;
	PFout(11) = 1;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;//key3\2\1����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure);
	PGout(12) = 0;
	PGout(13) = 0;
	PGout(14) = 0;
	PGout(15) = 0;
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8;//�ҳ������� �����  BAT+  ����������䲨�μ��  ��ǰ���ҡ������Ӳ��μ���
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure);
	
// 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
// 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
// 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
// 	GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/*****************************************************************************
 * @name       :void UART1_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :uart1 configure
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void UART1_Configure(void)//����
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* USART1_TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
    
    /* USART1_RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate =115200;
	USART_InitStructure.USART_WordLength =USART_WordLength_8b;
	USART_InitStructure.USART_StopBits =USART_StopBits_1;
	USART_InitStructure.USART_Parity =USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode =USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART1,&USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =UART1_MAINBOARD_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART1,ENABLE);
}

/*****************************************************************************
 * @name       :void UART3_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :uart3 configure
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void UART3_Configure(void)//��˴���
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* USART3_TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
    
    /* USART3_RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate =115200;
	USART_InitStructure.USART_WordLength =USART_WordLength_8b;
	USART_InitStructure.USART_StopBits =USART_StopBits_1;
	USART_InitStructure.USART_Parity =USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode =USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART3,&USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =UART3_BIGBOARD_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(USART3,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(USART3,ENABLE);
}

/*****************************************************************************
 * @name       :void UART4_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :gpio configuration
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void UART4_Configure(void)//DEBUG
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* USART4_TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    /* USART4_RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate =115200;
	USART_InitStructure.USART_WordLength =USART_WordLength_8b;
	USART_InitStructure.USART_StopBits =USART_StopBits_1;
	USART_InitStructure.USART_Parity =USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode =USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(UART4,&USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =UART4_DEBUG_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(UART4,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(UART4,ENABLE);
}

/*****************************************************************************
 * @name       :void UART5_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :gpio configuration
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void UART5_Configure(void)//��ʾ
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	/* USART5_TX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOC, &GPIO_InitStructure);
    
    /* USART5_RX */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOD, &GPIO_InitStructure);
	
	USART_InitStructure.USART_BaudRate =115200;
	USART_InitStructure.USART_WordLength =USART_WordLength_8b;
	USART_InitStructure.USART_StopBits =USART_StopBits_1;
	USART_InitStructure.USART_Parity =USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode =USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(UART5,&USART_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel =UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority =UART5_DISPLAY_PRIORITY;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority =0;
	NVIC_InitStructure.NVIC_IRQChannelCmd =ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_ITConfig(UART5,USART_IT_RXNE,ENABLE);
	
	USART_Cmd(UART5,ENABLE);
}

/*****************************************************************************
 * @name       :void ADC1_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :ADC1 configuration
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void ADC1_Configure(void)//TOF��Դ���
{
	GPIO_InitTypeDef GPIO_InitStructure;
	DMA_InitTypeDef DMA_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div4);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE );
	
 	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2;          
 	GPIO_InitStructure.GPIO_Mode =GPIO_Mode_AIN;
 	GPIO_InitStructure.GPIO_Speed =GPIO_Speed_50MHz;
 	GPIO_Init(GPIOA,&GPIO_InitStructure);

	/* DMA1 channel1 configuration ----------------------------------------------*/
	DMA_DeInit(DMA1_Channel1);
	DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&ADC1->DR);
	DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)&ADCValue;
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;
	DMA_InitStructure.DMA_BufferSize = 3;
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_High;
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
	DMA_Init(DMA1_Channel1, &DMA_InitStructure);

	/* Enable DMA1 channel1 */
	DMA_Cmd(DMA1_Channel1, ENABLE);

	/* ADC1 configuration ------------------------------------------------------*/
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	ADC_InitStructure.ADC_ScanConvMode = ENABLE;
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_InitStructure.ADC_NbrOfChannel = 3;
	ADC_Init(ADC1, &ADC_InitStructure);

	/* ADC1 regular channel14 configuration */ 
	ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_1, 2, ADC_SampleTime_55Cycles5);
	ADC_RegularChannelConfig(ADC1, ADC_Channel_2, 3, ADC_SampleTime_55Cycles5);

	/* Enable ADC1 DMA */
	ADC_DMACmd(ADC1, ENABLE);

	/* Enable ADC1 */
	ADC_Cmd(ADC1, ENABLE);

	/* Enable ADC1 reset calibration register */   
	ADC_ResetCalibration(ADC1);
	/* Check the end of ADC1 reset calibration register */
	while(ADC_GetResetCalibrationStatus(ADC1));

	/* Start ADC1 calibration */
	ADC_StartCalibration(ADC1);
	/* Check the end of ADC1 calibration */
	while(ADC_GetCalibrationStatus(ADC1));
	 
	/* Start ADC1 Software Conversion */ 
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}

/*****************************************************************************
 * @name       :void PWM_Configure(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :pwm configuration
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void TIM1_PWM_Configure(u16 arr,u16 pre)//38k�ز� arr = 26  pre = 71   ����ײ500hz 10%ռ�ձ�  arr = 200  pre = 719
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	
	GPIO_PinRemapConfig(GPIO_PartialRemap_TIM1, ENABLE);     //   TIM1 ������ӳ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	/* Time Base configuration */
	TIM_TimeBaseStructure.TIM_Period =arr;                           //    ��������ֵ     0x0000-0xffff
	TIM_TimeBaseStructure.TIM_Prescaler =pre;                 //    ��Ƶֵ         0x0000-0xffff
	TIM_TimeBaseStructure.TIM_ClockDivision =TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode =TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM1,&TIM_TimeBaseStructure);
	
	/* Channel 1, 2,3 and 4 Configuration in PWM mode */
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;      //  ��ʼ�ߵ�ƽʱ   PWM1 : ��ʱ��С�ڱȽ����趨ֵ�����  PWM2 : ��ʱ��С�ڱȽ����趨ֵ�����
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;              //   �������   ��ʼ��ƽΪ�ߵ�ƽ
	TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
	TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Reset;
	TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCNIdleState_Reset;
	
	TIM_OC2Init(TIM1, &TIM_OCInitStructure);	
	TIM_OC2PreloadConfig(TIM1, TIM_OCPreload_Enable);
	
	/* TIM1 counter enable */
	TIM_Cmd(TIM1, ENABLE);

	/* TIM1 Main Output Enable */
	TIM_CtrlPWMOutputs(TIM1, ENABLE);
}

/*****************************************************************************
 * @name       :void BSP_Init(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :Chip configuration
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void BSP_Init(void)
{
	NVIC_Configure();
//	HSE_SystemClock();
//	HSI_SystemClock();
	RCC_Configure();
	IWDG_Configure();
	GPIO_Configure();
	TIM2_Configure();
	TIM3_Configure();
	TIM4_Configure();
 	ADC1_Configure();
// 	TIM1_PWM_Configure(26,71);
	UART1_Configure();
	UART3_Configure();
	UART4_Configure();
	UART5_Configure();
}

/*****************************************************************************
 * @name       :void Param_Init(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :Parameter initialization
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Param_Init(void)
{
	//    ʱ�����
	mMaininf.mSystem.mSystemTick = 0;
	mMaininf.mSystem.mPowerOnStartTime = 0;
	
	mMaininf.mSystem.mSystem200usTick = 0;
	mMaininf.mSystem.mSystem10usTick = 0;
	
	mMaininf.mSystem.mMainBoardStartTime = 0;
	mMaininf.mSystem.mDisplayStartTime = 0;
	
	//    �������
	//UART1
	memset(mMaininf.mUart1.TxBuffer, 0, sizeof(mMaininf.mUart1.TxBuffer));     //  int arr[10]={0};
	memset(mMaininf.mUart1.RxBuffer, 0, sizeof(mMaininf.mUart1.RxBuffer));
	memset(mMaininf.mUart1.SendBuf, 0, sizeof(mMaininf.mUart1.SendBuf));
	memset(mMaininf.mUart1.ReceiveBuf, 0, sizeof(mMaininf.mUart1.ReceiveBuf));
	
	mMaininf.mUart1.mSendSize = 0;
	mMaininf.mUart1.mSendCont = 0;
	mMaininf.mUart1.mReceiveStep = ST_0x55;
	mMaininf.mUart1.mReceiveBCC = 0;
	mMaininf.mUart1.mReceiveSize = 0;
	mMaininf.mUart1.mReceiveCont = 0;
	mMaininf.mUart1.mReceiveTimeOut = 0;
	mMaininf.mUart1.mReceiveFlag = 0;      //    û�н��յ�����
	//UART4
	memset(mMaininf.mUart4.TxBuffer, 0, sizeof(mMaininf.mUart4.TxBuffer));     //  int arr[10]={0};
	memset(mMaininf.mUart4.RxBuffer, 0, sizeof(mMaininf.mUart4.RxBuffer));
	memset(mMaininf.mUart4.SendBuf, 0, sizeof(mMaininf.mUart4.SendBuf));
	memset(mMaininf.mUart4.ReceiveBuf, 0, sizeof(mMaininf.mUart4.ReceiveBuf));
	
	mMaininf.mUart4.mSendSize = 0;
	mMaininf.mUart4.mSendCont = 0;
	mMaininf.mUart4.mReceiveStep = ST_0x55;
	mMaininf.mUart4.mReceiveBCC = 0;
	mMaininf.mUart4.mReceiveSize = 0;
	mMaininf.mUart4.mReceiveCont = 0;
	mMaininf.mUart4.mReceiveTimeOut = 0;
	mMaininf.mUart4.mReceiveFlag = 0;      //    û�н��յ�����
	//UART5
	memset(mMaininf.mUart5.TxBuffer, 0, sizeof(mMaininf.mUart5.TxBuffer));     //  int arr[10]={0};
	memset(mMaininf.mUart5.RxBuffer, 0, sizeof(mMaininf.mUart5.RxBuffer));
	memset(mMaininf.mUart5.SendBuf, 0, sizeof(mMaininf.mUart5.SendBuf));
	memset(mMaininf.mUart5.ReceiveBuf, 0, sizeof(mMaininf.mUart5.ReceiveBuf));
	
	mMaininf.mUart5.mSendSize = 0;
	mMaininf.mUart5.mSendCont = 0;
	mMaininf.mUart5.mReceiveStep = ST_0x55;
	mMaininf.mUart5.mReceiveBCC = 0;
	mMaininf.mUart5.mReceiveSize = 0;
	mMaininf.mUart5.mReceiveCont = 0;
	mMaininf.mUart5.mReceiveTimeOut = 0;
	mMaininf.mUart5.mReceiveFlag = 0;      //    û�н��յ�����
	
	
	//    �������
	mMaininf.mWork.mWorkInitFlag = 0;
	mMaininf.mWork.mWorkChecking = 0;
	mMaininf.mWork.mWorkCheckStatus = 0;
	
	mMaininf.mWork.mWorkStep = 0;
	mMaininf.mWork.mWorkStepOld = 0;
	mMaininf.mWork.mWorkFileStep = 0;
	
	mMaininf.mWork.mWorkGuideSendFlag = 0;
	mMaininf.mWork.mWorkGuideSendStep = 0;
	mMaininf.mWork.mWorkGuideSendCont = 0;
	mMaininf.mWork.mWorkGuide[0].Flag = 0;
	mMaininf.mWork.mWorkGuide[0].Status = 0;
	mMaininf.mWork.mWorkGuide[1].Flag = 0;
	mMaininf.mWork.mWorkGuide[1].Status = 0;
	mMaininf.mWork.mWorkGuide[2].Flag = 0;
	mMaininf.mWork.mWorkGuide[2].Status = 0;
	mMaininf.mWork.mWorkGuide[3].Flag = 0;
	mMaininf.mWork.mWorkGuide[3].Status = 0;
	mMaininf.mWork.mWorkGuide[4].Flag = 0;
	mMaininf.mWork.mWorkGuide[4].Status = 0;
	
	mMaininf.mWork.mWorkKeyPressFlag = 0;
	mMaininf.mWork.mWorkKeyPressFlag1 = 0;
	mMaininf.mWork.mWorkKeyCont = 0;
	
	mMaininf.mWork.mWorkI8KeyPressFlag = 0;
	mMaininf.mWork.mWorkI8KeyPressFlag1 = 0;
	mMaininf.mWork.mWorkI8KeyCont = 0;
	mMaininf.mWork.mWorkI8KeyCont1 = 0;
	
	mMaininf.mWork.mWorkI9KeyPressFlag = 0;
	mMaininf.mWork.mWorkI9KeyPressFlag1 = 0;
	mMaininf.mWork.mWorkI9KeyCont = 0;
	mMaininf.mWork.mWorkI9KeyCont1 = 0;
	
	mMaininf.mWork.mWorkI8I9StatusFlag = 0;
	mMaininf.mWork.mWorkOldI8I9StatusFlag = 0;
	
	mMaininf.mWork.mWorkAlongSideReadVal = 0;
	mMaininf.mWork.mWorkAvoidBumpReadVal = 0;
	mMaininf.mWork.mWorkDropReadVal = 0;
	mMaininf.mWork.mWorkDropReadVal1 = 0;
	mMaininf.mWork.mWorkDropReadVal2 = 0;
	mMaininf.mWork.mWorkDropPhaseReadVal = 0;
	mMaininf.mWork.mWorkDropPhaseReadVal1 = 0;
	mMaininf.mWork.mWorkDropReadBaseVal = 0;
	mMaininf.mWork.mWorkCodeReadVal = 0;
	mMaininf.mWork.mWorkDustReadVal = 0;
	mMaininf.mWork.mWorkRollBrushCurrentVal = 0;
	mMaininf.mWork.mWorkVacuumCurrentVal = 0;
	mMaininf.mWork.mWorkGyroVoltageVal = 0;
	mMaininf.mWork.mWorkWaterTankVoltageVal = 0;
	mMaininf.mWork.mWorkNTCVoltageVal = 0;
	mMaininf.mWork.mWorkChargeVoltageVal = 0;
	mMaininf.mWork.mWorkBatteryPowerVoltageVal = 0;
	
	mMaininf.mWork.mWorkCodeSendFlag = 0;
	mMaininf.mWork.mWorkCodeSendCont = 0;
	
	mMaininf.mWork.mWorkDropSendFlag = 0;
	mMaininf.mWork.mWorkDropSendCont = 0;
	
	mMaininf.mWork.mWorkBigUartFlag = 0;
	
	mMaininf.mWork.mWorkReadErrorFlag = 0;
	mMaininf.mWork.mWorkReadErrorCont = 0;
	
	mMaininf.mWork.mWorkChangePhaseFlag = 0;
	mMaininf.mWork.mWorkReadTimeCont = 0;
	
	mMaininf.mWork.mWorkCheckErrorFlag = 0;
	mMaininf.mWork.mWorkChargeCheckFlag = 0;
	mMaininf.mWork.mWorkChargeCheckCurFlag = 0;
	
	mMaininf.mWork.mWorkTestADC = 0;
}

/*****************************************************************************
 * @name       :void prvSetupHardware(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :Initialize the chip
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void prvSetupHardware(void)
{
	BSP_Init();
	Param_Init();
}



// /*--------------------------------------------------------------------------

//         ��ӡlog

// ---------------------------------------------------------------------------*/



// /*-----------------------------------------------------------------------*/
// /* UART1��������                                                         */
// /*-----------------------------------------------------------------------*/


// void UART1_Configure(void)
// {
// 	GPIO_InitTypeDef GPIO_InitStructure;
// 	USART_InitTypeDef USART_InitStructure;
// 	
// 	/* USART1_TX */
//     GPIO_InitStructure.GPIO_Pin = DEBUG_UART_TX_PIN;
//     GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
// 	GPIO_Init(DEBUG_UART_GPIO, &GPIO_InitStructure);
//     
//     /* USART1_RX */
//     GPIO_InitStructure.GPIO_Pin = DEBUG_UART_RX_PIN;
//     GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
//     GPIO_Init(DEBUG_UART_GPIO, &GPIO_InitStructure);
// 	
// 	USART_InitStructure.USART_BaudRate =115200;
// 	USART_InitStructure.USART_WordLength =USART_WordLength_8b;
// 	USART_InitStructure.USART_StopBits =USART_StopBits_1;
// 	USART_InitStructure.USART_Parity =USART_Parity_No;
// 	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
// 	USART_InitStructure.USART_Mode =USART_Mode_Rx|USART_Mode_Tx;
// 	USART_Init(USART1,&USART_InitStructure);
// 	
// 	USART_Cmd(USART1,ENABLE);
// }


// int fputc(int ch, FILE *f)
// {
//   USART_SendData(USART1, (uint8_t) ch);
//   /* Loop until the end of transmission */
//   while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET)
//   {}
//   return ch;
// }

// int fgetc(FILE *f)
// {
//   
//    while(!(USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == SET))
//    {
//    }
//   
//     
//    return (USART_ReceiveData(USART1));
// }

// void assert_failed(u8* file, u32 line)
// {
//     /* User can add his own implementation to report the file name and line number,
//      ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
//     /* Infinite loop */
//     printf("assert failed at %s:%d \n", file, line);
//     while (1) {
//     }
// }

// void delay(uint32_t nCount)
// {
//   for(; nCount!= 0;nCount--);
// }










