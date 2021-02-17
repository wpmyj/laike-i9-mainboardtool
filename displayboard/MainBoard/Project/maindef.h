/****************************************************************************************************/
/*			@FileName		:	MAINDEF.h																																	  	*/
/*			@Author			:	zhengbaiqiu																																		*/
/*			@Version		:	v1.0																																					*/
/*			@Date				:	2019.11.12  																																	*/
/****************************************************************************************************/

#ifndef	__MAINDEF_H__
#define	__MAINDEF_H__

#include "stm32f10x.h"
#include <stdlib.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"


/*		struct congig		*/



#ifdef __cplusplus
extern "C" {
#endif
	
	
#define m_Ok 1                         //真
#define m_NoOk 0                       //假
	
#define BURN_TIMEOUT 300               //烧录步骤500ms超时	
	
#define mePRINT_QUEUE_SIZE	(5)
#define meBURN_QUEUE_SIZE	(5)
#define mDELAY100msTick		( pdMS_TO_TICKS( ( TickType_t ) 100 ) )	
#define mDELAY200msTick		( pdMS_TO_TICKS( ( TickType_t ) 200 ) )	
#define mDELAY500msTick		( pdMS_TO_TICKS( ( TickType_t ) 500 ) )
	
	
/* Task priorities. */
//#define mainQUEUE_POLL_PRIORITY				( tskIDLE_PRIORITY + 2 )
//#define mainCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
//#define mainSEM_TEST_PRIORITY				( tskIDLE_PRIORITY + 1 )
//#define mainBLOCK_Q_PRIORITY				( tskIDLE_PRIORITY + 2 )
//#define mainCREATOR_TASK_PRIORITY           ( tskIDLE_PRIORITY + 3 )
//#define mainFLASH_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )
//#define mainCOM_TEST_PRIORITY				( tskIDLE_PRIORITY + 1 )
//#define mainINTEGER_TASK_PRIORITY           ( tskIDLE_PRIORITY )
#define mainTIMER_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define mainDISPLAY_TASK_PRIORITY				( tskIDLE_PRIORITY + 1 )
// #define mainCHECKKEY_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
// #define mainCHECKSD_TASK_PRIORITY				( tskIDLE_PRIORITY + 3 )
// #define mainPRINT_TASK_PRIORITY          (tskIDLE_PRIORITY + 2 )
// #define mainBURN_TASK_PRIORITY          (tskIDLE_PRIORITY + 2 )
// #define mainVERSIONCHECK_TASK_PRIORITY				( tskIDLE_PRIORITY + 2 )


/* Task Stack. */
#define mainTIMER_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
#define mainDISPLAY_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
// #define mainCHECKKEY_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
// #define mainCHECKSD_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
// #define mainVERSIONCHECK_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
// #define mainPRINT_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 64 )
// #define mainBURN_TASK_STACK_SIZE			( configMINIMAL_STACK_SIZE + 128 )



/*--------------------------------------------------------------------------

        自定义结构体

---------------------------------------------------------------------------*/	


/*   	 自定义			*/
#define SYSTEMTIMEMAX                86400000               /*   System timing maximum 24 hours  */

/* timeout time define */

#define TIMEOUT_0ms           (0)               /*   0ms超时      */
#define TIMEOUT_5ms           (5)               /*   5ms超时      */
#define TIMEOUT_10ms          (10)              /*   10ms超时     */
#define TIMEOUT_50ms          (50)              /*   50ms超时     */
#define TIMEOUT_100ms         (100)             /*   100ms超时    */
#define TIMEOUT_300ms         (300)             /*   300ms超时    */
#define TIMEOUT_500ms         (500)             /*   500ms超时    */
#define TIMEOUT_1000ms        (1000)            /*   1000ms超时   */
#define TIMEOUT_3500ms        (3500)            /*   3500ms超时   */
#define TIMEOUT_5000ms        (5000)            /*   5000ms超时   */

/*   	 结构体声明			*/

typedef enum {
	ST_0x55 = 0x01,
	ST_0xAA,
	ST_MODE,
	ST_CMD,
	ST_STA,
	ST_BCC
} UART1_RECEIVE_STEP;

// typedef enum
// {
//     TEST_START=0x01,                  //01开始检测
//     TEST_TOP_GUIDE,                   //02上引导接收
//     TEST_FRONT_GUIDE,                 //03前引导接收
//     TEST_RIGHT_GUIDE,                 //04右引导接收
//     TEST_LEFT_GUIDE,                  //05左引导接收
//     TEST_LATE_GUIDE,                  //06后引导接收
//     TEST_DUSTCUP_REC,                 //07尘杯接收
//     TEST_LEFT_LEAVELAND,              //08左离地接收
//     TEST_RIGHT_LEAVELAND,             //09右离地接收
//     TEST_RIGHT_BUMP,                  //10右碰撞接收
//     TEST_LEFT_BUMP,                   //11左碰撞接收
//     TEST_FRONT_DROP_REC,              //12前下视接收
//     TEST_RIGHT_DROP_REC,              //13右下视接收
//     TEST_LEFT_DROP_REC,               //14左下视接收
//     TEST_LATE_DROP_REC,               //15后下视接收
//     TEST_DROP_SEND,                   //16下视发射
//     TEST_RIGHT_SIDE_REC,              //17右沿边接收
//     TEST_LEFT_SIDE_REC,               //18左沿边接收
//     TEST_RIGHT_AVOIDBUMP_REC,         //19右免碰撞接收
//     TEST_FRONT_AVOIDBUMP_REC,         //20前免碰撞接收
//     TEST_LEFT_AVOIDBUMP_REC,          //21左免碰撞接收
//     TEST_DUST_REC,                    //22灰尘接收
//     TEST_VACUUM_FEEDBACK,             //23吸尘电机反馈
//     TEST_VACUUM_CONTROL,              //24吸尘电机控制
//     TEST_LEFT_WHEEL,                  //25左大轮发射
//     TEST_RIGHT_WHEEL,                 //26右大轮发射
//     TEST_LEFT_WHEEL_FEEDBACK,         //27左大轮反馈
//     TEST_RIGHT_WHEEL_FEEDBACK,        //28右大轮反馈
//     TEST_WIFI,                        //29测试wifi
//     TEST_GYRO,                        //30测试陀螺仪
//     TEST_KEY1,                        //31按键1
//     TEST_KEY2,                        //32按键2
//     TEST_KEY3,                        //33按键3
//     TEST_VERSION,                     //34版本号
//     TEST_TOF_POWER,                   //35TOF供电
//     TEST_TOF_COMMUNICATION,           //36TOF通讯
//     TEST_TOF_RESET,                   //37TOF复位
//     TEST_SIDE_A_SEND,                 //38沿边A信号发射
//     TEST_SIDE_B_SEND,                 //39沿边B信号发射
//     TEST_AVOIDBUMP_A_SEND,            //40免碰撞A发射
//     TEST_AVOIDBUMP_B_SEND,            //41免碰撞B发射
//     TEST_PATHPLAN_UART,               //42大核串口
//     TEST_OPEN_KEY,                    //43开机键
//     TEST_WATERTANK,                   //44测试水箱
//     TEST_ROLLBURSH_CUR_FEEDBACK,      //45滚刷电流反馈
//     TEST_DISCHARGE_CUR_FEEDBACK,      //46电池放电电流反馈
//     TEST_POWER_NTC,                   //47检测NTC
//     TEST_CHARGE,                      //48检测充电
//     TEST_POSITION_CAMERA,             //49检测定位摄像头
//     TEST_POSITION_CAMERA_POWER        //50检测定位摄像头供电
// }enum_TEST_CMD;

typedef enum
{
	TEST_START = 0x01,                //01开始测试
	TEST_START_VERSION,               //02读取版本号
	TEST_TOF_POWER,                   //03TOF供电
    TEST_TOF_COMMUNICATION,           //04TOF通讯
    TEST_TOF_RESET,                   //05TOF复位
	TEST_SIDE_A_SEND,                 //06沿边A信号发射
    TEST_SIDE_B_SEND,                 //07沿边B信号发射
	TEST_LEFT_SIDE_REC,               //08左沿边接收
	TEST_RIGHT_SIDE_REC,              //09右沿边接收
	TEST_LEFT_GUIDE,                  //10左引导接收
	TEST_RIGHT_GUIDE,                 //11右引导接收
	TEST_TOP_GUIDE,                   //12上引导接收
	TEST_FRONT_GUIDE,                 //13前引导接收
	TEST_LATE_GUIDE,                  //14后引导接收
	TEST_GUIDE_POWER,
	TEST_AVOIDBUMP_A_SEND,            //15免碰撞A发射
    TEST_AVOIDBUMP_B_SEND,            //16免碰撞B发射
	TEST_LEFT_AVOIDBUMP_REC,          //17左免碰撞接收
	TEST_RIGHT_AVOIDBUMP_REC,         //18右免碰撞接收
	TEST_FRONT_AVOIDBUMP_REC,         //19前免碰撞接收
	TEST_GYRO,                        //20测试陀螺仪
	TEST_KEY1,                        //21按键1
    TEST_KEY2,                        //22按键2
    TEST_KEY3,                        //23按键3
	TEST_DROP_SEND_LEFT,              //24下视发射
	TEST_DROP_SEND_RIGHT,
	TEST_DROP_SEND_FRONT,
	TEST_DROP_SEND_LATE,
	TEST_LEFT_DROP_REC,               //25左下视接收
	TEST_RIGHT_DROP_REC,              //26右下视接收
	TEST_FRONT_DROP_REC,              //27前下视接收
	TEST_LATE_DROP_REC,               //28后下视接收
	TEST_LEFT_BUMP,                   //29左碰撞接收
	TEST_LEFT_BUMP_POWER,
	TEST_RIGHT_BUMP,                  //30右碰撞接收
	TEST_RIGHT_BUMP_POWER,
	TEST_LEFT_LEAVELAND,              //31左离地接收
    TEST_RIGHT_LEAVELAND,             //32右离地接收
	TEST_LEFT_WHEEL_FEEDBACK,         //33左大轮反馈
	TEST_LEFT_WHEEL_FEEDBACK_POWER,
    TEST_RIGHT_WHEEL_FEEDBACK,        //34右大轮反馈
	TEST_RIGHT_WHEEL_FEEDBACK_POWER,                             //右码盘供电
	TEST_LEFT_WHEEL,                  //35左大轮发射
    TEST_RIGHT_WHEEL,                 //36右大轮发射
	TEST_ROLLBURSH_CUR_FEEDBACK,      //37滚刷电流反馈
	TEST_VACUUM_FEEDBACK,             //38吸尘电机反馈
	TEST_VACUUM_CONTROL,              //39吸尘电机控制
	TEST_DISCHARGE_CUR_FEEDBACK,      //40电池放电电流反馈
	TEST_POWER_NTC,                   //41检测NTC
	TEST_OPEN_KEY,                    //42开机键
	TEST_DUST_REC,                    //43灰尘接收
	TEST_DUST_POWER,
	TEST_DUSTCUP_REC,                 //44尘杯接收
	TEST_DUSTCUP_POWER,
	TEST_WATERTANK,                   //45测试水箱
	TEST_POSITION_CAMERA,             //46检测定位摄像头
	TEST_POSITION_CAMERA_POWER,
	TEST_DC5V,
	TEST_DC5V_I8,
	TEST_PATHPLAN_UART,               //47大核串口
	TEST_WIFI,                        //48测试wifi
	TEST_BATTERY,                     //49检测电池电量
    TEST_CHARGE,                      //50检测充电
	TEST_POWER_POWER,                                            //电池供电脚
	

	
	TEST_FILE,                        //51测试FILE
	TEST_OK                           //52测试OK
	
}enum_TEST_CMD;

typedef struct _ST_SYSTEM_MANAGER{
	u32 mSystemTick ;                /*  1ms 模拟滴答计数器   */
	u32 mPowerOnStartTime ;
	
	u32 mReadUartStatusStartTime ;
	u32 mTestStartTime;
}_ST_SYSTEM_MANAGER;

typedef struct _ST_USART_MANAGER{
	u8 TxBuffer[64];
	u8 RxBuffer[64];
	u8 SendBuf[64];
	u8 ReceiveBuf[64];
	
	u16 mSendSize;
	u16 mSendCont;
	
	u8 mReceiveStep : 3;
	u8 mReceiveBCC;
	u16 mReceiveSize;
	u16 mReceiveCont;
	u16 mReceiveTimeOut;
	
	u8 mReceiveFlag : 1;
	
}_ST_USART_MANAGER;

typedef struct _ST_MODE_MANAGER{
	u8 mKeyPressFlag : 1;            //  0 : no press    1 : press  按键触发
	u8 mScreenPressFlag : 1;         //  0 : no press    1 : press  屏幕按下
	
	u8 mModePage;
}_ST_MODE_MANAGER;

typedef struct _ST_WORK_MANAGER{
	u8 mWorkMODE ;           //工作模式
 	u8 mWorkCMD ;            //工作命令字
 	u8 mWorkSTATUS ;         //传感器状态
	
	u8 mWorkInitFlag : 1;    //0:初始化失败   1：初始化成功
	u8 mWorkChecking : 1;    //0:没有检测     1：正在检测中
	u8 mWorkKeyCont ;
	
	u8 mWorkSelectI8OrI9Flag : 2;     //0:i9   1:i8
	
	u8 mWorkFileCont;
}_ST_WORK_MANAGER;


typedef struct _ST_MAINMANAGER{
	/*        文件内定义        */
	_ST_SYSTEM_MANAGER         mSystem;
	_ST_USART_MANAGER          mUart1;
	
	_ST_MODE_MANAGER           mMode;
	_ST_WORK_MANAGER           mWork;

}_ST_MAINMANAGER;
		
extern _ST_MAINMANAGER mMaininf;
	
void prvSetupHardware(void);
void vCreateQueueAndSemphr(void);



	
	
#ifdef _cplusplus
extern }
#endif

#endif /*__MAINDEF_H__*/	

