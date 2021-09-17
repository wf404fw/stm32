#include "show.h"
#include"control.h"
extern M1TypeDef  M1;
extern  M2TypeDef  M2;
   extern int d;
extern	float R;
extern	float baijiao ;
  /**************************************************************************
作者：平衡小车之家
我的淘宝小店：http://shop114407458.taobao.com/
**************************************************************************/
unsigned char i;          //计数变量
unsigned char Send_Count; //串口需要发送的数据个数
float Vol;
/**************************************************************************
函数功能：OLED显示
入口参数：无
返回  值：无
**************************************************************************/
void oled_show(void)
{
					//=============显示角度=======================//
		                      OLED_ShowString(00,00,"AngleX");
		if(Pitch<0)		     OLED_ShowString(65,00, "-"),
	                        OLED_ShowNumber(75,00,-Pitch,3,12);
		else 					  OLED_ShowString(65,00, "+"),      
			               OLED_ShowNumber(75,00,Pitch,3,12);
			//=============显示角度=======================//
			                      OLED_ShowString(00,10,"AngleY");
	 	if(Roll<0)		 OLED_ShowString(65,10, "-"),
			               OLED_ShowNumber(75,10,-Roll,3,12);
		 else					 OLED_ShowString(65,10, "+"),       
			             OLED_ShowNumber(75,10,Roll,3,12);
				//=============显示角度=======================//
			                      OLED_ShowString(00,20,"AngleZ");
	 	if(Yaw<0)		  OLED_ShowString(65,20, "+"),
			              OLED_ShowNumber(75,20,-Yaw,3,12);
		 else					 OLED_ShowString(65,20, "-"),       
			             OLED_ShowNumber(75,20,Yaw,3,12);
		 
		 //显示模式
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
		
		 
		//=============刷新=======================//
		OLED_Refresh_Gram();	
	}
/**************************************************************************
函数功能：虚拟示波器往上位机发送数据 关闭显示屏
入口参数：无
返回  值：无
作    者：平衡小车之家
**************************************************************************/
void DataScope(void)
{   
		DataScope_Get_Channel_Data( Roll, 1 );       //显示角度 单位：度（°）
		DataScope_Get_Channel_Data(Pitch, 2 );         //显示超声波测量的距离 单位：CM 
		DataScope_Get_Channel_Data( -Yaw, 3 );                 //显示电氐缪高单位：V
	DataScope_Get_Channel_Data( M1.PWM  , 4 );   
		DataScope_Get_Channel_Data(M2.PWM, 5 ); //用您要显示的数据替换0就行了
//		DataScope_Get_Channel_Data(0 , 6 );//用您要显示的数据替换0就行了
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