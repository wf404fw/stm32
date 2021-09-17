#ifndef __MOTOR_H
#define __MOTOR_H
#include <sys.h>	 
 
#define PWMD   TIM3->CCR4  //PC9  其中A、B为前轮PWM波输入——大小相同，方向可以改变；C、D为后轮PWM波输入，其中方向给定，向前
#define PWMC   TIM3->CCR3  //PC8
#define PWMB   TIM3->CCR2   //PC7 
#define PWMA   TIM3->CCR1    //PC6
#define IND   PBout(1)   //INA、INB控制前轮左轮的转向，INC、IND控制前轮右轮的转向
#define INC   PCout(5)  
#define INB   PBout(0)  
#define INA   PCout(4)  
  
void MiniBalance_PWM_Init(u16 arr,u16 psc);//关于前轮相关引脚的初始化设置
void MiniBalance_Motor_Init(void); //电机 PWM输出相关设置
void MotorPwmFlash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM);
#endif