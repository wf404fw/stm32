#include "show.h"
#include"control.h"
extern M1TypeDef  M1;
extern  M2TypeDef  M2;
   extern int d;
extern	float R;
extern	float baijiao ;
  /**************************************************************************
���ߣ�ƽ��С��֮��
�ҵ��Ա�С�꣺http://shop114407458.taobao.com/
**************************************************************************/
unsigned char i;          //��������
unsigned char Send_Count; //������Ҫ���͵����ݸ���
float Vol;
/**************************************************************************
�������ܣ�OLED��ʾ
��ڲ�������
����  ֵ����
**************************************************************************/
void oled_show(void)
{
					//=============��ʾ�Ƕ�=======================//
		                      OLED_ShowString(00,00,"AngleX");
		if(Pitch<0)		     OLED_ShowString(65,00, "-"),
	                        OLED_ShowNumber(75,00,-Pitch,3,12);
		else 					  OLED_ShowString(65,00, "+"),      
			               OLED_ShowNumber(75,00,Pitch,3,12);
			//=============��ʾ�Ƕ�=======================//
			                      OLED_ShowString(00,10,"AngleY");
	 	if(Roll<0)		 OLED_ShowString(65,10, "-"),
			               OLED_ShowNumber(75,10,-Roll,3,12);
		 else					 OLED_ShowString(65,10, "+"),       
			             OLED_ShowNumber(75,10,Roll,3,12);
				//=============��ʾ�Ƕ�=======================//
			                      OLED_ShowString(00,20,"AngleZ");
	 	if(Yaw<0)		  OLED_ShowString(65,20, "+"),
			              OLED_ShowNumber(75,20,-Yaw,3,12);
		 else					 OLED_ShowString(65,20, "-"),       
			             OLED_ShowNumber(75,20,Yaw,3,12);
		 
		 //��ʾģʽ
	/*	 OLED_ShowString(00,30," one:");
		 OLED_ShowString(65,30," two:");
		 OLED_ShowString(00,40," three:");
		 OLED_ShowString(60,40," four:");
		 OLED_ShowString(00,50," five:");
		 OLED_ShowString(65,50," six:");
		 if(d==1) OLED_ShowChar(41,30,'Y',12,1);
		// else
		 if(d==2) OLED_ShowChar(104,30,'Y',12,1);
		// else
		  if(d==3) OLED_ShowChar(55,40,'Y',12,1);
		// else
		 if(d==4)OLED_ShowChar(111,40,'Y',12,1);
		// else
			if(d==5) OLED_ShowChar(50,50,'Y',12,1);
		// else
		if(d==6) OLED_ShowChar(104,50,'Y',12,1);
		// else
		//	OLED_ShowString(20 ,30,"Y"); */
	/*	OLED_ShowString(00,30," mode:");
		OLED_ShowNumber(50,30,d,1,12);
		OLED_ShowString(00,40," R:");
		OLED_ShowNumber(20,40,R,3,12);
		OLED_ShowString(00,50," baijiao:");
		OLED_ShowNumber(70,50,baijiao,3,12); */
		
		 
		//=============ˢ��=======================//
		OLED_Refresh_Gram();	
	}
/**************************************************************************
�������ܣ�����ʾ��������λ���������� �ر���ʾ��
��ڲ�������
����  ֵ����
��    �ߣ�ƽ��С��֮��
**************************************************************************/
void DataScope(void)
{   
		DataScope_Get_Channel_Data( Roll, 1 );       //��ʾ�Ƕ� ��λ���ȣ��㣩
		DataScope_Get_Channel_Data(Pitch, 2 );         //��ʾ�����������ľ��� ��λ��CM 
		DataScope_Get_Channel_Data( -Yaw, 3 );                 //��ʾ��ص�Ѹߵ�λ��V
	DataScope_Get_Channel_Data( M1.PWM  , 4 );   
		DataScope_Get_Channel_Data(M2.PWM, 5 ); //����Ҫ��ʾ�������滻0������
//		DataScope_Get_Channel_Data(0 , 6 );//����Ҫ��ʾ�������滻0������
//		DataScope_Get_Channel_Data(0, 7 );
//		DataScope_Get_Channel_Data( 0, 8 ); 
//		DataScope_Get_Channel_Data(0, 9 );  
//		DataScope_Get_Channel_Data( 0 , 10);
		Send_Count = DataScope_Data_Generate(5);
		for( i = 0 ; i < Send_Count; i++) 
		{
		while((USART1->SR&0X40)==0);  
		USART1->DR = DataScope_OutPut_Buffer[i]; 
		}
}