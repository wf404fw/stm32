#include"beep.h"
void beep_init()
{
   		GPIO_InitTypeDef  GPIO_InitStructure;
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	    //使能PB端口时钟
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;			    //LED0-->PB.8 端口配置
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 	 //推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //IO口速度为50MHz
  GPIO_Init(GPIOB, &GPIO_InitStructure);			      
  GPIO_SetBits(GPIOB,GPIO_Pin_8);
	 






}
