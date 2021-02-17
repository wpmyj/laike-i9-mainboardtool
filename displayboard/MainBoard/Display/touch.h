/****************************************************************************************************/
/*			@FileName		:	TOUCH.h																																		   	*/
/*			@Author			:	zhengbaiqiu																																		*/
/*			@Version		:	v1.0																																					*/
/*			@Date			:	2019.11.12  																																	*/
/****************************************************************************************************/

#ifndef	__TOUCH_H__
#define	__TOUCH_H__
#include "stm32f10x.h"

#ifdef __cplusplus
extern "C" {
#endif


#define TP_PRES_DOWN 0x80  //����������	  
#define TP_CATH_PRES 0x40  //�а��������� 	  
										    
//������������
typedef struct
{
	u8 (*init)(void);			//��ʼ��������������
	u8 (*scan)(u8);				//ɨ�败����.0,��Ļɨ��;1,��������;	 
	void (*adjust)(void);		//������У׼
	u16 x0;						//ԭʼ����(��һ�ΰ���ʱ������)
	u16 y0;
	u16 x; 						//��ǰ����(�˴�ɨ��ʱ,����������)
	u16 y;						   	    
	u8  sta;					//�ʵ�״̬ 
								//b7:����1/�ɿ�0; 
	                            //b6:0,û�а�������;1,�а�������.         			  
////////////////////////������У׼����/////////////////////////								
	float xfac;					
	float yfac;
	short xoff;
	short yoff;	   
//�����Ĳ���,��������������������ȫ�ߵ�ʱ��Ҫ�õ�.
//touchtype=0��ʱ��,�ʺ�����ΪX����,����ΪY�����TP.
//touchtype=1��ʱ��,�ʺ�����ΪY����,����ΪX�����TP.
	u8 touchtype;
}_m_tp_dev;

extern _m_tp_dev tp_dev;	 	//������������touch.c���涨��

//�봥����оƬ��������	   
//�봥����оƬ��������	   
// #define PEN  PCin(10)    //PC10  INT
// #define DOUT PCin(2)     //PC2  MISO		 PC2--PB14
// #define TDIN PCout(3)    //PC3  MOSI		 PC3--PB15
// #define TCLK PCout(0)    //PC0  SCLK	 PC0--PB13
// #define TCS  PCout(13)   //PC13 CS    


// #define PEN  PCin(12)    //PC10  INT
// #define DOUT PCin(9)     //PC2  MISO		 PC2--PB14
// #define TDIN PCout(8)    //PC3  MOSI		 PC3--PB15
// #define TCLK PCout(6)    //PC0  SCLK	 PC0--PB13
// #define TCS  PCout(7)    //PC13 CS    

#define PEN  PDin(8)      //PD8   INT
#define DOUT PBin(15)     //PB15  MISO		 PC2--PB14
#define TDIN PBout(14)    //PB14  MOSI		 PC3--PB15
#define TCLK PBout(13)    //PB13  SCLK	 PC0--PB13
#define TCS  PBout(12)    //PB12  CS    
     

void TP_Write_Byte(u8 num);						//�����оƬд��һ������
u16 TP_Read_AD(u8 CMD);							//��ȡADת��ֵ
u16 TP_Read_XOY(u8 xy);							//���˲��������ȡ(X/Y)
u8 TP_Read_XY(u16 *x,u16 *y);					//˫�����ȡ(X+Y)
u8 TP_Read_XY2(u16 *x,u16 *y);					//����ǿ�˲���˫���������ȡ
void TP_Drow_Touch_Point(u16 x,u16 y,u16 color);//��һ������У׼��
void TP_Draw_Big_Point(u16 x,u16 y,u16 color);	//��һ�����
u8 TP_Scan(u8 tp);								//ɨ��
void TP_Save_Adjdata(void);						//����У׼����
u8 TP_Get_Adjdata(void);						//��ȡУ׼����
void TP_Adjust(void);							//������У׼
u8 TP_Init(void);								//��ʼ��

void Read_Touch(void);
																 
void TP_Adj_Info_Show(u16 x0,u16 y0,u16 x1,u16 y1,u16 x2,u16 y2,u16 x3,u16 y3,u16 fac);//��ʾУ׼��Ϣ
	
	
#ifdef _cplusplus
extern }
#endif

#endif /*__TOUCH_H__*/	


