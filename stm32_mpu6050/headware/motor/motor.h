#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 
 
#define PWMD   TIM3->CCR4  //PC9  ����A��BΪǰ��PWM�����롪����С��ͬ��������Ըı䣻C��DΪ����PWM�����룬���з����������ǰ
#define PWMC   TIM3->CCR3  //PC8
#define PWMB   TIM3->CCR2   //PC7 
#define PWMA   TIM3->CCR1    //PC6
#define IND   PBout(1)   //INA��INB����ǰ�����ֵ�ת��INC��IND����ǰ�����ֵ�ת��
#define INC   PCout(5)  
#define INB   PBout(0)  
#define INA   PCout(4)  
  
void MiniBalance_PWM_Init(u16 arr,u16 psc);//����ǰ��������ŵĳ�ʼ������
void MiniBalance_Motor_Init(void); //��� PWM����������
void MotorPwmFlash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM);
#endif