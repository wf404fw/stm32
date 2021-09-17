#include "iic.h"
#include <msp430.h>


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


//��ʼ��IIC

void IIC_Init(void)
{	
  
     P1DIR |=(BIT2+BIT3);
     P1REN |=(BIT2+BIT3);
}   

#define IIC_SDA_1       P1OUT|=BIT3               //SDA = 1
#define IIC_SDA_0       P1OUT&=~BIT3              //SDA = 0
#define IIC_SCL_1       P1OUT|=BIT2               //SCL = 1
#define IIC_SCL_0       P1OUT&=~BIT2              //SCL = 0
#define SDA_IN          P1DIR&=~BIT3             //I/O��Ϊ����
#define SDA_OUT         P1DIR|=BIT3               //I/0��Ϊ���
#define READ_SDA        (P1IN&BIT3)==BIT3
//#define READ_SDA       (P1IN&BIT3)==BIT3  
//#define FDC_SD	            P1OUT &= ~BIT5           //FDC_SD�õ�
//#define FDC_SD	            P1OUT |=  BIT5           //FDC_SD�ø�

//void delay_us(u8 z)
//{
//	unsigned int i;
//	for (i = 0; i < (z - 0); i++);		//2
//}


//����IIC��ʼ�ź�
void IIC_Start(void)
{
	SDA_OUT;    //sda�����
	IIC_SDA_1;	  	  
	IIC_SCL_1;
	delay_us(4);
 	IIC_SDA_0;//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	IIC_SCL_0;//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void IIC_Stop(void)
{
	SDA_OUT;//sda�����
	IIC_SCL_0;
	IIC_SDA_0;
 	delay_us(4); 
	IIC_SCL_1;//STOP:when CLK is high DATA change form low to high 
	IIC_SDA_1;//����I2C���߽����ź� 	
 	delay_us(4);
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
        SDA_IN;//SDA����Ϊ����
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
	IIC_SCL_0;//ʱ�����0 
	return 0;  
} 
//����ACKӦ��
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
//������ACKӦ��		    
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
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
	SDA_OUT; 	    
    IIC_SCL_0;//����ʱ�ӿ�ʼ���ݴ���
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

 
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
        SDA_IN; //SDA����Ϊ����
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;
}
unsigned int IIC_Read_Byte_16(unsigned char ack)
{
    unsigned int i,receive=0;
        SDA_IN; //SDA����Ϊ����
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
        IIC_NAck();//����nACK
    else
        IIC_Ack(); //����ACK
    return receive;
}


u8 MPU_Read_Byte(u8 addr,u8 reg)
{
		u8 res;
		IIC_Start(); 
		IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
		IIC_Wait_Ack();		//�ȴ�Ӧ�� 
        IIC_Send_Byte(reg);	//д�Ĵ�����ַ
        IIC_Wait_Ack();		//�ȴ�Ӧ��
        IIC_Start();
		IIC_Send_Byte((addr<<1)|1);//����������ַ+������	
        IIC_Wait_Ack();		//�ȴ�Ӧ�� 
		res=IIC_Read_Byte(0);//��ȡ����,����nACK 
        IIC_Stop();			//����һ��ֹͣ���� 
		return res;		
}
//���ֽڶ�ȡ*****************************************
u8 Single_Read(u8 SlaveAddress, u8 reg_add,unsigned int *Read)
{  
	u8 Dat_L = 0;
	u8 Dat_H = 0;
	
	/* ������ַ */
	IIC_Start();
	IIC_Send_Byte(SlaveAddress << 1);
	if (IIC_Wait_Ack() == 1)
	{
		return 0;
	}
	
	/* �Ĵ�����ַ */
	IIC_Send_Byte(reg_add);
	if (IIC_Wait_Ack() == 1)
	{
		return 0;
	}
	
	/* ������ַ������*/
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
		IIC_Send_Byte((addr<<1)|0);//����������ַ+д����
	    if (IIC_Wait_Ack() == 1)//�ȴ�Ӧ��
	    {
		    return 0;
	    }	 
        IIC_Send_Byte(reg);	//д�Ĵ�����ַ
	    if (IIC_Wait_Ack() == 1)//�ȴ�Ӧ��
	    {
		    return 0;
	    }

        IIC_Start();
		IIC_Send_Byte((addr<<1)|1);//����������ַ+������
	    if (IIC_Wait_Ack() == 1)//�ȴ�Ӧ��
	    {
		    return 0;
	    }
		res=IIC_Read_Byte(1);//��ȡ����,����ACK
		res<<=8;
		IIC_Ack();
		res|=IIC_Read_Byte(0);//��ȡ����,����nACK
        IIC_Stop();			//����һ��ֹͣ���� 
		return res;		
}



u8 MPU_Write_Byte(u8 addr,u8 reg,u8 data) 				 
{ 
  IIC_Start(); 
	IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();		 
		return 1;		
	}
  IIC_Send_Byte(reg);	//д�Ĵ�����ַ
  IIC_Wait_Ack();		//�ȴ�Ӧ�� 
	IIC_Send_Byte(data);//��������
	if(IIC_Wait_Ack())	//�ȴ�ACK
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
	IIC_Send_Byte((addr<<1)|0);//����������ַ+д����	
	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();		 
		return 1;		
	}
    IIC_Send_Byte(reg);	//д�Ĵ�����ַ
	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();		 
		return 1;		
	}
	IIC_Send_Byte(buffer[0]);//��������
	if(IIC_Wait_Ack())	//�ȴ�Ӧ��
	{
		IIC_Stop();		 
		return 1;		
	}
	IIC_Send_Byte(buffer[1]);//��������
	if(IIC_Wait_Ack())	//�ȴ�ACK
	{
		IIC_Stop();	 
		return 1;		 
	}
	
   IIC_Stop();	 
	return 0;
}
