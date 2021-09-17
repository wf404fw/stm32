/*
 * uart.c
 *
 *  Created on: 2014-7-15
 *      Author: dean
 */

#include <msp430.h>
#include "uart.h"

uchar data=0;
u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u32 USART_RX_STA=0;       //接收状态标记


void UART_RS232_Init(void)						 //RS232接口初始化函数
{

	   P4SEL |= BIT5+BIT4;                       // P4.4,5使用外设功能 = UCA1 TXD/RXD
	   UCA1CTL1 |= UCSWRST;                      // 复位USCI
	   UCA1CTL1 |= UCSSEL_1;                     // 设置ACLK时钟，用于发生特定波特率
	   UCA1BR0 = 0x03;                            // 设置波特率， 1MHz 波特率= 9600
	   UCA1BR1 = 0x00;
	   UCA1MCTL |= UCBRS_3 + UCBRF_0;
	   UCA1CTL1 &= ~UCSWRST;                     // 结束复位
	   UCA1IE |= UCRXIE;                         // 使能UCA1接受中断

}
//*************************************************************************
//              串口1发送数据函数
//*************************************************************************

void Send_Byte(unsigned char data)
{
  while(!(UCA1IFG&UCTXIFG));          //发送寄存器空的时候发送数据
  UCA1TXBUF=data;
}

//*************************************************************************
//              串口1发送字符串函数
//*************************************************************************
void Print_Str(unsigned char *s)
{
    while(*s != '\0')
    {
        Send_Byte(*s++);
    }
}


void TimerA_Init(void)							//定时器TA初始化函数
{
	TA0CTL |= MC_1 + TASSEL_2 + TACLR;			//时钟为SMCLK,比较模式，开始时清零计数器
	TA0CCTL0 = CCIE;							//比较器中断使能
	TA0CCR0  = 50000;							//比较值设为50000，相当于50ms的时间间隔
}
