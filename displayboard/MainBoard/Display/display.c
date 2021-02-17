/****************************************************************************************************/
/*			@FileName		:	display.c															  	*/
/*			@Author			:	zhengbaiqiu															*/
/*			@Version		:	v1.0																*/
/*			@Date			:	2019.11.12  														*/
/****************************************************************************************************/


/* Includes --------------------------------------------------------------------*/
#include "stm32f10x.h"

/* Project ---------------------------------------------------------------------*/
#include "maindef.h"
//#include "font.h"
#include "lcd_driver.h"	
#include "gui.h"	
#include "delay.h"
#include "display.h"
#include "apiLib.h"

/* Variable --------------------------------------------------------------------*/
extern u16 Touch_X;
extern u16 Touch_Y;

u8 mpass[4] = {0,1,2,2};

/* Function --------------------------------------------------------------------*/
void DrawTestPage(u8 *str);
void Test_Display(void);





/*****************************************************************************
 * @name       :void DrawTestPage(u8 *str)
 * @date       :2018-08-09 
 * @function   :Drawing test interface
 * @parameters :str:the start address of the Chinese and English strings
 * @retvalue   :None
******************************************************************************/ 
void DrawTestPage(u8 *str)
{
	//���ƹ̶���up
	//LCD_Clear(WHITE);
	LCD_Clear(GRAY0);
	LCD_Fill(0,0,lcddev.width,20,BLUE);
// 	LCD_Fill(0,20,lcddev.width,40,YELLOW);
	//���ƹ̶���down
	LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
	POINT_COLOR=WHITE;
	//POINT_COLOR=GRAY0;
	Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);//������ʾ
// 	Gui_StrCenters(96,22,BLACK,YELLOW,"�����",16,1);//������ʾ
// 	Gui_StrCenters(336,22,BLACK,YELLOW,"�����",16,1);//������ʾ
	//Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"http://www.zbq.com",16,1);//������ʾ
	Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"�밴��ʾ����",16,1);//������ʾ
	//���Ʋ�������
	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

/*****************************************************************************
 * @name       :void Display_Fail(u8 item,u8 position)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :��ʾ����
 * @parameters :item����ʾ��һ�����    position��λ��
 * @retvalue   :None
******************************************************************************/
void Display_Fail(u8 item,u8 position)
{
	u16 mpos;
	
	if(position < 10)
	{
		switch(position)
		{
			case 0 :
				mpos = 50;
				break;
			case 1 :
				mpos = 74;
				break;
			case 2 :
				mpos = 98;
				break;
			case 3 :
				mpos = 122;
				break;
			case 4 :
				mpos = 146;
				break;
			case 5 :
				mpos = 170;
				break;
			case 6 :
				mpos = 194;
				break;
			case 7 :
				mpos = 218;
				break;
			case 8 :
				mpos = 242;
				break;
			case 9 :
				mpos = 266;
				break;
			default :
				break;
		}
		
		switch(item)
		{
			case TEST_START ://01
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����ͨѶ");
				break;
			case TEST_START_VERSION ://02
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�汾��");
				break;
			case TEST_TOF_POWER ://03
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"TOF����");
				break;
			case TEST_TOF_COMMUNICATION ://04
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"TOFͨѶ");
				break;
			case TEST_TOF_RESET ://05
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"TOF��λ");
				break;
			case TEST_SIDE_A_SEND ://06
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�ر߷���A");
				break;
			case TEST_SIDE_B_SEND ://07
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�ر߷���B");
				break;
			case TEST_LEFT_SIDE_REC ://08
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"���ر߽���");
				break;
			case TEST_RIGHT_SIDE_REC ://09
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"���ر߽���");
				break;
			case TEST_LEFT_GUIDE ://10
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����������");
				break;
			case TEST_RIGHT_GUIDE ://11
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����������");
				break;
			case TEST_TOP_GUIDE ://12
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����������");
				break;
			case TEST_FRONT_GUIDE ://13
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"ǰ��������");
				break;
			case TEST_LATE_GUIDE ://14
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����������");
				break;
			case TEST_GUIDE_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"��������");
				break;
			case TEST_AVOIDBUMP_A_SEND ://15
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����ײA����");
				break;
			case TEST_AVOIDBUMP_B_SEND ://16
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����ײB����");
				break;
			case TEST_LEFT_AVOIDBUMP_REC ://17
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"������ײ����");
				break;
			case TEST_RIGHT_AVOIDBUMP_REC ://18
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"������ײ����");
				break;
			case TEST_FRONT_AVOIDBUMP_REC ://19
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"ǰ����ײ����");
				break;
			case TEST_GYRO ://20
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"������");
				break;
			case TEST_KEY1 ://21
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����1");
				break;
			case TEST_KEY2 ://22
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����2");
				break;
			case TEST_KEY3 ://23
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����3");
				break;
			case TEST_DROP_SEND_LEFT ://24
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����ӷ���");
				break;
			case TEST_DROP_SEND_RIGHT :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����ӷ���");
				break;
			case TEST_DROP_SEND_FRONT :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"ǰ���ӷ���");
				break;
			case TEST_DROP_SEND_LATE :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����ӷ���");
				break;
			case TEST_LEFT_DROP_REC ://25
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����ӽ���");
				break;
			case TEST_RIGHT_DROP_REC ://26
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����ӽ���");
				break;
			case TEST_FRONT_DROP_REC ://27
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"ǰ���ӽ���");
				break;
			case TEST_LATE_DROP_REC ://28
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����ӽ���");
				break;
			case TEST_LEFT_BUMP ://29
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����ײ����");
				break;
			case TEST_LEFT_BUMP_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����ײ����");
				break;
			case TEST_RIGHT_BUMP ://30
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����ײ����");
				break;
			case TEST_RIGHT_BUMP_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����ײ����");
				break;
			case TEST_LEFT_LEAVELAND ://31
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����ؽ���");
				break;
			case TEST_RIGHT_LEAVELAND ://32
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����ؽ���");
				break;
			case TEST_LEFT_WHEEL_FEEDBACK ://33
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����̽���");
				break;
			case TEST_LEFT_WHEEL_FEEDBACK_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����̹���");
				break;
			case TEST_RIGHT_WHEEL_FEEDBACK ://34
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����̽���");
				break;
			case TEST_RIGHT_WHEEL_FEEDBACK_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����̹���");
				break;
			case TEST_LEFT_WHEEL ://35
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����");
				break;
			case TEST_RIGHT_WHEEL ://36
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�Ҵ���");
				break;
			case TEST_ROLLBURSH_CUR_FEEDBACK ://37
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"��ˢ");
				break;
			case TEST_VACUUM_FEEDBACK ://38
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"����������");
				break;
			case TEST_VACUUM_CONTROL ://39
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����������");
				break;
			case TEST_DISCHARGE_CUR_FEEDBACK ://40
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����");
				break;
			case TEST_POWER_NTC ://41
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"NTC");
				break;
			case TEST_OPEN_KEY ://42
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"������");
				break;
			case TEST_DUST_REC ://43
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�ҳ����");
				break;
			case TEST_DUST_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�ҳ�����������");
				break;
			case TEST_DUSTCUP_REC ://44
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"���м��");
				break;
			case TEST_DUSTCUP_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"���д���������");
				break;
			case TEST_WATERTANK ://45
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"ˮ����");
				break;
			case TEST_POSITION_CAMERA ://46
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"��λ����ͷ");
				break;
			case TEST_POSITION_CAMERA_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"��λ����ͷ����");
				break;
			case TEST_DC5V :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"DC5V���");
				break;
			case TEST_DC5V_I8 :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"DC5V-I8���");
				break;
			case TEST_PATHPLAN_UART ://47
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"��˴���");
				break;
			case TEST_WIFI ://48
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"WIFI");
				break;
			case TEST_BATTERY ://49
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"��ص���");
				break;
			case TEST_CHARGE ://50
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"�����");
				break;
			case TEST_POWER_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"OVP");
				break;
			default :
				break;
		}
	}
}

/*****************************************************************************
 * @name       :void Display_I8_Test(u8 test_mode,u8 test_cmd,u8 test_status)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :display test
 * @parameters :test_cmd ��ȡ����������
 * @retvalue   :None
******************************************************************************/
void Display_I8_Test(u8 test_mode,u8 test_cmd,u8 test_status)
{
	switch(test_cmd)
	{
		case TEST_START ://01
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"����ͨѶ");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"����ͨѶ");
				Display_Fail(TEST_START,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_START_VERSION ://02
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"�汾��");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"�汾��");
				Display_Fail(TEST_START_VERSION,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_TOF_POWER ://03
			if(test_status == 1)
			{
				
			}
			else
			{
				
			}
			break;
		case TEST_TOF_COMMUNICATION ://04
			if(test_status == 1)
			{
				
			}
			else
			{
				
			}
			break;
		case TEST_TOF_RESET ://05
			if(test_status == 1)
			{
				
			}
			else
			{
				
			}
			break;
		case TEST_SIDE_A_SEND ://06
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"�ر߷���A");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"�ر߷���A");
				Display_Fail(TEST_SIDE_A_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_SIDE_B_SEND ://07
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"�ر߷���B");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"�ر߷���B");
				Display_Fail(TEST_SIDE_B_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_SIDE_REC ://08
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"���ر߽���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"���ر߽���");
				Display_Fail(TEST_LEFT_SIDE_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_SIDE_REC ://09
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"���ر߽���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"���ر߽���");
				Display_Fail(TEST_RIGHT_SIDE_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_GUIDE ://10
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"����������");
				Display_Fail(TEST_LEFT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_GUIDE ://11
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"����������");
				Display_Fail(TEST_RIGHT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_TOP_GUIDE ://12
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"����������");
				Display_Fail(TEST_TOP_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_GUIDE ://13
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"ǰ��������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"ǰ��������");
				Display_Fail(TEST_FRONT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_LATE_GUIDE ://14
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"����������");
				Display_Fail(TEST_LATE_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_GUIDE_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"��������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"��������");
				Display_Fail(TEST_GUIDE_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_AVOIDBUMP_A_SEND ://15
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"����ײA����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"����ײA����");
				Display_Fail(TEST_AVOIDBUMP_A_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_AVOIDBUMP_B_SEND ://16
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"����ײB����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"����ײB����");
				Display_Fail(TEST_AVOIDBUMP_B_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_AVOIDBUMP_REC ://17
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"������ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"������ײ����");
				Display_Fail(TEST_LEFT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_AVOIDBUMP_REC ://18
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"������ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"������ײ����");
				Display_Fail(TEST_RIGHT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_AVOIDBUMP_REC ://19
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"ǰ����ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"ǰ����ײ����");
				Display_Fail(TEST_FRONT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_GYRO ://20
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"������");
				Display_Fail(TEST_GYRO,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_KEY1 ://21
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"����1");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"����1");
				Display_Fail(TEST_KEY1,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_KEY2 ://22
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"����2");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"����2");
				Display_Fail(TEST_KEY2,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_KEY3 ://23
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"����3");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"����3");
				Display_Fail(TEST_KEY3,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_LEFT ://24
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"�����ӷ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"�����ӷ���");
				Display_Fail(TEST_DROP_SEND_LEFT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_RIGHT :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"�����ӷ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"�����ӷ���");
				Display_Fail(TEST_DROP_SEND_RIGHT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_FRONT :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"ǰ���ӷ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"ǰ���ӷ���");
				Display_Fail(TEST_DROP_SEND_FRONT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_LATE :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"�����ӷ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"�����ӷ���");
				Display_Fail(TEST_DROP_SEND_LATE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_DROP_REC ://25
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"�����ӽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"�����ӽ���");
				Display_Fail(TEST_LEFT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_DROP_REC ://26
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"�����ӽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"�����ӽ���");
				Display_Fail(TEST_RIGHT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_DROP_REC ://27
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"ǰ���ӽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"ǰ���ӽ���");
				Display_Fail(TEST_FRONT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_LATE_DROP_REC ://28
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"�����ӽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"�����ӽ���");
				Display_Fail(TEST_LATE_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_BUMP ://29
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"����ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"����ײ����");
				Display_Fail(TEST_LEFT_BUMP,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_BUMP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"����ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"����ײ����");
				Display_Fail(TEST_LEFT_BUMP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_BUMP ://30
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"����ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"����ײ����");
				Display_Fail(TEST_RIGHT_BUMP,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_BUMP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"����ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"����ײ����");
				Display_Fail(TEST_RIGHT_BUMP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_LEAVELAND ://31
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"����ؽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"����ؽ���");
				Display_Fail(TEST_LEFT_LEAVELAND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_LEAVELAND ://32
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"����ؽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"����ؽ���");
				Display_Fail(TEST_RIGHT_LEAVELAND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL_FEEDBACK ://33
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"�����̽���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"�����̽���");
				Display_Fail(TEST_LEFT_WHEEL_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL_FEEDBACK_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"�����̹���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"�����̹���");
				Display_Fail(TEST_LEFT_WHEEL_FEEDBACK_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL_FEEDBACK ://34
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"�����̽���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"�����̽���");
				Display_Fail(TEST_RIGHT_WHEEL_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL_FEEDBACK_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"�����̹���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"�����̹���");
				Display_Fail(TEST_RIGHT_WHEEL_FEEDBACK_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL ://35
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"�����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"�����");
				Display_Fail(TEST_LEFT_WHEEL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL ://36
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"�Ҵ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"�Ҵ���");
				Display_Fail(TEST_RIGHT_WHEEL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_ROLLBURSH_CUR_FEEDBACK ://37
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"��ˢ");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"��ˢ");
				Display_Fail(TEST_ROLLBURSH_CUR_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_VACUUM_FEEDBACK ://38
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"����������");
				Display_Fail(TEST_VACUUM_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_VACUUM_CONTROL ://39
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"�����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"�����������");
				Display_Fail(TEST_VACUUM_CONTROL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_DISCHARGE_CUR_FEEDBACK ://40
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"�����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"�����");
				Display_Fail(TEST_DISCHARGE_CUR_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_POWER_NTC ://41
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"NTC");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"NTC");
				Display_Fail(TEST_POWER_NTC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_OPEN_KEY ://42
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"������");
				Display_Fail(TEST_OPEN_KEY,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_DUST_REC ://43
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"�ҳ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"�ҳ����");
				Display_Fail(TEST_DUST_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_DUST_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"�ҳ�����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"�ҳ�����������");
				Display_Fail(TEST_DUST_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_DUSTCUP_REC ://44
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"���м��");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"���м��");
				Display_Fail(TEST_DUSTCUP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_DUSTCUP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"���д���������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"���д���������");
				Display_Fail(TEST_DUSTCUP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_WATERTANK ://45
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"ˮ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"ˮ����");
				Display_Fail(TEST_WATERTANK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_POSITION_CAMERA ://46
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"��λ����ͷ");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"��λ����ͷ");
				Display_Fail(TEST_POSITION_CAMERA,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_POSITION_CAMERA_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"��λ����ͷ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"��λ����ͷ����");
				Display_Fail(TEST_POSITION_CAMERA_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_DC5V :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"DC5V���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"DC5V���");
				Display_Fail(TEST_DC5V,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_DC5V_I8 :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"DC5V-I8���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"DC5V-I8���");
				Display_Fail(TEST_DC5V_I8,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_PATHPLAN_UART ://47
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"��˴���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"��˴���");
				Display_Fail(TEST_PATHPLAN_UART,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_WIFI ://48
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"WIFI");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"WIFI");
				Display_Fail(TEST_WIFI,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_BATTERY ://49
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"��ص���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"��ص���");
				Display_Fail(TEST_BATTERY,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_CHARGE ://50
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"�����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"�����");
				Display_Fail(TEST_CHARGE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_POWER_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"OVP");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"OVP");
				Display_Fail(TEST_POWER_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			break;
		case 0xfe ://ALL
			if(test_status == 1)
			{
				//Gui_DrawFont_GBK64(296,138,WHITE,GREEN,"PASS");
				LCD_Clear_Area(0,20,479,299,GRAY0);
				Gui_DrawFont_GBK128(116,78,GREEN,GRAY0,mpass);
			}
			else
			{
				
			}
			break;
		default :
			break;
	}
}

/*****************************************************************************
 * @name       :void Display_I9_Test(u8 test_mode,u8 test_cmd,u8 test_status)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :display test
 * @parameters :test_cmd ��ȡ����������
 * @retvalue   :None
******************************************************************************/
void Display_I9_Test(u8 test_mode,u8 test_cmd,u8 test_status)
{
	switch(test_cmd)
	{
		case TEST_START ://01
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"����ͨѶ");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"����ͨѶ");
				Display_Fail(TEST_START,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_START_VERSION ://02
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"�汾��");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"�汾��");
				Display_Fail(TEST_START_VERSION,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_TOF_POWER ://03
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"TOF����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"TOF����");
				Display_Fail(TEST_TOF_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_TOF_COMMUNICATION ://04
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"TOFͨѶ");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"TOFͨѶ");
				Display_Fail(TEST_TOF_COMMUNICATION,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_TOF_RESET ://05
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"TOF��λ");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"TOF��λ");
				Display_Fail(TEST_TOF_RESET,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_SIDE_A_SEND ://06
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"�ر߷���A");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"�ر߷���A");
				Display_Fail(TEST_SIDE_A_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_SIDE_B_SEND ://07
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"�ر߷���B");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"�ر߷���B");
				Display_Fail(TEST_SIDE_B_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_SIDE_REC ://08
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"���ر߽���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"���ر߽���");
				Display_Fail(TEST_LEFT_SIDE_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_SIDE_REC ://09
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"���ر߽���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"���ر߽���");
				Display_Fail(TEST_RIGHT_SIDE_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_GUIDE ://10
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"����������");
				Display_Fail(TEST_LEFT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_GUIDE ://11
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"����������");
				Display_Fail(TEST_RIGHT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_TOP_GUIDE ://12
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"����������");
				Display_Fail(TEST_TOP_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_GUIDE ://13
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"ǰ��������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"ǰ��������");
				Display_Fail(TEST_FRONT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_LATE_GUIDE ://14
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"����������");
				Display_Fail(TEST_LATE_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_GUIDE_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"��������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"��������");
				Display_Fail(TEST_GUIDE_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_AVOIDBUMP_A_SEND ://15
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"����ײA����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"����ײA����");
				Display_Fail(TEST_AVOIDBUMP_A_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_AVOIDBUMP_B_SEND ://16
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"����ײB����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"����ײB����");
				Display_Fail(TEST_AVOIDBUMP_B_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_AVOIDBUMP_REC ://17
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"������ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"������ײ����");
				Display_Fail(TEST_LEFT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_AVOIDBUMP_REC ://18
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"������ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"������ײ����");
				Display_Fail(TEST_RIGHT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_AVOIDBUMP_REC ://19
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"ǰ����ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"ǰ����ײ����");
				Display_Fail(TEST_FRONT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_GYRO ://20
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"������");
				Display_Fail(TEST_GYRO,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_KEY1 ://21
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"����1");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"����1");
				Display_Fail(TEST_KEY1,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_KEY2 ://22
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"����2");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"����2");
				Display_Fail(TEST_KEY2,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_KEY3 ://23
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"����3");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"����3");
				Display_Fail(TEST_KEY3,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_LEFT ://24
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"�����ӷ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"�����ӷ���");
				Display_Fail(TEST_DROP_SEND_LEFT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_RIGHT :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"�����ӷ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"�����ӷ���");
				Display_Fail(TEST_DROP_SEND_RIGHT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_FRONT :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"ǰ���ӷ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"ǰ���ӷ���");
				Display_Fail(TEST_DROP_SEND_FRONT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_LATE :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"�����ӷ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"�����ӷ���");
				Display_Fail(TEST_DROP_SEND_LATE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_DROP_REC ://25
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"�����ӽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"�����ӽ���");
				Display_Fail(TEST_LEFT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_DROP_REC ://26
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"�����ӽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"�����ӽ���");
				Display_Fail(TEST_RIGHT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_DROP_REC ://27
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"ǰ���ӽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"ǰ���ӽ���");
				Display_Fail(TEST_FRONT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_LATE_DROP_REC ://28
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"�����ӽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"�����ӽ���");
				Display_Fail(TEST_LATE_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_BUMP ://29
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"����ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"����ײ����");
				Display_Fail(TEST_LEFT_BUMP,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_BUMP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"����ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"����ײ����");
				Display_Fail(TEST_LEFT_BUMP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_BUMP ://30
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"����ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"����ײ����");
				Display_Fail(TEST_RIGHT_BUMP,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_BUMP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"����ײ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"����ײ����");
				Display_Fail(TEST_RIGHT_BUMP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_LEAVELAND ://31
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"����ؽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"����ؽ���");
				Display_Fail(TEST_LEFT_LEAVELAND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_LEAVELAND ://32
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"����ؽ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"����ؽ���");
				Display_Fail(TEST_RIGHT_LEAVELAND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL_FEEDBACK ://33
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"�����̽���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"�����̽���");
				Display_Fail(TEST_LEFT_WHEEL_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL_FEEDBACK_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"�����̹���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"�����̹���");
				Display_Fail(TEST_LEFT_WHEEL_FEEDBACK_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL_FEEDBACK ://34
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"�����̽���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"�����̽���");
				Display_Fail(TEST_RIGHT_WHEEL_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL_FEEDBACK_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"�����̹���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"�����̹���");
				Display_Fail(TEST_RIGHT_WHEEL_FEEDBACK_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL ://35
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"�����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"�����");
				Display_Fail(TEST_LEFT_WHEEL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL ://36
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"�Ҵ���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"�Ҵ���");
				Display_Fail(TEST_RIGHT_WHEEL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_ROLLBURSH_CUR_FEEDBACK ://37
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"��ˢ");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"��ˢ");
				Display_Fail(TEST_ROLLBURSH_CUR_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_VACUUM_FEEDBACK ://38
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"����������");
				Display_Fail(TEST_VACUUM_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_VACUUM_CONTROL ://39
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"�����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"�����������");
				Display_Fail(TEST_VACUUM_CONTROL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_DISCHARGE_CUR_FEEDBACK ://40
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"�����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"�����");
				Display_Fail(TEST_DISCHARGE_CUR_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_POWER_NTC ://41
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"NTC");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"NTC");
				Display_Fail(TEST_POWER_NTC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_OPEN_KEY ://42
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"������");
				Display_Fail(TEST_OPEN_KEY,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_DUST_REC ://43
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"�ҳ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"�ҳ����");
				Display_Fail(TEST_DUST_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_DUST_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"�ҳ�����������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"�ҳ�����������");
				Display_Fail(TEST_DUST_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_DUSTCUP_REC ://44
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"���м��");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"���м��");
				Display_Fail(TEST_DUSTCUP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_DUSTCUP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"���д���������");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"���д���������");
				Display_Fail(TEST_DUSTCUP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_WATERTANK ://45
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"ˮ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"ˮ����");
				Display_Fail(TEST_WATERTANK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_POSITION_CAMERA ://46
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"��λ����ͷ");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"��λ����ͷ");
				Display_Fail(TEST_POSITION_CAMERA,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_POSITION_CAMERA_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"��λ����ͷ����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"��λ����ͷ����");
				Display_Fail(TEST_POSITION_CAMERA_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_DC5V :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"DC5V���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"DC5V���");
				Display_Fail(TEST_DC5V,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_DC5V_I8 :
			if(test_status == 1)
			{
				
			}
			else
			{
				
			}
			break;
		case TEST_PATHPLAN_UART ://47
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"��˴���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"��˴���");
				Display_Fail(TEST_PATHPLAN_UART,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_WIFI ://48
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"WIFI");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"WIFI");
				Display_Fail(TEST_WIFI,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_BATTERY ://49
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"��ص���");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"��ص���");
				Display_Fail(TEST_BATTERY,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_CHARGE ://50
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"�����");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"�����");
				Display_Fail(TEST_CHARGE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_POWER_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"OVP");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"OVP");
				Display_Fail(TEST_POWER_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			break;
		case 0xfe ://ALL
			if(test_status == 1)
			{
				//Gui_DrawFont_GBK64(296,138,WHITE,GREEN,"PASS");
				LCD_Clear_Area(0,20,479,299,GRAY0);
				Gui_DrawFont_GBK128(116,78,GREEN,GRAY0,mpass);
			}
			else
			{
				
			}
			break;
		default :
			break;
	}
}

/*****************************************************************************
 * @name       :void Test_Display(void)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :display test
 * @parameters :None
 * @retvalue   :None
******************************************************************************/
void Test_Display(void)
{
//	if(mMaininf.mWork.mWorkInitFlag == 1)//��ʼ���ɹ�
	if(1)
	{
// 		if(mMaininf.mWork.mWorkChecking == 0)//δ�ڼ��״̬
// 		{
// 			if(mMaininf.mMode.mScreenPressFlag == 1)            //    ��Ļ����
// 			{
// 				mMaininf.mMode.mScreenPressFlag = 0;
// 				
// 				if((Touch_X >= 305) && (Touch_X <= 423) && (Touch_Y >= 215) && (Touch_Y <= 278))
// 				{
// 					LCD_Clear_Area(305,215,423,278,GRAY0);
// 					
// 					Gui_DrawFont_GBK24(140,130,BLUE,GRAY0,"�����..              ");
// 					
// 					api_SendCMDData(2,1,1);//��ʼ���
// 					mMaininf.mWork.mWorkChecking = 1;
// 				}
// 			}
// 		}
//		else
		if(1)
		{
			if(mMaininf.mUart1.mReceiveFlag == 1)            //    ���յ�����
			{
				mMaininf.mUart1.mReceiveFlag = 0;
				
				if((mMaininf.mUart1.ReceiveBuf[0] == 2) && (mMaininf.mUart1.ReceiveBuf[1] == 1) && 
				   (mMaininf.mUart1.ReceiveBuf[2] == 1))//���յ�����   ����
				{
					mMaininf.mWork.mWorkFileCont = 0;
					
// 					LCD_Clear_Area(0,44,150,295,GRAY0);
// 					LCD_Clear_Area(242,44,390,295,GRAY0);
					LCD_Fill(0,20,lcddev.width,40,YELLOW);
					LCD_Clear_Area(0,40,479,299,GRAY0);
					Gui_DrawLine(240,41,240,299,BLACK);
					Gui_StrCenters(96,22,BLACK,YELLOW,"�����",16,1);//������ʾ
					Gui_StrCenters(336,22,BLACK,YELLOW,"������",16,1);//������ʾ
					
					Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
					api_SendCMDData(2,1,1);//��ʼ���
					vTaskDelay(5);
				}
				else if((mMaininf.mUart1.ReceiveBuf[0] == 2) && (mMaininf.mUart1.ReceiveBuf[1] == 2) && 
				   (mMaininf.mUart1.ReceiveBuf[2] == 1))//���յ�����
				{
					LCD_Fill(195,0,285,20,BLUE);
					LCD_Fill(0,20,lcddev.width,40,YELLOW);
					LCD_Fill(0,40,480,300,GRAY0);
					Gui_DrawLine(240,41,240,299,BLACK);
					Gui_StrCenter(0,2,WHITE,BLUE,"I8���幤װ",16,1);//������ʾ
					Gui_StrCenters(96,22,BLACK,YELLOW,"�����",16,1);//������ʾ
					Gui_StrCenters(336,22,BLACK,YELLOW,"������",16,1);//������ʾ
					api_SendCMDData(2,2,1);       //����
					//vTaskDelay(5);
					mMaininf.mWork.mWorkSelectI8OrI9Flag = 1;
				}
				else if((mMaininf.mUart1.ReceiveBuf[0] == 2) && (mMaininf.mUart1.ReceiveBuf[1] == 3) && 
				   (mMaininf.mUart1.ReceiveBuf[2] == 1))//���յ�����
				{
					LCD_Fill(195,0,285,20,BLUE);
					LCD_Fill(0,20,lcddev.width,40,YELLOW);
					LCD_Fill(0,40,480,300,GRAY0);
					Gui_DrawLine(240,41,240,299,BLACK);
					Gui_StrCenter(0,2,WHITE,BLUE,"I9���幤װ",16,1);//������ʾ
					Gui_StrCenters(96,22,BLACK,YELLOW,"�����",16,1);//������ʾ
					Gui_StrCenters(336,22,BLACK,YELLOW,"������",16,1);//������ʾ
					api_SendCMDData(2,3,1);       //����
					//vTaskDelay(5);
					mMaininf.mWork.mWorkSelectI8OrI9Flag = 0;
				}
				if(mMaininf.mUart1.ReceiveBuf[0] == 1)//���յ�ָ��
				{
					if(mMaininf.mWork.mWorkSelectI8OrI9Flag == 1)//i8
					{
						Display_I8_Test(1,mMaininf.mUart1.ReceiveBuf[1],mMaininf.mUart1.ReceiveBuf[2]);
						
						api_SendCMDData(1,mMaininf.mUart1.ReceiveBuf[1],1);//������Ϣ
						vTaskDelay(5);
						mMaininf.mWork.mWorkChecking = 0;
					}
					else//i9
					{
						Display_I9_Test(1,mMaininf.mUart1.ReceiveBuf[1],mMaininf.mUart1.ReceiveBuf[2]);
						
						api_SendCMDData(1,mMaininf.mUart1.ReceiveBuf[1],1);//������Ϣ
						vTaskDelay(5);
						mMaininf.mWork.mWorkChecking = 0;
					}
				}
			}
			
			//Display_Test(mMaininf.mWork.mWorkMODE,mMaininf.mWork.mWorkCMD,mMaininf.mWork.mWorkSTATUS);
		}
	}
	Gui_DrawPoint(0,0,GRAY0);
	
	
// 	DisplayButtonUp(15,38,113,58); //x1,y1,x2,y2
//  	Gui_DrawFont_GBK16(16,40,YELLOW,GRAY0,"����������");
//  	DisplayButtonDown(15,68,113,88); //x1,y1,x2,y2
// 	Gui_DrawFont_GBK16(16,70,BLUE,GRAY0,"������ʾ����");

// 	DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
// 	Gui_DrawFont_GBK24(16,100,RED,GRAY0,"��ײ�ر�����");
// 	
// 	delay_ms(1200);
}






















