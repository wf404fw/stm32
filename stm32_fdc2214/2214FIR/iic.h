#ifndef __IIC_H
#define __IIC_H
#define CPU_F ((double)16000000)   //�ⲿ��Ƶ����8MHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEK MiniSTM32������
//IIC���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2014/3/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
   	   		   


#define u8 unsigned char




//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(u8 txd);			//IIC����һ���ֽ�
u8 IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
u8 IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

//���ݿ��ƶ�����޸�
u8 MPU_Read_Byte(u8 addr,u8 reg);   //��һ���ֽ�����
u8 Single_Read(u8 SlaveAddress, u8 reg_add,unsigned int *Read);
unsigned int MPU_Read_2Byte(u8 addr,u8 reg); //�������ֽ�����


u8 MPU_Write_Byte(u8 addr,u8 reg,u8 data);   //дһ���ֽ�����
u8 MPU_Write_2Byte(u8 addr,u8 reg,unsigned int data); //д�����ֽ�����

#endif
















