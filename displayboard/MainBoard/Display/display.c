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
	//绘制固定栏up
	//LCD_Clear(WHITE);
	LCD_Clear(GRAY0);
	LCD_Fill(0,0,lcddev.width,20,BLUE);
// 	LCD_Fill(0,20,lcddev.width,40,YELLOW);
	//绘制固定栏down
	LCD_Fill(0,lcddev.height-20,lcddev.width,lcddev.height,BLUE);
	POINT_COLOR=WHITE;
	//POINT_COLOR=GRAY0;
	Gui_StrCenter(0,2,WHITE,BLUE,str,16,1);//居中显示
// 	Gui_StrCenters(96,22,BLACK,YELLOW,"检测栏",16,1);//居中显示
// 	Gui_StrCenters(336,22,BLACK,YELLOW,"检测栏",16,1);//居中显示
	//Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"http://www.zbq.com",16,1);//居中显示
	Gui_StrCenter(0,lcddev.height-18,WHITE,BLUE,"请按提示操作",16,1);//居中显示
	//绘制测试区域
	//LCD_Fill(0,20,lcddev.width,lcddev.height-20,WHITE);
}

/*****************************************************************************
 * @name       :void Display_Fail(u8 item,u8 position)
 * @date       :2020-09-19 
 * @author     :zhengbaiqiu 
 * @function   :显示报错
 * @parameters :item：显示哪一项错误    position：位置
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
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"主板通讯");
				break;
			case TEST_START_VERSION ://02
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"版本号");
				break;
			case TEST_TOF_POWER ://03
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"TOF供电");
				break;
			case TEST_TOF_COMMUNICATION ://04
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"TOF通讯");
				break;
			case TEST_TOF_RESET ://05
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"TOF复位");
				break;
			case TEST_SIDE_A_SEND ://06
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"沿边发射A");
				break;
			case TEST_SIDE_B_SEND ://07
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"沿边发射B");
				break;
			case TEST_LEFT_SIDE_REC ://08
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左沿边接收");
				break;
			case TEST_RIGHT_SIDE_REC ://09
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右沿边接收");
				break;
			case TEST_LEFT_GUIDE ://10
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左引导接收");
				break;
			case TEST_RIGHT_GUIDE ://11
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右引导接收");
				break;
			case TEST_TOP_GUIDE ://12
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"上引导接收");
				break;
			case TEST_FRONT_GUIDE ://13
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"前引导接收");
				break;
			case TEST_LATE_GUIDE ://14
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"后引导接收");
				break;
			case TEST_GUIDE_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"引导供电");
				break;
			case TEST_AVOIDBUMP_A_SEND ://15
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"免碰撞A发射");
				break;
			case TEST_AVOIDBUMP_B_SEND ://16
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"免碰撞B发射");
				break;
			case TEST_LEFT_AVOIDBUMP_REC ://17
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左免碰撞接收");
				break;
			case TEST_RIGHT_AVOIDBUMP_REC ://18
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右免碰撞接收");
				break;
			case TEST_FRONT_AVOIDBUMP_REC ://19
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"前免碰撞接收");
				break;
			case TEST_GYRO ://20
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"陀螺仪");
				break;
			case TEST_KEY1 ://21
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"按键1");
				break;
			case TEST_KEY2 ://22
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"按键2");
				break;
			case TEST_KEY3 ://23
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"按键3");
				break;
			case TEST_DROP_SEND_LEFT ://24
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左下视发射");
				break;
			case TEST_DROP_SEND_RIGHT :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右下视发射");
				break;
			case TEST_DROP_SEND_FRONT :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"前下视发射");
				break;
			case TEST_DROP_SEND_LATE :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"后下视发射");
				break;
			case TEST_LEFT_DROP_REC ://25
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左下视接收");
				break;
			case TEST_RIGHT_DROP_REC ://26
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右下视接收");
				break;
			case TEST_FRONT_DROP_REC ://27
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"前下视接收");
				break;
			case TEST_LATE_DROP_REC ://28
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"后下视接收");
				break;
			case TEST_LEFT_BUMP ://29
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左碰撞接收");
				break;
			case TEST_LEFT_BUMP_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左碰撞供电");
				break;
			case TEST_RIGHT_BUMP ://30
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右碰撞接收");
				break;
			case TEST_RIGHT_BUMP_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右碰撞供电");
				break;
			case TEST_LEFT_LEAVELAND ://31
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左离地接收");
				break;
			case TEST_RIGHT_LEAVELAND ://32
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右离地接收");
				break;
			case TEST_LEFT_WHEEL_FEEDBACK ://33
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左码盘接收");
				break;
			case TEST_LEFT_WHEEL_FEEDBACK_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左码盘供电");
				break;
			case TEST_RIGHT_WHEEL_FEEDBACK ://34
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右码盘接收");
				break;
			case TEST_RIGHT_WHEEL_FEEDBACK_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右码盘供电");
				break;
			case TEST_LEFT_WHEEL ://35
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"左大轮");
				break;
			case TEST_RIGHT_WHEEL ://36
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"右大轮");
				break;
			case TEST_ROLLBURSH_CUR_FEEDBACK ://37
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"滚刷");
				break;
			case TEST_VACUUM_FEEDBACK ://38
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"吸尘电机检测");
				break;
			case TEST_VACUUM_CONTROL ://39
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"吸尘电机控制");
				break;
			case TEST_DISCHARGE_CUR_FEEDBACK ://40
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"充电检测");
				break;
			case TEST_POWER_NTC ://41
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"NTC");
				break;
			case TEST_OPEN_KEY ://42
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"开机键");
				break;
			case TEST_DUST_REC ://43
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"灰尘检测");
				break;
			case TEST_DUST_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"灰尘传感器供电");
				break;
			case TEST_DUSTCUP_REC ://44
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"尘盒检测");
				break;
			case TEST_DUSTCUP_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"尘盒传感器供电");
				break;
			case TEST_WATERTANK ://45
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"水箱检测");
				break;
			case TEST_POSITION_CAMERA ://46
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"定位摄像头");
				break;
			case TEST_POSITION_CAMERA_POWER :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"定位摄像头供电");
				break;
			case TEST_DC5V :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"DC5V检测");
				break;
			case TEST_DC5V_I8 :
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"DC5V-I8检测");
				break;
			case TEST_PATHPLAN_UART ://47
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"大核串口");
				break;
			case TEST_WIFI ://48
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"WIFI");
				break;
			case TEST_BATTERY ://49
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"电池电量");
				break;
			case TEST_CHARGE ://50
				Gui_DrawFont_GBK24(242,mpos,RED,GRAY0,"充电检测");
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
 * @parameters :test_cmd 读取到的命令码
 * @retvalue   :None
******************************************************************************/
void Display_I8_Test(u8 test_mode,u8 test_cmd,u8 test_status)
{
	switch(test_cmd)
	{
		case TEST_START ://01
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"主板通讯");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"主板通讯");
				Display_Fail(TEST_START,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_START_VERSION ://02
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"版本号");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"版本号");
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
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"沿边发射A");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"沿边发射A");
				Display_Fail(TEST_SIDE_A_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_SIDE_B_SEND ://07
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"沿边发射B");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"沿边发射B");
				Display_Fail(TEST_SIDE_B_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_SIDE_REC ://08
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"左沿边接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"左沿边接收");
				Display_Fail(TEST_LEFT_SIDE_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_SIDE_REC ://09
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"右沿边接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"右沿边接收");
				Display_Fail(TEST_RIGHT_SIDE_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_GUIDE ://10
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"左引导接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"左引导接收");
				Display_Fail(TEST_LEFT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_GUIDE ://11
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"右引导接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"右引导接收");
				Display_Fail(TEST_RIGHT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_TOP_GUIDE ://12
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"上引导接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"上引导接收");
				Display_Fail(TEST_TOP_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_GUIDE ://13
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"前引导接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"前引导接收");
				Display_Fail(TEST_FRONT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_LATE_GUIDE ://14
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"后引导接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"后引导接收");
				Display_Fail(TEST_LATE_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_GUIDE_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"引导供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"引导供电");
				Display_Fail(TEST_GUIDE_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_AVOIDBUMP_A_SEND ://15
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"免碰撞A发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"免碰撞A发射");
				Display_Fail(TEST_AVOIDBUMP_A_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_AVOIDBUMP_B_SEND ://16
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"免碰撞B发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"免碰撞B发射");
				Display_Fail(TEST_AVOIDBUMP_B_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_AVOIDBUMP_REC ://17
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"左免碰撞接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"左免碰撞接收");
				Display_Fail(TEST_LEFT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_AVOIDBUMP_REC ://18
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"右免碰撞接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"右免碰撞接收");
				Display_Fail(TEST_RIGHT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_AVOIDBUMP_REC ://19
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"前免碰撞接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"前免碰撞接收");
				Display_Fail(TEST_FRONT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_GYRO ://20
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"陀螺仪");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"陀螺仪");
				Display_Fail(TEST_GYRO,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_KEY1 ://21
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"按键1");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"按键1");
				Display_Fail(TEST_KEY1,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_KEY2 ://22
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"按键2");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"按键2");
				Display_Fail(TEST_KEY2,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_KEY3 ://23
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"按键3");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"按键3");
				Display_Fail(TEST_KEY3,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_LEFT ://24
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"左下视发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"左下视发射");
				Display_Fail(TEST_DROP_SEND_LEFT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_RIGHT :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"右下视发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"右下视发射");
				Display_Fail(TEST_DROP_SEND_RIGHT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_FRONT :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"前下视发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"前下视发射");
				Display_Fail(TEST_DROP_SEND_FRONT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_LATE :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"后下视发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"后下视发射");
				Display_Fail(TEST_DROP_SEND_LATE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_DROP_REC ://25
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"左下视接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"左下视接收");
				Display_Fail(TEST_LEFT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_DROP_REC ://26
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"右下视接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"右下视接收");
				Display_Fail(TEST_RIGHT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_DROP_REC ://27
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"前下视接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"前下视接收");
				Display_Fail(TEST_FRONT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_LATE_DROP_REC ://28
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"后下视接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"后下视接收");
				Display_Fail(TEST_LATE_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_BUMP ://29
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"左碰撞接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"左碰撞接收");
				Display_Fail(TEST_LEFT_BUMP,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_BUMP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"左碰撞供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"左碰撞供电");
				Display_Fail(TEST_LEFT_BUMP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_BUMP ://30
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"右碰撞接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"右碰撞接收");
				Display_Fail(TEST_RIGHT_BUMP,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_BUMP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"右碰撞供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"右碰撞供电");
				Display_Fail(TEST_RIGHT_BUMP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_LEAVELAND ://31
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"左离地接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"左离地接收");
				Display_Fail(TEST_LEFT_LEAVELAND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_LEAVELAND ://32
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"右离地接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"右离地接收");
				Display_Fail(TEST_RIGHT_LEAVELAND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL_FEEDBACK ://33
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"左码盘接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"左码盘接收");
				Display_Fail(TEST_LEFT_WHEEL_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL_FEEDBACK_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"左码盘供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"左码盘供电");
				Display_Fail(TEST_LEFT_WHEEL_FEEDBACK_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL_FEEDBACK ://34
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"右码盘接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"右码盘接收");
				Display_Fail(TEST_RIGHT_WHEEL_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL_FEEDBACK_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"右码盘供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"右码盘供电");
				Display_Fail(TEST_RIGHT_WHEEL_FEEDBACK_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL ://35
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"左大轮");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"左大轮");
				Display_Fail(TEST_LEFT_WHEEL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL ://36
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"右大轮");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"右大轮");
				Display_Fail(TEST_RIGHT_WHEEL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_ROLLBURSH_CUR_FEEDBACK ://37
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"滚刷");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"滚刷");
				Display_Fail(TEST_ROLLBURSH_CUR_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_VACUUM_FEEDBACK ://38
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"吸尘电机检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"吸尘电机检测");
				Display_Fail(TEST_VACUUM_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_VACUUM_CONTROL ://39
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"吸尘电机控制");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"吸尘电机控制");
				Display_Fail(TEST_VACUUM_CONTROL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_DISCHARGE_CUR_FEEDBACK ://40
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"充电检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"充电检测");
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
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"开机键");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"开机键");
				Display_Fail(TEST_OPEN_KEY,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_DUST_REC ://43
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"灰尘检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"灰尘检测");
				Display_Fail(TEST_DUST_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_DUST_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"灰尘传感器供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"灰尘传感器供电");
				Display_Fail(TEST_DUST_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_DUSTCUP_REC ://44
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"尘盒检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"尘盒检测");
				Display_Fail(TEST_DUSTCUP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_DUSTCUP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"尘盒传感器供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"尘盒传感器供电");
				Display_Fail(TEST_DUSTCUP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_WATERTANK ://45
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"水箱检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"水箱检测");
				Display_Fail(TEST_WATERTANK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_POSITION_CAMERA ://46
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"定位摄像头");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"定位摄像头");
				Display_Fail(TEST_POSITION_CAMERA,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_POSITION_CAMERA_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"定位摄像头供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"定位摄像头供电");
				Display_Fail(TEST_POSITION_CAMERA_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_DC5V :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"DC5V检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"DC5V检测");
				Display_Fail(TEST_DC5V,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_DC5V_I8 :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"DC5V-I8检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"DC5V-I8检测");
				Display_Fail(TEST_DC5V_I8,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_PATHPLAN_UART ://47
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"大核串口");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"大核串口");
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
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"电池电量");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"电池电量");
				Display_Fail(TEST_BATTERY,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_CHARGE ://50
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"充电检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"充电检测");
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
 * @parameters :test_cmd 读取到的命令码
 * @retvalue   :None
******************************************************************************/
void Display_I9_Test(u8 test_mode,u8 test_cmd,u8 test_status)
{
	switch(test_cmd)
	{
		case TEST_START ://01
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"主板通讯");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"主板通讯");
				Display_Fail(TEST_START,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_START_VERSION ://02
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"版本号");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"版本号");
				Display_Fail(TEST_START_VERSION,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_TOF_POWER ://03
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"TOF供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"TOF供电");
				Display_Fail(TEST_TOF_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_TOF_COMMUNICATION ://04
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"TOF通讯");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"TOF通讯");
				Display_Fail(TEST_TOF_COMMUNICATION,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_TOF_RESET ://05
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"TOF复位");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"TOF复位");
				Display_Fail(TEST_TOF_RESET,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_SIDE_A_SEND ://06
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"沿边发射A");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"沿边发射A");
				Display_Fail(TEST_SIDE_A_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_SIDE_B_SEND ://07
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"沿边发射B");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"沿边发射B");
				Display_Fail(TEST_SIDE_B_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_SIDE_REC ://08
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"左沿边接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"左沿边接收");
				Display_Fail(TEST_LEFT_SIDE_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_SIDE_REC ://09
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"右沿边接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"右沿边接收");
				Display_Fail(TEST_RIGHT_SIDE_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_GUIDE ://10
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"左引导接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"左引导接收");
				Display_Fail(TEST_LEFT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_GUIDE ://11
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"右引导接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"右引导接收");
				Display_Fail(TEST_RIGHT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_TOP_GUIDE ://12
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"上引导接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"上引导接收");
				Display_Fail(TEST_TOP_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_GUIDE ://13
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"前引导接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"前引导接收");
				Display_Fail(TEST_FRONT_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_LATE_GUIDE ://14
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"后引导接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"后引导接收");
				Display_Fail(TEST_LATE_GUIDE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_GUIDE_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"引导供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"引导供电");
				Display_Fail(TEST_GUIDE_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_AVOIDBUMP_A_SEND ://15
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"免碰撞A发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"免碰撞A发射");
				Display_Fail(TEST_AVOIDBUMP_A_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_AVOIDBUMP_B_SEND ://16
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"免碰撞B发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"免碰撞B发射");
				Display_Fail(TEST_AVOIDBUMP_B_SEND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_AVOIDBUMP_REC ://17
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"左免碰撞接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"左免碰撞接收");
				Display_Fail(TEST_LEFT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_AVOIDBUMP_REC ://18
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"右免碰撞接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"右免碰撞接收");
				Display_Fail(TEST_RIGHT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_AVOIDBUMP_REC ://19
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"前免碰撞接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"前免碰撞接收");
				Display_Fail(TEST_FRONT_AVOIDBUMP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_GYRO ://20
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"陀螺仪");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"陀螺仪");
				Display_Fail(TEST_GYRO,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_KEY1 ://21
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"按键1");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"按键1");
				Display_Fail(TEST_KEY1,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_KEY2 ://22
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"按键2");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"按键2");
				Display_Fail(TEST_KEY2,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_KEY3 ://23
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"按键3");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"按键3");
				Display_Fail(TEST_KEY3,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_LEFT ://24
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"左下视发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"左下视发射");
				Display_Fail(TEST_DROP_SEND_LEFT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_RIGHT :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"右下视发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"右下视发射");
				Display_Fail(TEST_DROP_SEND_RIGHT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_FRONT :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"前下视发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"前下视发射");
				Display_Fail(TEST_DROP_SEND_FRONT,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_DROP_SEND_LATE :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"后下视发射");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"后下视发射");
				Display_Fail(TEST_DROP_SEND_LATE,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_DROP_REC ://25
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"左下视接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"左下视接收");
				Display_Fail(TEST_LEFT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_DROP_REC ://26
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"右下视接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"右下视接收");
				Display_Fail(TEST_RIGHT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_FRONT_DROP_REC ://27
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"前下视接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"前下视接收");
				Display_Fail(TEST_FRONT_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_LATE_DROP_REC ://28
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"后下视接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"后下视接收");
				Display_Fail(TEST_LATE_DROP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_BUMP ://29
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"左碰撞接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"左碰撞接收");
				Display_Fail(TEST_LEFT_BUMP,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_BUMP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"左碰撞供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"左碰撞供电");
				Display_Fail(TEST_LEFT_BUMP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_BUMP ://30
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"右碰撞接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"右碰撞接收");
				Display_Fail(TEST_RIGHT_BUMP,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_BUMP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"右碰撞供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"右碰撞供电");
				Display_Fail(TEST_RIGHT_BUMP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_LEAVELAND ://31
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"左离地接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"左离地接收");
				Display_Fail(TEST_LEFT_LEAVELAND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_LEAVELAND ://32
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"右离地接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"右离地接收");
				Display_Fail(TEST_RIGHT_LEAVELAND,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL_FEEDBACK ://33
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"左码盘接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"左码盘接收");
				Display_Fail(TEST_LEFT_WHEEL_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL_FEEDBACK_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"左码盘供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"左码盘供电");
				Display_Fail(TEST_LEFT_WHEEL_FEEDBACK_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL_FEEDBACK ://34
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"右码盘接收");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"右码盘接收");
				Display_Fail(TEST_RIGHT_WHEEL_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL_FEEDBACK_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"右码盘供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"右码盘供电");
				Display_Fail(TEST_RIGHT_WHEEL_FEEDBACK_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_LEFT_WHEEL ://35
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"左大轮");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"左大轮");
				Display_Fail(TEST_LEFT_WHEEL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_RIGHT_WHEEL ://36
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"右大轮");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"右大轮");
				Display_Fail(TEST_RIGHT_WHEEL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_ROLLBURSH_CUR_FEEDBACK ://37
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"滚刷");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"滚刷");
				Display_Fail(TEST_ROLLBURSH_CUR_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_VACUUM_FEEDBACK ://38
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"吸尘电机检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"吸尘电机检测");
				Display_Fail(TEST_VACUUM_FEEDBACK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_VACUUM_CONTROL ://39
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"吸尘电机控制");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"吸尘电机控制");
				Display_Fail(TEST_VACUUM_CONTROL,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_DISCHARGE_CUR_FEEDBACK ://40
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"充电检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"充电检测");
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
				Gui_DrawFont_GBK24(0,266,BLACK,GRAY0,"开机键");
			}
			else
			{
				Gui_DrawFont_GBK24(0,266,RED,GRAY0,"开机键");
				Display_Fail(TEST_OPEN_KEY,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			LCD_Fill(0,41,235,295,GRAY0);
			Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
			break;
		case TEST_DUST_REC ://43
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"灰尘检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"灰尘检测");
				Display_Fail(TEST_DUST_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_DUST_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"灰尘传感器供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"灰尘传感器供电");
				Display_Fail(TEST_DUST_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"...");
			break;
		case TEST_DUSTCUP_REC ://44
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,98,BLACK,GRAY0,"尘盒检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,98,RED,GRAY0,"尘盒检测");
				Display_Fail(TEST_DUSTCUP_REC,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"...");
			break;
		case TEST_DUSTCUP_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,122,BLACK,GRAY0,"尘盒传感器供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,122,RED,GRAY0,"尘盒传感器供电");
				Display_Fail(TEST_DUSTCUP_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"...");
			break;
		case TEST_WATERTANK ://45
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,146,BLACK,GRAY0,"水箱检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,146,RED,GRAY0,"水箱检测");
				Display_Fail(TEST_WATERTANK,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"...");
			break;
		case TEST_POSITION_CAMERA ://46
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,170,BLACK,GRAY0,"定位摄像头");
			}
			else
			{
				Gui_DrawFont_GBK24(0,170,RED,GRAY0,"定位摄像头");
				Display_Fail(TEST_POSITION_CAMERA,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"...");
			break;
		case TEST_POSITION_CAMERA_POWER :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,194,BLACK,GRAY0,"定位摄像头供电");
			}
			else
			{
				Gui_DrawFont_GBK24(0,194,RED,GRAY0,"定位摄像头供电");
				Display_Fail(TEST_POSITION_CAMERA_POWER,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"...");
			break;
		case TEST_DC5V :
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,218,BLACK,GRAY0,"DC5V检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,218,RED,GRAY0,"DC5V检测");
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
				Gui_DrawFont_GBK24(0,242,BLACK,GRAY0,"大核串口");
			}
			else
			{
				Gui_DrawFont_GBK24(0,242,RED,GRAY0,"大核串口");
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
				Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"电池电量");
			}
			else
			{
				Gui_DrawFont_GBK24(0,50,RED,GRAY0,"电池电量");
				Display_Fail(TEST_BATTERY,mMaininf.mWork.mWorkFileCont);
				mMaininf.mWork.mWorkFileCont ++;
			}
			Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"...");
			break;
		case TEST_CHARGE ://50
			if(test_status == 1)
			{
				Gui_DrawFont_GBK24(0,74,BLACK,GRAY0,"充电检测");
			}
			else
			{
				Gui_DrawFont_GBK24(0,74,RED,GRAY0,"充电检测");
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
//	if(mMaininf.mWork.mWorkInitFlag == 1)//初始化成功
	if(1)
	{
// 		if(mMaininf.mWork.mWorkChecking == 0)//未在检测状态
// 		{
// 			if(mMaininf.mMode.mScreenPressFlag == 1)            //    屏幕触发
// 			{
// 				mMaininf.mMode.mScreenPressFlag = 0;
// 				
// 				if((Touch_X >= 305) && (Touch_X <= 423) && (Touch_Y >= 215) && (Touch_Y <= 278))
// 				{
// 					LCD_Clear_Area(305,215,423,278,GRAY0);
// 					
// 					Gui_DrawFont_GBK24(140,130,BLUE,GRAY0,"检测中..              ");
// 					
// 					api_SendCMDData(2,1,1);//开始检测
// 					mMaininf.mWork.mWorkChecking = 1;
// 				}
// 			}
// 		}
//		else
		if(1)
		{
			if(mMaininf.mUart1.mReceiveFlag == 1)            //    接收到反馈
			{
				mMaininf.mUart1.mReceiveFlag = 0;
				
				if((mMaininf.mUart1.ReceiveBuf[0] == 2) && (mMaininf.mUart1.ReceiveBuf[1] == 1) && 
				   (mMaininf.mUart1.ReceiveBuf[2] == 1))//接收到反馈   按键
				{
					mMaininf.mWork.mWorkFileCont = 0;
					
// 					LCD_Clear_Area(0,44,150,295,GRAY0);
// 					LCD_Clear_Area(242,44,390,295,GRAY0);
					LCD_Fill(0,20,lcddev.width,40,YELLOW);
					LCD_Clear_Area(0,40,479,299,GRAY0);
					Gui_DrawLine(240,41,240,299,BLACK);
					Gui_StrCenters(96,22,BLACK,YELLOW,"检测栏",16,1);//居中显示
					Gui_StrCenters(336,22,BLACK,YELLOW,"报错栏",16,1);//居中显示
					
					Gui_DrawFont_GBK24(0,50,BLACK,GRAY0,"...");
					api_SendCMDData(2,1,1);//开始检测
					vTaskDelay(5);
				}
				else if((mMaininf.mUart1.ReceiveBuf[0] == 2) && (mMaininf.mUart1.ReceiveBuf[1] == 2) && 
				   (mMaininf.mUart1.ReceiveBuf[2] == 1))//接收到反馈
				{
					LCD_Fill(195,0,285,20,BLUE);
					LCD_Fill(0,20,lcddev.width,40,YELLOW);
					LCD_Fill(0,40,480,300,GRAY0);
					Gui_DrawLine(240,41,240,299,BLACK);
					Gui_StrCenter(0,2,WHITE,BLUE,"I8主板工装",16,1);//居中显示
					Gui_StrCenters(96,22,BLACK,YELLOW,"检测栏",16,1);//居中显示
					Gui_StrCenters(336,22,BLACK,YELLOW,"报错栏",16,1);//居中显示
					api_SendCMDData(2,2,1);       //返回
					//vTaskDelay(5);
					mMaininf.mWork.mWorkSelectI8OrI9Flag = 1;
				}
				else if((mMaininf.mUart1.ReceiveBuf[0] == 2) && (mMaininf.mUart1.ReceiveBuf[1] == 3) && 
				   (mMaininf.mUart1.ReceiveBuf[2] == 1))//接收到反馈
				{
					LCD_Fill(195,0,285,20,BLUE);
					LCD_Fill(0,20,lcddev.width,40,YELLOW);
					LCD_Fill(0,40,480,300,GRAY0);
					Gui_DrawLine(240,41,240,299,BLACK);
					Gui_StrCenter(0,2,WHITE,BLUE,"I9主板工装",16,1);//居中显示
					Gui_StrCenters(96,22,BLACK,YELLOW,"检测栏",16,1);//居中显示
					Gui_StrCenters(336,22,BLACK,YELLOW,"报错栏",16,1);//居中显示
					api_SendCMDData(2,3,1);       //返回
					//vTaskDelay(5);
					mMaininf.mWork.mWorkSelectI8OrI9Flag = 0;
				}
				if(mMaininf.mUart1.ReceiveBuf[0] == 1)//接收到指令
				{
					if(mMaininf.mWork.mWorkSelectI8OrI9Flag == 1)//i8
					{
						Display_I8_Test(1,mMaininf.mUart1.ReceiveBuf[1],mMaininf.mUart1.ReceiveBuf[2]);
						
						api_SendCMDData(1,mMaininf.mUart1.ReceiveBuf[1],1);//返回信息
						vTaskDelay(5);
						mMaininf.mWork.mWorkChecking = 0;
					}
					else//i9
					{
						Display_I9_Test(1,mMaininf.mUart1.ReceiveBuf[1],mMaininf.mUart1.ReceiveBuf[2]);
						
						api_SendCMDData(1,mMaininf.mUart1.ReceiveBuf[1],1);//返回信息
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
//  	Gui_DrawFont_GBK16(16,40,YELLOW,GRAY0,"啊啊填充测试");
//  	DisplayButtonDown(15,68,113,88); //x1,y1,x2,y2
// 	Gui_DrawFont_GBK16(16,70,BLUE,GRAY0,"文字显示测试");

// 	DisplayButtonUp(15,98,113,118); //x1,y1,x2,y2
// 	Gui_DrawFont_GBK24(16,100,RED,GRAY0,"防撞沿边下视");
// 	
// 	delay_ms(1200);
}






















