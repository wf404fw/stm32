#include "control.h"	
//#include "filter.h"	
#include "motor.h"
#include "math.h"
#include"sys.h"
M1TypeDef M1;
M2TypeDef M2;
float Position_P1,   Position_I1 ,  Position_D1 ;//λ�û��е�Ⱥ�ӱ���
static float Bias1 , Pwm1, Integral_bias1  , Last_bias1; //λ�û��еľ�̬����
float Yaw0 ,Movement;//����ʱ�ĳ�ʼ�Ƕ�

void M1TypeDef_Init(void)  
{
	M1.CurPos    = 0.0;
	M1.PrevPos   = 0.0;
	M1.CurAcc    = 0.0;
	M1.PrevSpeed = 0.0;
 	M1.Offset    = 0.1;   //����ƫ����
	M1.CurSpeed  = 0.0;  //��ǰ�ٶ�ʸ��
	M1.PWM = 0;	         //PWM
}

void M2TypeDef_Init(void)
{
	M2.CurPos    = 0.0;
	M2.PrevPos   = 0.0;
	M2.CurAcc    = 0.0;
	M2.PrevSpeed = 0.0;
 	M2.Offset    = 0.1;   //����ƫ����
	M2.CurSpeed  = 0.0;  //��ǰ�ٶ�ʸ��
	M2.PWM = 0;	         //PWM		
}

int myabs(int a) //ȡ����ֵ����
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}

void Get_Angle(u8 way)  //��ȡ�ǶȺ���
{ 
	    if(way==1)                           //===DMP�Ķ�ȡ�����ݲɼ��ж϶�ȡ���ϸ���ѭʱ��Ҫ��
			{	
					Read_DMP();                      //===��ȡ���ٶȡ����ٶȡ����
			}			
}


int32_t PID_M1_PosLocCalc(float NextYaw,float targetYaw ,float p ,float i , float d) /*//X��pwm*/ //����
{    Read_DMP( );
 
	    
	   
	  Position_P1=p ,  Position_I1=i ,  Position_D1=d ;
	  Bias1=targetYaw-NextYaw +Yaw0+Movement;
	  Integral_bias1+=Bias1;
	  Pwm1=Position_P1*Bias1+Position_I1*Integral_bias1+Position_D1*(Bias1-Last_bias1);
	  Last_bias1=Bias1;
	  return Pwm1;
	
}

void CtrlMotor(void)
{
		  Read_DMP( );
	  
	                                 //===��ȡ�Ƕ�ֵ
	  M1.PWM = PID_M1_PosLocCalc(  Yaw,  0, 300 ,  0 ,  1);
	  M2.PWM =1500; //���������ٶȸ���
	  if(M1.PWM > POWER_MAX)  M1.PWM =  POWER_MAX; //����
	  if(M1.PWM < -POWER_MAX) M1.PWM = -POWER_MAX;
      
	 if(M1.PWM>0)  //λ��ƫ�� ����ǰת ���ֺ�ת
	 {   INA=1,INB=0,INC=0,IND=1;
		  PWMA=M1.PWM;
		  PWMB=M1.PWM;
	 }
	 if(M1.PWM<0)//����ƫ
	 {    INA=0,INB=1,INC=1,IND=0;
		   PWMA=myabs(M1.PWM);
		   PWMB=myabs(M1.PWM);
	 }
	     
	 
	 PWMC= PWMD =M2.PWM;
	  
	
}
	
	

