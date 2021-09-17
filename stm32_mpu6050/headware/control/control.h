#ifndef __CONTROL_H
#define __CONTROL_H
#include "sys.h"
   
#define PI 3.14159265
#define ZHONGZHI 0 
#define DIFFERENCE 100
#define POWER_MAX	 	 2400	   //软件极限功率<0-3000>
typedef struct
{
	        float Offset;	  //允许偏差量
			float CurPos;
			float PrevPos;
			float CurAcc;
			float PrevSpeed;

	volatile float SetXPos;	  //设定位置
	volatile float SetYPos;	  //设定位置
	volatile float SetSpeed;  //设定速度
	
	volatile float CurXPos;	  //当前位置
	volatile float CurYPos;	  //当前位置
	volatile float CurSpeed;  //当前速度矢量

	volatile int32_t  PWM;	      //PWM
	volatile uint8_t  ShootFlag;
	volatile uint8_t  AdjustFlag;
	volatile uint8_t  ErrFlag;

	volatile uint32_t SetMaxPos;	  //软件设定最大位置
	volatile uint32_t SetMaxPower;	  //软件设定最大力量
	volatile int32_t  SetMaxSpeed;	  //软件设定最大速度
		
}M1TypeDef,M2TypeDef;


void M1TypeDef_Init(void);
void M2TypeDef_Init(void);
 
int32_t PID_M1_PosLocCalc(float NextRoll,float targetroll ,float p ,float i , float d);
 

void Get_Angle(u8 way);

void CtrlMotor(void);

int myabs(int a);


#endif
