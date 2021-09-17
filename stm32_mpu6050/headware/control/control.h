#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
   
#define PI 3.14159265
#define ZHONGZHI 0 
#define DIFFERENCE 100
#define POWER_MAX	 	 2400	   //������޹���<0-3000>
typedef struct
{
	        float Offset;	  //����ƫ����
			float CurPos;
			float PrevPos;
			float CurAcc;
			float PrevSpeed;

	volatile float SetXPos;	  //�趨λ��
	volatile float SetYPos;	  //�趨λ��
	volatile float SetSpeed;  //�趨�ٶ�
	
	volatile float CurXPos;	  //��ǰλ��
	volatile float CurYPos;	  //��ǰλ��
	volatile float CurSpeed;  //��ǰ�ٶ�ʸ��

	volatile int32_t  PWM;	      //PWM
	volatile uint8_t  ShootFlag;
	volatile uint8_t  AdjustFlag;
	volatile uint8_t  ErrFlag;

	volatile uint32_t SetMaxPos;	  //����趨���λ��
	volatile uint32_t SetMaxPower;	  //����趨�������
	volatile int32_t  SetMaxSpeed;	  //����趨����ٶ�
		
}M1TypeDef,M2TypeDef;


void M1TypeDef_Init(void);
void M2TypeDef_Init(void);
 
int32_t PID_M1_PosLocCalc(float NextRoll,float targetroll ,float p ,float i , float d);
 

void Get_Angle(u8 way);

void CtrlMotor(void);

int myabs(int a);


#endif
