 #include "stm32f10x.h"
  #include "led.h"
 #include "delay.h"
 #include"beep.h" 
 #include"sys.h"
 float Pitch,Roll,Yaw; 
int main( )
 {	 Stm32_Clock_Init(9);            //=====系统时钟设置
	delay_init(72);                 //=====延时初始化
	JTAG_Set(JTAG_SWD_DISABLE);     //=====关闭JTAG接口
	JTAG_Set(SWD_ENABLE);           //=====打开SWD接口 可以利用主板的SWD接口调试
	LED_Init();                     //=====初始化与 LED 连接的硬件接口
//	KEY_Init();                     //=====按键初始化
	OLED_Init();                    //=====OLED初始化
	uart_init(72,128000);           //=====串口1初始化
	IIC_Init();                     //=====IIC初始化
  MPU6050_initialize();           //=====MPU6050初始化	
  DMP_Init();                     //=====初始化DMP     
//  EXTI_Init();                    //=====MPU6050 5ms定时中断初始化
//	TIM1_Int_Init(4,4900);
//	MiniBalance_PWM_Init(7199,0);   //=====初始化PWM 10KHZ，用于驱动电机 如需初始化电调接口 
      
  while(1)
	{
	  
	}
 }
 
 