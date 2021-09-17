#include "iic.h"
#include <msp430.h>


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


//初始化IIC

void IIC_Init(void)
{	
  
     P1DIR |=(BIT2+BIT3);
     P1REN |=(BIT2+BIT3);
}   

#define IIC_SDA_1       P1OUT|=BIT3               //SDA = 1
#define IIC_SDA_0       P1OUT&=~BIT3              //SDA = 0
#define IIC_SCL_1       P1OUT|=BIT2               //SCL = 1
#define IIC_SCL_0       P1OUT&=~BIT2              //SCL = 0
#define SDA_IN          P1DIR&=~BIT3             //I/O口为输入
#define SDA_OUT         P1DIR|=BIT3               //I/0口为输出
#define READ_SDA        (P1IN&BIT3)==BIT3
//#define READ_SDA       (P1IN&BIT3)==BIT3  
//#define FDC_SD	            P1OUT &= ~BIT5           //FDC_SD置低
//#define FDC_SD	            P1OUT |=  BIT5           //FDC_SD置高

//void delay_us(u8 z)
//{
//	unsigned int i;
//	for (i = 0; i < (z - 0); i++);		//2
//}


//产生IIC起始信号
void IIC_Start(void)
{
	SDA_OUT;    //sda线输出
	IIC_SDA_1;	  	  
	IIC_SCL_1;
	delay_us(4);
 	IIC_SDA_0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_0;//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void IIC_Stop(void)
{
	SDA_OUT;//sda线输出
	IIC_SCL_0;
	IIC_SDA_0;
 	delay_us(4); 
	IIC_SCL_1;//STOP:when CLK is high DATA change form low to high 
	IIC_SDA_1;//发送I2C总线结束信号 	
 	delay_us(4);
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
        SDA_IN;//SDA设置为输入
	IIC_SDA_1;delay_us(1);
	IIC_SCL_1;delay_us(1);

	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
                        
		}
	}
	IIC_SDA_0;
	IIC_SCL_0;//时钟输出0 
	return 0;  
} 
//产生ACK应答
void IIC_Ack(void)
{
    SDA_OUT;
    P1REN &=~(BIT2+BIT3);
	IIC_SDA_0;
	IIC_SCL_1;
	_nop();
	IIC_SCL_0;
	IIC_SDA_1;
	_nop();
	IIC_SCL_0;
	IIC_SDA_0;
	P1REN |=(BIT2+BIT3);
}
//不产生ACK应答		    
void IIC_NAck(void)
{
	SDA_OUT;
	IIC_SCL_0;	
	IIC_SDA_1;
	delay_us(2);
	IIC_SCL_1;
	delay_us(2);
	IIC_SCL_0;
	IIC_SDA_0;	
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT; 	    
    IIC_SCL_0;//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {   
		if(txd & 0x80)
		{
		     IIC_SDA_1; 
		}
		else
		{
			 IIC_SDA_0;
		}
         txd<<=1; 	  
		 delay_us(2);
		 IIC_SCL_1;
		 delay_us(2);				
		 IIC_SCL_0;		
    }	 
} 	

 
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
        SDA_IN; //SDA设置为输入
       IIC_SDA_1;
    for(i=0;i<8;i++ )
	{
        IIC_SCL_0;
        delay_us(2);
		IIC_SCL_1;
		delay_us(4);
        receive<<=1;
        if(READ_SDA)receive++;
		delay_us(2);
    }
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;
}
unsigned int IIC_Read_Byte_16(unsigned char ack)
{
    unsigned int i,receive=0;
        SDA_IN; //SDA设置为输入
       IIC_SDA_1;
    for(i=0;i<16;i++ )
    {
        IIC_SCL_0;
        delay_us(2);
        IIC_SCL_1;
        delay_us(4);
        receive<<=1;
        if(READ_SDA)receive++;
        delay_us(2);
    }
    if (!ack)
        IIC_NAck();//发送nACK
    else
        IIC_Ack(); //发送ACK
    return receive;
}


u8 MPU_Read_Byte(u8 addr,u8 reg)
{
		u8 res;
		IIC_Start(); 
		IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
		IIC_Wait_Ack();		//等待应答 
        IIC_Send_Byte(reg);	//写寄存器地址
        IIC_Wait_Ack();		//等待应答
        IIC_Start();
		IIC_Send_Byte((addr<<1)|1);//发送器件地址+读命令	
        IIC_Wait_Ack();		//等待应答 
		res=IIC_Read_Byte(0);//读取数据,发送nACK 
        IIC_Stop();			//产生一个停止条件 
		return res;		
}
//单字节读取*****************************************
u8 Single_Read(u8 SlaveAddress, u8 reg_add,unsigned int *Read)
{  
	u8 Dat_L = 0;
	u8 Dat_H = 0;
	
	/* 器件地址 */
	IIC_Start();
	IIC_Send_Byte(SlaveAddress << 1);
	if (IIC_Wait_Ack() == 1)
	{
		return 0;
	}
	
	/* 寄存器地址 */
	IIC_Send_Byte(reg_add);
	if (IIC_Wait_Ack() == 1)
	{
		return 0;
	}
	
	/* 器件地址（读）*/
	IIC_Start();
	
	IIC_Send_Byte((SlaveAddress << 1) + 1);
	if (IIC_Wait_Ack() == 1)
	{
		return 0;
	}
		
	
	Dat_H = IIC_Read_Byte(1);	//ack
	Dat_L = IIC_Read_Byte(0);	//Nack
	
	IIC_Stop();
		
	*Read = ((Dat_H << 8) | Dat_L);
	
	return 1;
}	

unsigned int MPU_Read_2Byte(u8 addr,u8 reg)
{
	 
		unsigned int res=0;
		IIC_Start(); 
		IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令
	    if (IIC_Wait_Ack() == 1)//等待应答
	    {
		    return 0;
	    }	 
        IIC_Send_Byte(reg);	//写寄存器地址
	    if (IIC_Wait_Ack() == 1)//等待应答
	    {
		    return 0;
	    }

        IIC_Start();
		IIC_Send_Byte((addr<<1)|1);//发送器件地址+读命令
	    if (IIC_Wait_Ack() == 1)//等待应答
	    {
		    return 0;
	    }
		res=IIC_Read_Byte(1);//读取数据,发送ACK
		res<<=8;
		IIC_Ack();
		res|=IIC_Read_Byte(0);//读取数据,发送nACK
        IIC_Stop();			//产生一个停止条件 
		return res;		
}



u8 MPU_Write_Byte(u8 addr,u8 reg,u8 data) 				 
{ 
  IIC_Start(); 
	IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
	if(IIC_Wait_Ack())	//等待应答
	{
		IIC_Stop();		 
		return 1;		
	}
  IIC_Send_Byte(reg);	//写寄存器地址
  IIC_Wait_Ack();		//等待应答 
	IIC_Send_Byte(data);//发送数据
	if(IIC_Wait_Ack())	//等待ACK
	{
		IIC_Stop();	 
		return 1;		 
	}		 
  IIC_Stop();	 
	return 0;
}

u8 MPU_Write_2Byte(u8 addr,u8 reg,unsigned int data)
{ 
		static u8 buffer[2];	
		buffer[0] = (data >> 8);
		buffer[1] = (u8)(data & 0x00ff);	
	
    IIC_Start(); 
	IIC_Send_Byte((addr<<1)|0);//发送器件地址+写命令	
	if(IIC_Wait_Ack())	//等待应答
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte(reg);	//写寄存器地址
	if(IIC_Wait_Ack())	//等待应答
	{
		IIC_Stop();		 
		return 1;		
	}
	IIC_Send_Byte(buffer[0]);//发送数据
	if(IIC_Wait_Ack())	//等待应答
	{
		IIC_Stop();		 
		return 1;		
	}
	IIC_Send_Byte(buffer[1]);//发送数据
	if(IIC_Wait_Ack())	//等待ACK
	{
		IIC_Stop();	 
		return 1;		 
	}
	
   IIC_Stop();	 
	return 0;
}
