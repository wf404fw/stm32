#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "timer.h"
#include "led.h"
#include "oled.h"
#include "fdc2214.h"
#include "McuDataSend.h"

float res0,res1,res2,res3;
float temp0,temp1,temp2,temp3;  //��ʼֵ

void Sys_Init(void)
{
	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration();//����NVIC�жϷ���2:2��2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	//uart_init(115200);	 //���ڳ�ʼ��Ϊ115200
	LED_Init();
	OLED_Init();
	while(FDC2214_Init());
	led=0;
	delay_ms(100);
	temp0 = Cap_Calculate(0);//��ȡ��ʼֵ
	temp1 = Cap_Calculate(1);
	temp2 = Cap_Calculate(2);
	temp3 = Cap_Calculate(3);
	TIM5_Ctrl_Init(2000-1,720-1);
}

int main(void)
{
  Sys_Init();
	while(1)
	{
		Oled_Printf_Float(0,1,res0-temp0,0);
		Oled_Printf_Float(0,3,res1-temp1,0);
		Oled_Printf_Float(0,5,res2-temp2,0);
		Oled_Printf_Float(0,7,res3-temp3,0);
		//printf("CH0;%3.3f CH1;%3.3f CH2;%3.3f CH3;%3.3f\r\n",res0-temp0,res1-temp1,res2-temp2,res3-temp3);
		while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
    //delay_ms(20);
	}
}


//��ʱ��5�жϷ������
void TIM5_IRQHandler(void)   //TIM5�ж�
{
		if(TIM5->SR&0X0001)//20ms��ʱ�ж�
		 {
			res0 = Cap_Calculate(0);//�ɼ�����
			res1 = Cap_Calculate(1);
			res2 = Cap_Calculate(2);
			res3 = Cap_Calculate(3);
		  //	Data_Send_Status(res,0,0);
		  //	printf("%5d : %5d : %5d\r\n",res0,res1,res2);
			 led=~led;
		 }
	 TIM5->SR&=~(1<<0);  //�жϱ�־λ��0���ȴ���һ���ж�
}
