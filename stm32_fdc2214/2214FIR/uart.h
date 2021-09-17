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

#define USART_REC_LEN           100      //�����������ֽ��� 200
extern uchar data;
extern u8 USART_RX_BUF[USART_REC_LEN];     //���ջ���,���USART_REC_LEN���ֽ�.
extern u32 USART_RX_STA;       //����״̬���

void UART_RS232_Init(void);
void TimerA_Init(void);
void Send_Byte(unsigned char data);
void Print_Str(unsigned char *s);
#endif /* UART_H_ */
