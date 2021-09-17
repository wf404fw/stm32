#ifndef __IIC_H
#define __IIC_H
#define CPU_F ((double)16000000)   //外部高频晶振8MHZ
#define delay_us(x) __delay_cycles((long)(CPU_F*(double)x/1000000.0))
#define delay_ms(x) __delay_cycles((long)(CPU_F*(double)x/1000.0))
//////////////////////////////////////////////////////////////////////////////////	 
//本程序只供学习使用，未经作者许可，不得用于其它任何用途
//ALIENTEK MiniSTM32开发板
//IIC驱动 代码	   
//正点原子@ALIENTEK
//技术论坛:www.openedv.com
//修改日期:2014/3/9
//版本：V1.0
//版权所有，盗版必究。
//Copyright(C) 广州市星翼电子科技有限公司 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////
   	   		   


#define u8 unsigned char




//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(u8 txd);			//IIC发送一个字节
u8 IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
u8 IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

//根据控制对象而修改
u8 MPU_Read_Byte(u8 addr,u8 reg);   //读一个字节数据
u8 Single_Read(u8 SlaveAddress, u8 reg_add,unsigned int *Read);
unsigned int MPU_Read_2Byte(u8 addr,u8 reg); //读两个字节数据


u8 MPU_Write_Byte(u8 addr,u8 reg,u8 data);   //写一个字节数据
u8 MPU_Write_2Byte(u8 addr,u8 reg,unsigned int data); //写两个字节数据

#endif
















