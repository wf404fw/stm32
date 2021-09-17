#include "motor.h"
 
void MiniBalance_Motor_Init(void) // 0��1������ı�ǰ�ֵķ���
{
	RCC->APB2ENR|=1<<3;       //PORTBʱ��ʹ��   PB0,PB1
	RCC->APB2ENR|=1<<4;       //PORTCʱ��ʹ��   PC4,PC5
	GPIOB->CRL&=0XFFFFFF00;   //�������
	GPIOB->CRL|=0X00000022;   //�������
	//GPIOB->ODR|=0<<0;  	
	//GPIOB->ODR|=0<<1;  	
	
	GPIOC->CRL&=0XFF00FFFF;   //�������
	GPIOC->CRL|=0X00220000;   //�������
	//GPIOC->ODR|=0<<4;
	//GPIOC->ODR|=0<<5;  		
}
void MiniBalance_PWM_Init(u16 arr,u16 psc)
{		 					 
    GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
   MiniBalance_Motor_Init();	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);// ʹ�ܶ�ʱ��3
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC , ENABLE);  //ʹ��GPIO����ʱ��ʹ��
   //���ø�����Ϊ�����������,���TIM3 CH1-CH4��PWM���岨��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7| GPIO_Pin_8|GPIO_Pin_9; //TIM_CH1����TIM_CH4
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  //�����������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure); //PC6,PC7,PC8,PC9����·PWM�����
	
	TIM_TimeBaseStructure.TIM_Period = arr; //��������һ�������¼�װ�����Զ���װ�ؼĴ������ڵ�ֵ	 
	TIM_TimeBaseStructure.TIM_Prescaler =psc; //����������ΪTIMxʱ��Ƶ�ʳ�����Ԥ��Ƶֵ  ����Ƶ
	TIM_TimeBaseStructure.TIM_ClockDivision = 0; //����ʱ�ӷָ�:TDTS = Tck_tim
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  //TIM���ϼ���ģʽ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); //����TIM_TimeBaseInitStruct��ָ���Ĳ�����ʼ��TIMx��ʱ�������λ

 
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; //ѡ��ʱ��ģʽ:TIM�����ȵ���ģʽ1
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable; //�Ƚ����ʹ��
	TIM_OCInitStructure.TIM_Pulse = 0;                            //���ô�װ�벶��ȽϼĴ���������ֵ
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;     //�������:TIM����Ƚϼ��Ը�
	TIM_OC1Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx
	TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC3Init(TIM3, &TIM_OCInitStructure);
	TIM_OC4Init(TIM3, &TIM_OCInitStructure);  //����TIM_OCInitStruct��ָ���Ĳ�����ʼ������TIMx

  TIM_CtrlPWMOutputs(TIM3,ENABLE);	//MOE �����ʹ��	

	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH1Ԥװ��ʹ��	 
	TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH2Ԥװ��ʹ��	 
	TIM_OC3PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH3Ԥװ��ʹ��	 
	TIM_OC4PreloadConfig(TIM3, TIM_OCPreload_Enable);  //CH4Ԥװ��ʹ��	 
	
	TIM_ARRPreloadConfig(TIM3, ENABLE); //ʹ��TIMx��ARR�ϵ�Ԥװ�ؼĴ���
	
	TIM_Cmd(TIM3, ENABLE);  //ʹ��TIM3	
} 
void MotorPwmFlash(int16_t MOTO1_PWM,int16_t MOTO2_PWM,int16_t MOTO3_PWM,int16_t MOTO4_PWM) //������·PWM��
{   
	 TIM3->CCR4 = MOTO1_PWM;   //PC9--M1
    TIM3->CCR3 = MOTO2_PWM;   //PC8--M2
    TIM3->CCR2 = MOTO3_PWM;   //PC7--M3
    TIM3->CCR1 = MOTO4_PWM;   //PC6--M4
	 

}