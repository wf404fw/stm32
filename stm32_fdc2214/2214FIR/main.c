#include <msp430.h>
#include "oled.h"
#include "uart.h"
#include "string.h"
#include "fdc2214.h"
#include "iic.h"
#include "xiaoche.h"
#include <math.h>

/*#define CC0 1000
#define CC12 1000
#define CC13 2800
#define CC2 200
#define CC3 300

#define DD0 1000
#define DD11 500
#define DD12 1500
#define DD13 2800
#define DD2 200
#define DD3 700 */

int CC0= 300 ;
int CC12= 1000;
int CC13 =1550;
int CC2 =100;
int CC3 =200;

int DD0= 300;
int DD11= 500;
int DD12= 1000;
int DD13= 1400;
int DD2= 100;
int DD3= 200;

int flagR=0,flagS=0,flagP=0,flag1=0,flag2=0,flag3=0,flag4=0,flag5=0,flagk0=0,flagk1=0,flagk2=0,flagk3=0,flagk4=0,flagk5=0;
int k=0,d;
long tt,T0,T1,T2,T3,T4;
long GG0,GG2;
long X0,X1,X2,X3,Y0,Y1,Y2,Y3,M0,M1,M2,M3,N0,N1,N2,N3,t,K00,K01,K02,K03,K10,K11,K12,K13,K20,K21,K22,K23,K30,K31,K32,K33,K40,K41,K42,K43,K50,K51,K52,K53;
int i, Buffer1[4];
long R0,R1,R2,R3,S0,S1,S2,S3,P0,P1,P2,P3,H10,H11,H12,H13,H20,H21,H22,H23,H30,H31,H32,H33,H40,H41,H42,H43,H50,H51,H52,H53;//石头
unsigned long PDR,PDS,PDP,PD1,PD2,PD3,PD4,PD5,PDflag;

    void Mode_1();//显示+改手心
    void Mode_2();//学习0
    void Mode_3();//学习1
    void Mode_4();//学习2
    void Mode_5();//学习3
    void Mode_6();//学习4
    void Mode_7();//学习5
    void Mode_8();//显示+改手心
    void Mode_9();//题目一判断
    void Mode_10();//显示+改手心
    void Mode_11();//题目二判断
    void Mode_12();//显示
    void Mode_13();//学习拳头
    void Mode_14();//学习剪刀
    void Mode_15();//学习布
    void Mode_16();//题目三判断
    void Mode_17();//显示
    void Mode_18();//学习1
    void Mode_19();//学习2
    void Mode_20();//学习3
    void Mode_21();//学习4
    void Mode_22();//学习5
    void Mode_23();//题目四判断


    unsigned char Is_sw_pressed1(unsigned char key_bit);
    unsigned char Is_sw_pressed2(unsigned char key_bit);
    unsigned char Is_sw_pressed3(unsigned char key_bit);
    unsigned char Is_sw_pressed4(unsigned char key_bit);
    unsigned char Is_sw_pressed5(unsigned char key_bit);
    unsigned char Is_sw_pressed6(unsigned char key_bit);
    unsigned char Is_sw_pressed7(unsigned char key_bit);




long Buffer[4]={0};
void delay(unsigned int x){
    unsigned int i,j;
    for(i=0;i<x;i++){
        for(j=0;j<x;j++);
    }
}
void IO_Init(void){
    P2DIR |= BIT7 + BIT6;//OLED

  //  P6DIR |= BIT0 + BIT1 + BIT2 + BIT3; //灏忚溅寮曡剼璁句负杈撳嚭
}

/*void Pwm_Init(void){
    P2DIR |= BIT4+BIT5;
    P2SEL |= BIT4+BIT5;
    TA2CCR0 = 128;
    TA2CCTL1 = OUTMOD_6;
    TA2CCR1 = 96;
    TA2CCTL2 = OUTMOD_6;
    TA2CCR2 = 96;
    TA2CTL = TASSEL_2 + MC_3 + TACLR;
}*/
void Clock_Init(void){
    unsigned int i;
    P1DIR |= BIT0;                            // ACLK set out to pins
    P1SEL |= BIT0;
    P2DIR |= BIT2;                            // SMCLK set out to pins
    P2SEL |= BIT2;
    P7DIR |= BIT7;                            // MCLK set out to pins
    P7SEL |= BIT7;

    P5SEL   |= BIT4+BIT5;       //P5.4鍜孭5.5閫夋嫨XT1鏅舵尟鍔熻兘
    UCSCTL3 |= SELREF_0;        //璁剧疆FLL鍙傝�冩椂閽熸簮涓篨T1
    UCSCTL4 |= SELA_0;          //ACLK = XT1CLK
    UCSCTL0 = 0;                //璁剧疆DCO=MOD=0
    do
    {
      UCSCTL7 &= ~(XT2OFFG + XT1LFOFFG + DCOFFG);
                               //娓呴櫎XT2,XT1,DCO鏁呴殰澶辨晥鏍囧織浣�
      SFRIFG1 &= ~OFIFG;       //娓呴櫎鏅舵尟鏁呴殰澶辨晥涓柇鏍囧織浣�
    }while(SFRIFG1&OFIFG);      //鏅舵尟鏁呴殰澶辨晥涓柇鏍囧織浣�
    UCSCTL6 &= ~XT1DRIVE_0;     //鍑忓皯XT1椹卞姩鑳藉姏
    __bis_SR_register(SCG0);    //绂佹FLL
    UCSCTL1 = DCORSEL_4;        //閫夋嫨DCO棰戠巼鑼冨洿
    UCSCTL2 |= 499;             //璁剧疆棰戠巼16Mhz
    __bic_SR_register(SCG0);    //鍚敤FLL
    for(i = 50000;i>0;i--);     //delay锛岀瓑寰匜LL绋冲畾
}



void mode_xuanze(int j) //根据题目选择函数
        {
            if(j==1) Mode_1();
            if(j==2) Mode_2();
            if(j==3) Mode_3();
            if(j==4) Mode_4();
            if(j==5) Mode_5();
            if(j==6) Mode_6();
            if(j==7) Mode_7();//标准
              if(j==8) Mode_8();//第一题
              if(j==9) Mode_9();//标准
              if(j==10) Mode_10();//第二题
              if(j==11) Mode_11();//标准
              if(j==12) Mode_12();//学习石头
              if(j==13) Mode_13();//学习剪刀
              if(j==14) Mode_14();//学习布
              if(j==15) Mode_15();//第三题
              if(j==16) Mode_16();//标准
              if(j==17) Mode_17();//学习1
              if(j==18) Mode_18();//学习2
              if(j==19) Mode_19();//学习3
              if(j==20) Mode_20();//学习4
             if(j==21) Mode_21();//学习5
              if(j==22) Mode_22();//第四题
              if(j==23) Mode_23();
              if(j>23)  Mode_1();

        }
/**
 * main.c
 */
void main(void)
{
    char retVal=0;
    unsigned int id = 0;
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer
	Clock_Init();
	//Pwm_Init();
	IO_Init();
	UART_RS232_Init();
	OLED_Init();
	OLED_Clear();
	IIC_Init();
	_EINT();                        //寮�涓柇
	 OLED_ShowString(0,0,"  FDC2214_Demo  ",16);

	P2DIR &= ~(BIT1);  //P2.1璁剧疆涓鸿緭鍏�
	P2REN |= BIT1;
	P2OUT |= BIT1;

	P1DIR &= ~(BIT1);  //P2.1璁剧疆涓鸿緭鍏�
    P1REN |= BIT1;
    P1OUT |= BIT1;

    P6DIR &= ~(BIT0+BIT1+BIT2+BIT3);  //P2.1璁剧疆涓鸿緭鍏�
    P6REN |= BIT0+BIT1+BIT2+BIT3;
    P6OUT |= BIT0+BIT1+BIT2+BIT3;

     P2DIR &= ~(BIT4);  //P2.1璁剧疆涓鸿緭鍏�
     P2REN |= BIT4;
     P2OUT |= BIT4;


	 do
	   {
        retVal = 0;
        retVal = FDC2214_init();  //鍒濆鍖朏DC2214
        if(retVal==1)OLED_ShowString(2,2," Init Success ",16);
        if(retVal==0)OLED_ShowString(2,2," Init defeated ",16);
        }while (retVal!=1);

    id=MPU_Read_2Byte(0x2A,LDC13xx16xx_CMD_DEVID);//璇昏澶嘔D
    OLED_ShowString(0,4,"FDC_ID:",16);
    OLED_ShowNum(72,4,id,5,16);//鏄剧ずASCII瀛楃鐨勭爜鍊�
    delay_ms(2000);
    OLED_Clear();
    OLED_ShowString(0,0,"CH0:         pf",16);
    OLED_ShowString(0,2,"CH1:         pf",16);
   OLED_ShowString(0,4,"CH2:         pf",16);
   OLED_ShowString(0,6,"CH3:         pf",16);

	  __no_operation();
	  while(1)
   {

	      if((USART_RX_STA&0x8000)==0x8000)
	      {
	        //OLED_Clear();
	        OLED_ShowString(20,0,USART_RX_BUF,16);
	        USART_RX_STA=0;
	        memset(USART_RX_BUF,'\0',sizeof(USART_RX_BUF));//娓呴櫎鎺ュ彈瀛楃涓叉暟缁�
	      }else
	      {
	          evm_processDRDY(Buffer);//璇诲彇鐢靛鍊肩數瀹圭殑鍊�
	          if(Is_sw_pressed2(1)==1)
	          {
	              d++;
	              if(d>23) d=0;

	              OLED_Clear();
	           }//按键循环检测
	          mode_xuanze(d); //根据题目选择函数，每次模式转换的时候都会清屏
	         if(d==0)
	             {
	                 OLED_ShowNum(32,0,Buffer[0],9,16);//鏄剧ず鐢靛鐨勫��
	                 OLED_ShowNum(32,2,Buffer[1],9,16);//鏄剧ず鐢靛鐨勫��
	                 OLED_ShowNum(32,4,Buffer[2],9,16);//鏄剧ず鐢靛鐨勫��
	                 OLED_ShowNum(32,6,Buffer[3],9,16);//鏄剧ず鐢靛鐨勫��
	             }
	         if(d==1)
	         {
	             if(Is_sw_pressed1(1)==1)
	                 {
	                     CC3=CC3+50;DD3=DD3+50;
	                     if(CC3>350) CC3=100;
	                     if(DD3>350) DD3=100;
	                 }
	         }
	         if(d==8)
	         {
	             if(Is_sw_pressed1(1)==1)
	                  {
	                      CC3=CC3+50;DD3=DD3+50;
	                      if(CC3>350) CC3=100;
	                      if(DD3>350) DD3=100;
	                  }
	         }
	         if(d==10)
	                      {
	                          if(Is_sw_pressed1(1)==1)
	                               {
	                                   CC3=CC3+50;DD3=DD3+50;
	                                   if(CC3>350) CC3=100;
	                                   if(DD3>350) DD3=100;
	                               }
	                      }
/*	         if(d==2)//读取模式一的时候观察屏幕，得到变化大小，以便是否要按按键，来改变原来设定的宏定义的值
	       {

	             if(Is_sw_pressed2(1)==1)
	            {

	                CC0+=100; //cc0默认是1000
	               if(CC0==1500)
	                CC0=500;


	            }
	            if(Is_sw_pressed3(1)==1) //cc12默认是1000
	             {
OLED_ShowString(0,4,"CHOOSE MODE2",16);
	              CC12+=100;
	              if(CC12==1500)
	              CC12=500;


	             }
	            if(Is_sw_pressed4(1)==1)
	                             {
	                OLED_ShowString(0,4,"CHOOSE MODE2",16);
	                              CC13+=200;   //默认是2800
	                              if(CC13==3400)
	                              CC13=2200;


	                             }
	            if(Is_sw_pressed5(1)==1)
	            {OLED_ShowString(0,4,"CHOOSE MODE2",16);


	                             }
	            if(Is_sw_pressed6(1)==1)
	                             {
	                OLED_ShowString(0,4,"CHOOSE MODE2",16);
	                              CC2+=50;//默认是200
	                              if(CC2==450)
	                              CC2=50;

	                              CC3+=50;//默认是300
	                              if(CC3==550)
	                              CC3=100;


	                             }

	      }
	        if(d==4)
	     {

	            if(Is_sw_pressed2(1)==1)
	        {
	            DD0+=100;  //默认是1000
	           if(DD0==1500)

	           DD0=500;

	         }
	            if(Is_sw_pressed3(1)==1)
	                      {
	                          DD11+=50;//默认是500
	                         if(DD11==750)

	                         DD11=250;

	                       }
	            if(Is_sw_pressed4(1)==1)
	                      {
	                          DD12+=100;//默认是1500
	                         if(DD12==2000)

	                         DD12=1000;

	                       }
	            if(Is_sw_pressed5(1)==1)
	                      {
	                          DD13+=100;//默认是2800
	                         if(DD13==3200)

	                         DD13=2300;

	                       }
	            if(Is_sw_pressed6(1)==1)
	                      {
	                          DD2+=50; //默认是200
	                         if(DD2==450)

	                         DD2=50;

	                       }
	            if(Is_sw_pressed7(1)==1)
	                      {
	                          DD3+=50; //默认是700
	                         if(DD3==950)

	                         DD3=450;

	                       }


	    }*/
	  }
   }
}
/**
 * 涓插彛1涓柇鏂规硶x`
 */
#pragma vector=USCI_A1_VECTOR                                       //USCI涓柇鏈嶅姟鍑芥暟
__interrupt void USCI_A1_ISR(void){
    switch(__even_in_range(UCA1IV,4)){
        case 0:break;                                                   //鏃犱腑鏂�
        case 2:{
            data = UCA1RXBUF;
            Send_Byte(data);
            if((USART_RX_STA&0x8000)==0){        //鎺ユ敹鏈畬鎴�
               if(USART_RX_STA&0x4000){           //鎺ユ敹鍒颁簡0x0d
                 if(data!=0x0a)USART_RX_STA=0;//鎺ユ敹閿欒,閲嶆柊寮�濮�
                 else{
                   USART_RX_STA|=0x8000;   //鎺ユ敹瀹屾垚浜�
                 }
               }
               else{                              //杩樻病鏀跺埌0X0D
                 if(data==0x0d)USART_RX_STA|=0x4000;
                 else{
                     USART_RX_BUF[USART_RX_STA&0X3FFF]=data ;
                     USART_RX_STA++;
                     if(USART_RX_STA>(USART_REC_LEN-1))USART_RX_STA=0;//鎺ユ敹鏁版嵁閿欒,閲嶆柊寮�濮嬫帴鏀�
                     }
                 }
              }
           }
            break;
        case 4:break;                                                   //鍙戦�佷腑鏂笉澶勭悊
        default:break;                                                  //鍏朵粬鎯呭喌鏃犳搷浣�
    }
}


unsigned char Is_sw_pressed1(unsigned char key_bit)
{
    if ((P2IN & (1<<key_bit)) == 0) {   //有键被按下?
        delay_ms(20);   //是的。等待20mS去抖动
        if ((P2IN & (1<<key_bit)) == 0) {   //按键一直被按着？
            while ((P2IN & (1<<key_bit)) == 0); //是的，等待按键释放
            delay_ms(20);   //当按键释放时，等待20mS去抖动
                    if  ((P2IN & (1<<key_bit)) != 0) {  //如果按键确实被释放
                        return 1;   //则认为此次按键操作合法
                    }
                }
            }
            return 0;   //否则认为是非法操作
 }



unsigned char Is_sw_pressed2(unsigned char key_bit)
{
    if ((P1IN & (1<<key_bit)) == 0) {   //有键被按下?
        delay_ms(20);   //是的。等待20mS去抖动
        if ((P1IN & (1<<key_bit)) == 0) {   //按键一直被按着？
            while ((P1IN & (1<<key_bit)) == 0); //是的，等待按键释放
            delay_ms(20);   //当按键释放时，等待20mS去抖动
                    if  ((P1IN & (1<<key_bit)) != 0) {  //如果按键确实被释放
                        return 1;   //则认为此次按键操作合法
                    }
                }
            }
            return 0;   //否则认为是非法操作
 }

unsigned char Is_sw_pressed3(unsigned char key_bit)
{
    if ((P6IN & (0<<key_bit)) == 0) {   //有键被按下?
        delay_ms(20);   //是的。等待20mS去抖动
        if ((P6IN & (0<<key_bit)) == 0) {   //按键一直被按着？
            while ((P6IN & (0<<key_bit)) == 0); //是的，等待按键释放
            delay_ms(20);   //当按键释放时，等待20mS去抖动
                    if  ((P6IN & (0<<key_bit)) != 0) {  //如果按键确实被释放
                        return 1;   //则认为此次按键操作合法
                    }
                }
            }
            return 0;   //否则认为是非法操作
 }

unsigned char Is_sw_pressed4(unsigned char key_bit)
{
    if ((P6IN & (1<<key_bit)) == 0) {   //有键被按下?
        delay_ms(20);   //是的。等待20mS去抖动
        if ((P6IN & (1<<key_bit)) == 0) {   //按键一直被按着？
            while ((P6IN & (1<<key_bit)) == 0); //是的，等待按键释放
            delay_ms(20);   //当按键释放时，等待20mS去抖动
                    if  ((P2IN & (1<<key_bit)) != 0) {  //如果按键确实被释放
                        return 1;   //则认为此次按键操作合法
                    }
                }
            }
            return 0;   //否则认为是非法操作
 }

unsigned char Is_sw_pressed5(unsigned char key_bit)
{
    if ((P6IN & (2<<key_bit)) == 0) {   //有键被按下?
        delay_ms(20);   //是的。等待20mS去抖动
        if ((P6IN & (2<<key_bit)) == 0) {   //按键一直被按着？
            while ((P6IN & (2<<key_bit)) == 0); //是的，等待按键释放
            delay_ms(20);   //当按键释放时，等待20mS去抖动
                    if  ((P6IN & (2<<key_bit)) != 0) {  //如果按键确实被释放
                        return 1;   //则认为此次按键操作合法
                    }
                }
            }
            return 0;   //否则认为是非法操作
 }

unsigned char Is_sw_pressed6(unsigned char key_bit)
{
    if ((P6IN & (3<<key_bit)) == 0) {   //有键被按下?
        delay_ms(20);   //是的。等待20mS去抖动
        if ((P6IN & (3<<key_bit)) == 0) {   //按键一直被按着？
            while ((P6IN & (3<<key_bit)) == 0); //是的，等待按键释放
            delay_ms(20);   //当按键释放时，等待20mS去抖动
                    if  ((P6IN & (3<<key_bit)) != 0) {  //如果按键确实被释放
                        return 1;   //则认为此次按键操作合法
                    }
                }
            }
            return 0;   //否则认为是非法操作
 }

unsigned char Is_sw_pressed7(unsigned char key_bit)
{
    if ((P2IN & (4<<key_bit)) == 0) {   //有键被按下?
        delay_ms(20);   //是的。等待20mS去抖动
        if ((P2IN & (4<<key_bit)) == 0) {   //按键一直被按着？
            while ((P2IN & (4<<key_bit)) == 0); //是的，等待按键释放
            delay_ms(20);   //当按键释放时，等待20mS去抖动
                    if  ((P2IN & (4<<key_bit)) != 0) {  //如果按键确实被释放
                        return 1;   //则认为此次按键操作合法
                    }
                }
            }
            return 0;   //否则认为是非法操作
 }

void Mode_1(void)//显示+改手心
{
    evm_processDRDY(Buffer);//读取电容值电容的值
    delay_ms(20);X0=Buffer[0];T0=X0;
    delay_ms(20);X1=Buffer[1];T1=X1;
    delay_ms(20);X2=Buffer[2];T2=X2;
    delay_ms(20);X3=Buffer[3];T3=X3;
        OLED_ShowNum(32,0,X0,9,16);//鏄剧ず鐢靛鐨勫��
        OLED_ShowNum(32,2,X1,9,16);//鏄剧ず鐢靛鐨勫��
        OLED_ShowNum(32,4,X2,9,16);//鏄剧ず鐢靛鐨勫��
        OLED_ShowNum(32,6,X3,9,16);//鏄剧ず鐢靛鐨勫��

}

void Mode_2(void) // xue 0
{
    OLED_ShowString(0,0,"show 0",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flagk0<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        K00= Buffer1[0];
        K01= Buffer1[1];
        K02= Buffer1[2];
        K03= Buffer1[3];
        flagk0++;
    }
    if(flagk0>0&&flagk0<4) OLED_ShowString(0,0,"zero already",16);

    delay_ms(500);
    OLED_Clear();
}

void Mode_3(void) // xue 1
{
    OLED_ShowString(0,0,"show 1",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flagk1<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        K10= Buffer1[0];
        K11= Buffer1[1];
        K12= Buffer1[2];
        K13= Buffer1[3];
        flagk1++;
    }
    if(flagk1>0&&flagk1<4) OLED_ShowString(0,0,"one already",16);

    delay_ms(500);
    OLED_Clear();
}

void Mode_4(void)   //xue 2
{
    OLED_ShowString(0,0,"show 2",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flagk2<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        K20= Buffer1[0];
        K21= Buffer1[1];
        K22= Buffer1[2];
        K23= Buffer1[3];
        flagk2++;
     }
     if(flagk2>0&&flagk2<4) OLED_ShowString(0,0,"two already",16);

     delay_ms(500);
     OLED_Clear();
}

void Mode_5(void)// xue san
{
    OLED_ShowString(0,0,"show 3",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flagk3<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        K30= Buffer1[0];
        K31= Buffer1[1];
        K32= Buffer1[2];
        K33= Buffer1[3];
        flagk3++;
     }
     if(flagk3>0&&flagk3<4) OLED_ShowString(0,0,"three already",16);

     delay_ms(500);
     OLED_Clear();
}

void Mode_6(void)// xue 4
{
    OLED_ShowString(0,0,"show 4",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flagk4<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        K40= Buffer1[0];
        K41= Buffer1[1];
        K42= Buffer1[2];
        K43= Buffer1[3];
        flagk4++;
    }
    if(flagk4>0&&flagk4<4) OLED_ShowString(0,0,"four already",16);

    delay_ms(500);
    OLED_Clear();
}

void Mode_7(void) //xue 5
{
    OLED_ShowString(0,0,"show 5",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flagk5<1)     OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        K50= Buffer1[0];
        K51= Buffer1[1];
        K52= Buffer1[2];
        K53= Buffer1[3];
        flagk5++;
    }
    if(flagk5>0&&flagk5<4) OLED_ShowString(0,0,"five already",16);

    delay_ms(500);
    OLED_Clear();
}





void Mode_8(void)//读显示+改手心
{
    evm_processDRDY(Buffer);//读取电容值电容的值
    delay_ms(20);
    X0=Buffer[0];
    X1=Buffer[1];
    X2=Buffer[2];
    X3=Buffer[3];delay_ms(80);
    CC0 = abs(K50 - K20) - 70;
    CC12 = abs(K21 - K01) - 70;
    CC13 = abs(K31 - K01) + 70;
    CC2 = abs(K52 - K22)-50;
    OLED_ShowNum(32,0,CC0,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,2,CC12,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,4,CC13,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,6,CC2,9,16);//鏄剧ず鐢靛鐨勫��
}


void Mode_9(void)//判断第一题
{
    OLED_ShowString(0,0,"FIRST:",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(X3-Y3)<CC3) OLED_ShowString(0,2,"please start",16); //是没放上去之前显示
    if(abs(X3-Y3)>CC3) //手放上去
    {
        delay_ms(300);
        Y0= Buffer[0];
        Y1= Buffer[1];
        Y2= Buffer[2];
//        OLED_ShowNum(32,0,abs(X0-Y0),9,16);
//        OLED_ShowNum(32,2,abs(X1-Y1),9,16);
//        OLED_ShowNum(32,4,abs(X2-Y2),9,16);
//        OLED_ShowNum(32,6,abs(X3-Y3),9,16);


        if((abs(X0-Y0)>CC0)&&(abs(X2-Y2)>CC2))
         {   OLED_ShowString(0,4,"paper",16); //0.1.2改变
            delay_ms(500);
            OLED_Clear();
         }
        if(abs(X1-Y1)>CC12&&abs(X1-Y1)<CC13&&abs(X2-Y2)<CC2)
        {  OLED_ShowString(0,4,"scissor",16);//1变为剪刀
           delay_ms(500);
           OLED_Clear();
        }
        if(abs(X0-Y0)<CC0&&abs(X1-Y1)<CC12&&abs(X2-Y2)<CC2 ) //0.1.2不变化为石头
        {  OLED_ShowString(0,4,"rock",16);
            delay_ms(500);
            OLED_Clear();
        }

    }
}

void Mode_10(void)//显示+改手心
{
    evm_processDRDY(Buffer);//读取电容值电容的值,手放上去之前的初始值
    delay_ms(20);
    M0=Buffer[0];
    M1=Buffer[1];
    M2=Buffer[2];
    M3=Buffer[3];
    delay_ms(80);
    OLED_ShowNum(32,0,M0,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,2,M1,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,4,M2,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,6,M3,9,16);//鏄剧ず鐢靛鐨勫��
    DD0 = abs(K50 - K20)-70;
    DD11 = abs(K11 - K01) - 70;
    DD12 = abs(K21 - K01) - 40;
    DD13 = abs(K31 - K01) + 70;
    DD2 = abs(K52 - K22)-50;
}

/*
void Mode_10(void)//判断第二题
{
    OLED_ShowString(0,0,"SECOND:",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    N3= Buffer[3];
    if(abs(M3-N3)<CC3) OLED_ShowString(0,2,"please start",16); //是没放上去之前显示
    if(abs(M3-N3)>CC3) //手放上去
    {
        delay_ms(300);
        N0= Buffer[0];
        N1= Buffer[1];
        N2= Buffer[2];
*/
/*      PD1 = abs(K10-N0)+abs(K11-N1)+abs(K12-N2);
        PD2 = abs(K20-N0)+abs(K21-N1)+abs(K22-N2);
        PD3 = (abs(K30-N0)+abs(K31-N1)+abs(K32-N2))-10;
        PD4 = (abs(K40-N0)+abs(K41-N1)+abs(K42-N2))-15;
        PD5 = abs(K50-N0)+abs(K51-N1)+abs(K52-N2);
        if(PD3>2000) PD3=0;
        if(PD4>2000) PD4=0;
*/
/*
            PDflag=PD1;
            if(PDflag>PD2) PDflag=PD2;
            if(PDflag>PD3) PDflag=PD3;
            if(PDflag>PD4) PDflag=PD4;
            if(PDflag>PD5) PDflag=PD5;

        if (PD1==PDflag)
        {
            OLED_ShowString(0,4,"one",16);
            OLED_ShowNum(0,6,PDflag,9,16);
                        delay_ms(500);
                        OLED_Clear();
        }
        if (PD2==PDflag)
        {
            OLED_ShowString(0,4,"two",16);
            OLED_ShowNum(0,6,PDflag,9,16);
            delay_ms(500);
            OLED_Clear();
        }
        if (PD3==PDflag)
        {
            OLED_ShowString(0,4,"three",16);
            OLED_ShowNum(0,6,PDflag,9,16);
            delay_ms(500);
            OLED_Clear();
        }
        if (PD4==PDflag)
                {
                    OLED_ShowString(0,4,"four",16);
                    OLED_ShowNum(0,6,PDflag,9,16);
                    delay_ms(500);
                    OLED_Clear();
                }
        if (PD5==PDflag)
                {
                    OLED_ShowString(0,4,"five",16);
                    OLED_ShowNum(0,6,PDflag,9,16);
                    delay_ms(500);
                    OLED_Clear();
                }
*/
/*
        OLED_ShowNum(32,6,PD2,9,16);
        OLED_ShowNum(32,2,PD3,9,16);
        OLED_ShowNum(32,4,PD4,9,16);
       OLED_ShowNum(32,6,PD5,9,16);
    }
}*/

void Mode_11(void)//  12345 判定
{
    OLED_ShowString(0,0,"SECOND:",16);
    evm_processDRDY(Buffer);//读取电容值电容的值


            N3= Buffer[3];
            if(abs(M3-N3)<CC3)     OLED_ShowString(0,2,"please start",16); //如果手没有放上去

            if(abs(M3-N3)>CC3) //手放上去
                {
                    delay_ms(300);
                    N0= Buffer[0];
                    N1= Buffer[1];
                    N2= Buffer[2];
/*
                    PD1 = abs(M0-N0)+abs(M1-N1)+2*abs(M2-N2);
                    PD1 = (int) PD1*1.5;
                    OLED_ShowNum(0,6,PD1,9,16);
                    if(PD1>1300&&PD1<1600) OLED_ShowNum(0,4,1,9,16);
                    if(PD1>1900&&PD1<2200) OLED_ShowNum(0,4,2,9,16);
                    if(PD1>2300&&PD1<2600) OLED_ShowNum(0,4,3,9,16);
                    if(PD1>2700&&PD1<3000) OLED_ShowNum(0,4,4,9,16);
                    if(PD1>3100) OLED_ShowNum(0,4,5,9,16);
                    delay_ms(500);
                    OLED_Clear();
*/


//                   OLED_ShowNum(0,0,abs(M0-N0),9,16);
//                   OLED_ShowNum(0,2,abs(M1-N1),9,16);
//                   OLED_ShowNum(0,4,abs(M2-N2),9,16);
//                   OLED_ShowNum(0,6,abs(M3-N3),9,16);


                    if(abs(M0-N0)<DD0&&abs(M2-N2)<DD2) //通道0和2差值不变 表示在做123的判定
                      {
                         if(abs(M1-N1)>DD11&&abs(M1-N1)<DD12)
                         {
                             OLED_ShowNum(0,4,1,9,16);//显示数字1
                             delay_ms(500);
                             OLED_Clear();
                         }
                             if(abs(M1-N1)>DD12&&abs(M1-N1)<DD13)
                          {
                             OLED_ShowNum(0,4,2,9,16);//显示数字2
                             delay_ms(500);
                             OLED_Clear();

                          }
                             if(abs(M1-N1)>DD13)
                          {
                             OLED_ShowNum(0,4,3,9,16);//显示数字3
                            delay_ms(500);
                              OLED_Clear();

                          }


                      }

                    /* if(abs(M2-N2)>DD2&&abs(M1-N1)>DD11)
                     {
                          OLED_ShowNum(0,4,3,9,16);//显示数字3
                          delay_ms(500);
                          OLED_Clear();

                     }*/

                      if(abs(M0-N0)<DD0&&abs(M2-N2)>DD2)//通道0没有变化，通道2有变化
                     {

                          OLED_ShowNum(0,4,4,9,16);//显示数字4
                          delay_ms(500);
                         OLED_Clear();
                     }
                     if(abs(M0-N0)>DD0&&abs(M2-N2)>DD2)
                     {
                         OLED_ShowNum(0,4,5,9,16);//显示数字5
                         delay_ms(500);
                         OLED_Clear();
                     }

                }
}

void Mode_12(void)//显示+改手心
{
    evm_processDRDY(Buffer);//读取电容值电容的值
    delay_ms(20);X0=Buffer[0];
    delay_ms(20);X1=Buffer[1];
    delay_ms(20);X2=Buffer[2];
    delay_ms(20);X3=Buffer[3];
    OLED_ShowNum(32,0,X0,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,2,X1,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,4,X2,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,6,X3,9,16);//鏄剧ず鐢靛鐨勫��
}


void Mode_13(void)//  进入训练模式R
{
    OLED_ShowString(0,0,"show rock",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flagR<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        R0= Buffer1[0];
        R1= Buffer1[1];
        R2= Buffer1[2];
        R3= Buffer1[3];
        flagR++;
    }
    if(flagR>0&&flagR<4) OLED_ShowString(0,0,"rock already",16);

    delay_ms(500);
    OLED_Clear();
}

void Mode_14(void)//  进入训练模式S
{
    OLED_ShowString(0,0,"show scissor",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flagS<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        S0= Buffer1[0];
        S1= Buffer1[1];
        S2= Buffer1[2];
        S3= Buffer1[3];
        flagS++;
    }
    if(flagS>0&&flagS<4) OLED_ShowString(0,0,"scissor already",16);

    delay_ms(500);
    OLED_Clear();
}
void Mode_15(void)//  进入训练模式P
{
    OLED_ShowString(0,0,"show paper",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flagP<1)     OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        P0= Buffer1[0];
        P1= Buffer1[1];
        P2= Buffer1[2];
        P3= Buffer1[3];
        flagP++;
    }
    if(flagP>0&&flagP<4) OLED_ShowString(0,0,"paper already",16);
    delay_ms(500);
    OLED_Clear();
}

void Mode_16(void)//判断第三题
{
    OLED_ShowString(0,0,"THIRD:",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(X3-Y3)<CC3) OLED_ShowString(0,2,"please start",16); //是没放上去之前显示
    if(abs(X3-Y3)>CC3) //手放上去
    {
        delay_ms(300);
        Y0= Buffer[0];
        Y1= Buffer[1];
        Y2= Buffer[2];
        PDR = abs(R0-Y0)+abs(R1-Y1)+abs(R2-Y2);
        PDS = abs(S0-Y0)+abs(S1-Y1)+abs(S2-Y2);
        PDP = abs(P0-Y0)+abs(P1-Y1)+abs(P2-Y2);

        if (PDR<PDS&&PDR<PDP)
        {
            OLED_ShowString(0,4,"rock",16);
                        delay_ms(500);
                        OLED_Clear();
        }
        if (PDS<PDR&&PDS<PDP)
        {
            OLED_ShowString(0,4,"scissor",16);
            delay_ms(500);
            OLED_Clear();
        }
        if (PDS<PDR&&PDP<PDS)
        {
            OLED_ShowString(0,4,"paper",16);
            delay_ms(500);
            OLED_Clear();
        }

//        OLED_ShowNum(32,0,PDR,9,16);
//        OLED_ShowNum(32,2,PDS,9,16);
//        OLED_ShowNum(32,4,PDP,9,16);
       /*delay_ms(500);
        if(abs(X0-Y0)<CC0&&abs(X1-Y1)<CC1&&abs(X2-Y2)<CC2 ) //0.1.2不变化为石头
        {  OLED_ShowString(0,4,"rock",16);
            delay_ms(500);
            OLED_Clear();
        }
        if(abs(X1-Y1)>CC1&&abs(X0-Y0)<CC0)
        {  OLED_ShowString(0,4,"scissor",16);//1变为剪刀
           delay_ms(500);
           OLED_Clear();
        }
         if(abs(X0-Y0)>CC0)
         {   OLED_ShowString(0,4,"paper",16); //0.1.2改变
            delay_ms(500);
            OLED_Clear();
         }
         //else
         //   { OLED_ShowString(0,4,"error",16); // 显示错误
         //     delay_ms(1000);
         //     OLED_Clear();
          //  }*/

    }
}


void Mode_17(void) //显示+改手心
{
    evm_processDRDY(Buffer);//读取电容值电容的值
    delay_ms(20);X0=Buffer[0];
    delay_ms(20);X1=Buffer[1];
    delay_ms(20);X2=Buffer[2];
    delay_ms(20);X3=Buffer[3];
    OLED_ShowNum(32,0,X0,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,2,X1,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,4,X2,9,16);//鏄剧ず鐢靛鐨勫��
    OLED_ShowNum(32,6,X3,9,16);//鏄剧ず鐢靛鐨勫��
}

void Mode_18(void) // xue 1
{
    OLED_ShowString(0,0,"show 1",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flag1<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        H10= Buffer1[0];
        H11= Buffer1[1];
        H12= Buffer1[2];
        H13= Buffer1[3];
        flag1++;
     }
    if(flag1>0&&flag1<4) OLED_ShowString(0,0,"one already",16);
    OLED_ShowNum(32,4,H10,9,16);
    OLED_ShowNum(32,6,H12,9,16);
    //OLED_ShowNum(32,6,H11,9,16);
     delay_ms(500);
     OLED_Clear();
}

void Mode_19(void)   //xue 2
{
    OLED_ShowString(0,0,"show 2",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flag2<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        H20= Buffer1[0];
        H21= Buffer1[1];
        H22= Buffer1[2];
        H23= Buffer1[3];
        flag2++;
    }
    if(flag2>0&&flag2<4) OLED_ShowString(0,0,"two already",16);
    OLED_ShowNum(32,6,H21,9,16);
    delay_ms(500);
    OLED_Clear();
}

void Mode_20(void)// xue san
{
    OLED_ShowString(0,0,"show 3",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flag3<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        H30= Buffer1[0];
        H31= Buffer1[1];
        H32= Buffer1[2];
        H33= Buffer1[3];
        flag3++;
     }
     if(flag3>0&&flag3<4) OLED_ShowString(0,0,"three already",16);
    OLED_ShowNum(32,6,H31,9,16);
     delay_ms(500);
     OLED_Clear();
}

void Mode_21(void)// xue 4
{
    OLED_ShowString(0,0,"show 4",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flag4<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        H40= Buffer1[0];
        H41= Buffer1[1];
        H42= Buffer1[2];
        H43= Buffer1[3];
        flag4++;
    }
    if(flag4>0&&flag4<4) OLED_ShowString(0,0,"four already",16);

    delay_ms(500);
    OLED_Clear();
}

void Mode_22(void) //xue 5
{
    OLED_ShowString(0,0,"show 5",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(Y3-X3)<CC3&&flag5<1) OLED_ShowString(0,2,"please start",16); //如果手没有放上去
    if(abs(Y3-X3)>CC3) //手放上去
    {
        for(i=0;i<4;i++)
        Buffer1[i]=Buffer[i];
        H50= Buffer1[0];
        H51= Buffer1[1];
        H52= Buffer1[2];
        H53= Buffer1[3];
        flag5++;
    }
    if(flag5>0&&flag5<4) OLED_ShowString(0,0,"five already",16);
    OLED_ShowNum(32,4,H50,9,16);
    OLED_ShowNum(32,6,H52,9,16);
    delay_ms(500);
    OLED_Clear();
}

void Mode_23(void)//判断第四题
{
    OLED_ShowString(0,0,"FORTH:",16);
    evm_processDRDY(Buffer);//读取电容值电容的值
    Y3= Buffer[3];
    if(abs(X3-Y3)<CC3) OLED_ShowString(0,2,"please start",16); //是没放上去之前显示
    if(abs(X3-Y3)>CC3) //手放上去
    {
        delay_ms(300);
        Y0= Buffer[0];
        Y1= Buffer[1];
        Y2= Buffer[2];
        PD1 = abs(H11-Y1);
        PD2 = abs(H21-Y1);
        PD3 = abs(H31-Y1);
        GG0=abs(H50-H10);GG2=abs(H52-H12);
        //OLED_ShowNum(0,2,GG0,9,16);
        //OLED_ShowNum(0,4,GG2,9,16);
        PDflag=PD1;
        if(PDflag>PD2) PDflag=PD2;
        if(PDflag>PD3) PDflag=PD3;

        if(abs(X0-Y0)<GG0&&abs(X2-Y2)<GG2) //通道0和2差值不变 表示在做123的判定
        {
            if (PD1==PDflag)
            {
                                OLED_ShowString(0,4,"one",16);
                                //OLED_ShowNum(0,6,PDflag,9,16);
                                            delay_ms(500);
                                            OLED_Clear();
            }
            if (PD2==PDflag)
            {
                                OLED_ShowString(0,4,"two",16);
                                //OLED_ShowNum(0,6,PDflag,9,16);
                                delay_ms(500);
                                OLED_Clear();
            }
            if (PD3==PDflag)
            {
                                OLED_ShowString(0,4,"three",16);
                                //OLED_ShowNum(0,6,PDflag,9,16);
                                delay_ms(500);
                                OLED_Clear();
            }
        }
        if(abs(X0-Y0)<GG0&&abs(X2-Y2)>GG2)//通道0没有变化，通道2有变化
        {
            OLED_ShowString(0,4,"four",16);//显示数字4
            delay_ms(500);
            OLED_Clear();
        }
        if(abs(X0-Y0)>GG0&&abs(X2-Y2)>GG2)
        {
            OLED_ShowString(0,4,"five",16);;//显示数字5
            delay_ms(500);
            OLED_Clear();
        }

/*
        PD1 = abs(H10-Y0)+abs(H11-Y1)+abs(H12-Y2)+abs(H12-Y2);
        PD2 = abs(H20-Y0)+abs(H21-Y1)+abs(H22-Y2)+abs(H22-Y2);
        PD3 = abs(H30-Y0)+abs(H31-Y1)+abs(H32-Y2)+abs(H32-Y2);
        PD4 = abs(H40-Y0)+abs(H41-Y1)+abs(H42-Y2)+abs(H42-Y2);
        PD5 = abs(H50-Y0)+abs(H51-Y1)+abs(H52-Y2)+abs(H42-Y2);

            PDflag=PD1;
            if(PDflag>PD2) PDflag=PD2;
            if(PDflag>PD3) PDflag=PD3;
            if(PDflag>PD4) PDflag=PD4;
            if(PDflag>PD5) PDflag=PD5;

        if (PD1==PDflag)
        {
            OLED_ShowString(0,4,"one",16);
            OLED_ShowNum(0,6,PDflag,9,16);
                        delay_ms(500);
                        OLED_Clear();
        }
        if (PD2==PDflag)
        {
            OLED_ShowString(0,4,"two",16);
            OLED_ShowNum(0,6,PDflag,9,16);
            delay_ms(500);
            OLED_Clear();
        }
        if (PD3==PDflag)
        {
            OLED_ShowString(0,4,"three",16);
            OLED_ShowNum(0,6,PDflag,9,16);
            delay_ms(500);
            OLED_Clear();
        }
        if (PD4==PDflag)
                {
                    OLED_ShowString(0,4,"four",16);
                    OLED_ShowNum(0,6,PDflag,9,16);
                    delay_ms(500);
                    OLED_Clear();
                }
        if (PD5==PDflag)
                {
                    OLED_ShowString(0,4,"five",16);
                    OLED_ShowNum(0,6,PDflag,9,16);
                    delay_ms(500);
                    OLED_Clear();
                }
*/
//        OLED_ShowNum(32,0,PD1,9,16);
//        OLED_ShowNum(32,2,PD2,9,16);
//        OLED_ShowNum(32,4,PD3,9,16);
//        OLED_ShowNum(32,6,PD4,9,16);
    }
}
