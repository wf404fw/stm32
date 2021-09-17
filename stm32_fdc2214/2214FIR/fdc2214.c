/**
******************************************************************************
* @file    FDC2214.c
* @author  BOB   
* @version V1.0
* @date    2018-07-5
* @email   
* @brief   FDC2214闁板秶鐤嗛崣濠冩殶閹诡喛顕伴崣鏍у毐閺�?
******************************************************************************
**/

#include "fdc2214.h"
#include "iic.h"
#include "math.h"
#include "msp430.h"


 //ADDR閸滃D瀵洝鍓奸崚婵嗩潗閸�?
#define FDC_ADDR_0	        P1OUT &= ~BIT4           //FDC_ADDR缂冾喕缍�
#define FDC_ADDR_1	        P1OUT |=  BIT4           //FDC_ADDR缂冾噣鐝�

#define FDC_SD_0	            P1OUT &= ~BIT5           //FDC_SD缂冾喕缍�
#define FDC_SD_1	            P1OUT |=  BIT5           //FDC_SD缂冾噣鐝�



/***************************************
 * 閸戣姤鏆熼崥宥忕窗ADDR_SD_Init
 * 閹诲繗鍫�  閿涙岸鍘ょ純鐢僁C閻€劌鍩岄惃鍑�/O閸�?
                   ADDR--PC11
				   SD  --PC12
 * 鏉堟挸鍙�  閿涙碍妫�
 * 鏉堟挸鍤�  閿涙碍妫�
 **************************************/
/*
void ADDR_SD_Init(void)       //ADDR閸滃D瀵洝鍓奸崚婵嗩潗閸�?
{					     

  
}
*/

/***************************************
 * 閸戣姤鏆熼崥宥忕窗InitFDC2214
 * 閹诲繗鍫�  閿涙艾鍨垫慨瀣FDC2214
 * 鏉堟挸鍙�  閿涙碍妫�
 * 鏉堟挸鍤�  閿涙etVal  0 and 1
 **************************************/
u8 FDC2214_init(void)
{
	unsigned int id;
	u8 retVal=0;
	u8 ErrCount = 0;
	
	FDC_ADDR_0;// ADDR=0(FDC2214_IIC閸︽澘娼冮柅澶嬪=0X2A) // ADDR=1(FDC2214_IIC閸︽澘娼冮柅澶嬪=0X2B)
	FDC_SD_0;  // SD=0瀵�?閸氼垵绶崗?   // SD=1閸忔娊妫存潏鎾冲弳
	
    default_addr = 0x2a;  //FDC2214閸︽澘娼冮柅澶嬪閺嗗倸鐡�
    delay_ms(10);	
	
	// software reset 
	MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_RESET_DEVICE,0x8000);
	
    delay_ms(10);
	
	do
	{
		if (ErrCount++ > 50)
			{
				return 0;
			}
		retVal=0;
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH0,0xFFFF); // 4 clock periods
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH1,0xFFFF);
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH2,0xFFFF);
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_REF_COUNT_CH3,0xFFFF);
			
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_OFFSET_CH0,0x0000);    //鐞涖儱浼╅崐?
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_OFFSET_CH1,0x0000);
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_OFFSET_CH2,0x0000);
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_OFFSET_CH3,0x0000);
			
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH0,0x0400); // 1 clock period
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH1,0x0400);
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH2,0x0400);
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_SETTLE_COUNT_CH3,0x0400);
			
	    retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH0,0x1001); // 1000
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH1,0x1001);
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH2,0x1001);
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH3,0x1001);
			
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH0,0xF800); //
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH1,0xF800); //
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH2,0xF800); //
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_DRIVE_CURRENT_CH3,0xF800); //
			
		retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_ERROR_CONFIG,0x0001); // report only DRDYs to INT
		
			
	    retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_MUX_CONFIG,0xC20C); // ch0, ch1,ch2,ch3-> Wipro for 4 ch
			
	    retVal |= MPU_Write_2Byte(default_addr,LDC13xx16xx_CMD_CONFIG,0x1C01); // CLKIN pin1281
				

	}while(retVal!=0);
	
  //	id=MPU_Read_2Byte(default_addr,LDC13xx16xx_CMD_DEVID);//鐠囨槒顔曟径鍢擠
//    if(id==0x3055||id==0x3054)
//	{   
//       return 1;
//	}
//    else 
//    { 
//      return 0;
//    }	
     return 1;
}


/***************************************
 * 閸戣姤鏆熼崥宥忕窗evm_processDRDY
 * 閹诲繗鍫�  閿涙俺顕伴崣鏍х槑鐎涙ê娅掗弫鐗堝祦
 * 鏉堟挸鍙�  閿涙碍妫�
 * 鏉堟挸鍤�  閿涙碍妫�
 **************************************/
void evm_processDRDY(unsigned long allData[4]) 
{
    u8 i=0;
    unsigned long reading = 0;
    float CAP_Data[4]; 
    float conver = 0;   //閺�?缂佸牏娈戞潪顒佸床閻ㄥ嫮绮ㄩ弸?
		
   for(i=0;i<=3;i++)
	{                                                         //0x0FFF  閺�?妤傛ê鍩岄崣?28娴�?
	  reading = ((unsigned long)(MPU_Read_2Byte(default_addr,i*2) & 0x0FFF) << 16);
          reading |= MPU_Read_2Byte(default_addr,(i*2)+1);
          //allData[i]=reading;
	  CAP_Data[i]=reading;
	  reading=0;
	}
	
//***濞夈劍鍓癐nit娑擃厼鎮囬柅姘朵壕鐎靛嫬鐡ㄩ崳?0x10-0x17閻ㄥ嫭妞傞柦鐔峰瀻妫�?***//
//*******娴犮儰绗呴崶娑欘劄鐠侊紕鐣婚弽瑙勫祦datasheet P19閸忣剙绱�*******//
   for(i=0;i<=3;i++)
    {   
	  CAP_Data[i] = (CAP_Data[i] * 40000000.0F)/268435456.0F;//瀵版鍩孎(sensorx)
	  CAP_Data[i] = CAP_Data[i] * 2.0F *3.1515926F;
	  CAP_Data[i] = 1.0F/((CAP_Data[i] * CAP_Data[i]) * 0.000018F);
	  CAP_Data[i] = CAP_Data[i] - 0.000000000033F;
	  CAP_Data[i] = CAP_Data[i] * 2000000000000000.0F;//F鏉烆剚宕瞤F;
         allData[i]=CAP_Data[i];
    }	
}

/***********************************/
/******FDC2214濡�?濞村鏁哥�圭懓?鑲┾柤鎼�?********/
/************************************/
double GetCapacitance(unsigned long value)
{
    double pi = 3.14159265359;
    double L = 18; //uH
    double Cboard = 33; //pf
    double Cparacitic = 3; //pf
    unsigned long long fsensor;
    double temp; 
	  
    fsensor = 1 * 40000000 * value;
    fsensor = fsensor / pow(2,28);

	temp = 2 * pi * fsensor;  
    temp = temp * temp;
		
    temp = temp / 1000000; //uH
    temp *= L;
    return temp;
}



