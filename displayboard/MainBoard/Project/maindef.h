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
	
	
#define m_Ok 1                         //��
#define m_NoOk 0                       //��
	
#define BURN_TIMEOUT 300               //��¼����500ms��ʱ	
	
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

        �Զ���ṹ��

---------------------------------------------------------------------------*/	


/*   	 �Զ���			*/
#define SYSTEMTIMEMAX                86400000               /*   System timing maximum 24 hours  */

/* timeout time define */

#define TIMEOUT_0ms           (0)               /*   0ms��ʱ      */
#define TIMEOUT_5ms           (5)               /*   5ms��ʱ      */
#define TIMEOUT_10ms          (10)              /*   10ms��ʱ     */
#define TIMEOUT_50ms          (50)              /*   50ms��ʱ     */
#define TIMEOUT_100ms         (100)             /*   100ms��ʱ    */
#define TIMEOUT_300ms         (300)             /*   300ms��ʱ    */
#define TIMEOUT_500ms         (500)             /*   500ms��ʱ    */
#define TIMEOUT_1000ms        (1000)            /*   1000ms��ʱ   */
#define TIMEOUT_3500ms        (3500)            /*   3500ms��ʱ   */
#define TIMEOUT_5000ms        (5000)            /*   5000ms��ʱ   */

/*   	 �ṹ������			*/

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
//     TEST_START=0x01,                  //01��ʼ���
//     TEST_TOP_GUIDE,                   //02����������
//     TEST_FRONT_GUIDE,                 //03ǰ��������
//     TEST_RIGHT_GUIDE,                 //04����������
//     TEST_LEFT_GUIDE,                  //05����������
//     TEST_LATE_GUIDE,                  //06����������
//     TEST_DUSTCUP_REC,                 //07��������
//     TEST_LEFT_LEAVELAND,              //08����ؽ���
//     TEST_RIGHT_LEAVELAND,             //09����ؽ���
//     TEST_RIGHT_BUMP,                  //10����ײ����
//     TEST_LEFT_BUMP,                   //11����ײ����
//     TEST_FRONT_DROP_REC,              //12ǰ���ӽ���
//     TEST_RIGHT_DROP_REC,              //13�����ӽ���
//     TEST_LEFT_DROP_REC,               //14�����ӽ���
//     TEST_LATE_DROP_REC,               //15�����ӽ���
//     TEST_DROP_SEND,                   //16���ӷ���
//     TEST_RIGHT_SIDE_REC,              //17���ر߽���
//     TEST_LEFT_SIDE_REC,               //18���ر߽���
//     TEST_RIGHT_AVOIDBUMP_REC,         //19������ײ����
//     TEST_FRONT_AVOIDBUMP_REC,         //20ǰ����ײ����
//     TEST_LEFT_AVOIDBUMP_REC,          //21������ײ����
//     TEST_DUST_REC,                    //22�ҳ�����
//     TEST_VACUUM_FEEDBACK,             //23�����������
//     TEST_VACUUM_CONTROL,              //24�����������
//     TEST_LEFT_WHEEL,                  //25����ַ���
//     TEST_RIGHT_WHEEL,                 //26�Ҵ��ַ���
//     TEST_LEFT_WHEEL_FEEDBACK,         //27����ַ���
//     TEST_RIGHT_WHEEL_FEEDBACK,        //28�Ҵ��ַ���
//     TEST_WIFI,                        //29����wifi
//     TEST_GYRO,                        //30����������
//     TEST_KEY1,                        //31����1
//     TEST_KEY2,                        //32����2
//     TEST_KEY3,                        //33����3
//     TEST_VERSION,                     //34�汾��
//     TEST_TOF_POWER,                   //35TOF����
//     TEST_TOF_COMMUNICATION,           //36TOFͨѶ
//     TEST_TOF_RESET,                   //37TOF��λ
//     TEST_SIDE_A_SEND,                 //38�ر�A�źŷ���
//     TEST_SIDE_B_SEND,                 //39�ر�B�źŷ���
//     TEST_AVOIDBUMP_A_SEND,            //40����ײA����
//     TEST_AVOIDBUMP_B_SEND,            //41����ײB����
//     TEST_PATHPLAN_UART,               //42��˴���
//     TEST_OPEN_KEY,                    //43������
//     TEST_WATERTANK,                   //44����ˮ��
//     TEST_ROLLBURSH_CUR_FEEDBACK,      //45��ˢ��������
//     TEST_DISCHARGE_CUR_FEEDBACK,      //46��طŵ��������
//     TEST_POWER_NTC,                   //47���NTC
//     TEST_CHARGE,                      //48�����
//     TEST_POSITION_CAMERA,             //49��ⶨλ����ͷ
//     TEST_POSITION_CAMERA_POWER        //50��ⶨλ����ͷ����
// }enum_TEST_CMD;

typedef enum
{
	TEST_START = 0x01,                //01��ʼ����
	TEST_START_VERSION,               //02��ȡ�汾��
	TEST_TOF_POWER,                   //03TOF����
    TEST_TOF_COMMUNICATION,           //04TOFͨѶ
    TEST_TOF_RESET,                   //05TOF��λ
	TEST_SIDE_A_SEND,                 //06�ر�A�źŷ���
    TEST_SIDE_B_SEND,                 //07�ر�B�źŷ���
	TEST_LEFT_SIDE_REC,               //08���ر߽���
	TEST_RIGHT_SIDE_REC,              //09���ر߽���
	TEST_LEFT_GUIDE,                  //10����������
	TEST_RIGHT_GUIDE,                 //11����������
	TEST_TOP_GUIDE,                   //12����������
	TEST_FRONT_GUIDE,                 //13ǰ��������
	TEST_LATE_GUIDE,                  //14����������
	TEST_GUIDE_POWER,
	TEST_AVOIDBUMP_A_SEND,            //15����ײA����
    TEST_AVOIDBUMP_B_SEND,            //16����ײB����
	TEST_LEFT_AVOIDBUMP_REC,          //17������ײ����
	TEST_RIGHT_AVOIDBUMP_REC,         //18������ײ����
	TEST_FRONT_AVOIDBUMP_REC,         //19ǰ����ײ����
	TEST_GYRO,                        //20����������
	TEST_KEY1,                        //21����1
    TEST_KEY2,                        //22����2
    TEST_KEY3,                        //23����3
	TEST_DROP_SEND_LEFT,              //24���ӷ���
	TEST_DROP_SEND_RIGHT,
	TEST_DROP_SEND_FRONT,
	TEST_DROP_SEND_LATE,
	TEST_LEFT_DROP_REC,               //25�����ӽ���
	TEST_RIGHT_DROP_REC,              //26�����ӽ���
	TEST_FRONT_DROP_REC,              //27ǰ���ӽ���
	TEST_LATE_DROP_REC,               //28�����ӽ���
	TEST_LEFT_BUMP,                   //29����ײ����
	TEST_LEFT_BUMP_POWER,
	TEST_RIGHT_BUMP,                  //30����ײ����
	TEST_RIGHT_BUMP_POWER,
	TEST_LEFT_LEAVELAND,              //31����ؽ���
    TEST_RIGHT_LEAVELAND,             //32����ؽ���
	TEST_LEFT_WHEEL_FEEDBACK,         //33����ַ���
	TEST_LEFT_WHEEL_FEEDBACK_POWER,
    TEST_RIGHT_WHEEL_FEEDBACK,        //34�Ҵ��ַ���
	TEST_RIGHT_WHEEL_FEEDBACK_POWER,                             //�����̹���
	TEST_LEFT_WHEEL,                  //35����ַ���
    TEST_RIGHT_WHEEL,                 //36�Ҵ��ַ���
	TEST_ROLLBURSH_CUR_FEEDBACK,      //37��ˢ��������
	TEST_VACUUM_FEEDBACK,             //38�����������
	TEST_VACUUM_CONTROL,              //39�����������
	TEST_DISCHARGE_CUR_FEEDBACK,      //40��طŵ��������
	TEST_POWER_NTC,                   //41���NTC
	TEST_OPEN_KEY,                    //42������
	TEST_DUST_REC,                    //43�ҳ�����
	TEST_DUST_POWER,
	TEST_DUSTCUP_REC,                 //44��������
	TEST_DUSTCUP_POWER,
	TEST_WATERTANK,                   //45����ˮ��
	TEST_POSITION_CAMERA,             //46��ⶨλ����ͷ
	TEST_POSITION_CAMERA_POWER,
	TEST_DC5V,
	TEST_DC5V_I8,
	TEST_PATHPLAN_UART,               //47��˴���
	TEST_WIFI,                        //48����wifi
	TEST_BATTERY,                     //49����ص���
    TEST_CHARGE,                      //50�����
	TEST_POWER_POWER,                                            //��ع����
	

	
	TEST_FILE,                        //51����FILE
	TEST_OK                           //52����OK
	
}enum_TEST_CMD;

typedef struct _ST_SYSTEM_MANAGER{
	u32 mSystemTick ;                /*  1ms ģ��δ������   */
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
	u8 mKeyPressFlag : 1;            //  0 : no press    1 : press  ��������
	u8 mScreenPressFlag : 1;         //  0 : no press    1 : press  ��Ļ����
	
	u8 mModePage;
}_ST_MODE_MANAGER;

typedef struct _ST_WORK_MANAGER{
	u8 mWorkMODE ;           //����ģʽ
 	u8 mWorkCMD ;            //����������
 	u8 mWorkSTATUS ;         //������״̬
	
	u8 mWorkInitFlag : 1;    //0:��ʼ��ʧ��   1����ʼ���ɹ�
	u8 mWorkChecking : 1;    //0:û�м��     1�����ڼ����
	u8 mWorkKeyCont ;
	
	u8 mWorkSelectI8OrI9Flag : 2;     //0:i9   1:i8
	
	u8 mWorkFileCont;
}_ST_WORK_MANAGER;


typedef struct _ST_MAINMANAGER{
	/*        �ļ��ڶ���        */
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

