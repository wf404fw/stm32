/*
 * uart.h
 *
 *  Created on: 2014-7-15
 *      Author: dean
 */

#ifndef UART_H_
#define UART_H_
#define uchar unsigned char
#define u8 unsigned char
#define u32 unsigned int

#define USART_REC_LEN           100      //定义最大接收字节数 200
extern uchar data;
extern u8 USART_RX_BUF[USART_REC_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
extern u32 USART_RX_STA;       //接收状态标记

void UART_RS232_Init(void);
void TimerA_Init(void);
void Send_Byte(unsigned char data);
void Print_Str(unsigned char *s);
#endif /* UART_H_ */
