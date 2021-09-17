 #include "stm32f10x.h"
  #include "led.h"
 #include "delay.h"
 #include"beep.h" 
 #include"sys.h"
 float Pitch,Roll,Yaw; 
int main( )
 {	 Stm32_Clock_Init(9);            //=====ϵͳʱ������
	delay_init(72);                 //=====��ʱ��ʼ��
	JTAG_Set(JTAG_SWD_DISABLE);     //=====�ر�JTAG�ӿ�
	JTAG_Set(SWD_ENABLE);           //=====��SWD�ӿ� �������������SWD�ӿڵ���
	LED_Init();                     //=====��ʼ���� LED ���ӵ�Ӳ���ӿ�
//	KEY_Init();                     //=====������ʼ��
	OLED_Init();                    //=====OLED��ʼ��
	uart_init(72,128000);           //=====����1��ʼ��
	IIC_Init();                     //=====IIC��ʼ��
  MPU6050_initialize();           //=====MPU6050��ʼ��	
  DMP_Init();                     //=====��ʼ��DMP     
//  EXTI_Init();                    //=====MPU6050 5ms��ʱ�жϳ�ʼ��
//	TIM1_Int_Init(4,4900);
//	MiniBalance_PWM_Init(7199,0);   //=====��ʼ��PWM 10KHZ������������� �����ʼ������ӿ� 
      
  while(1)
	{
	  
	}
 }
 
 