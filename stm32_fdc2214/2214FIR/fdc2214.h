/**
  ******************************************************************************
  * @file    FDC2214.h
  * @author  BOB   
  * @version V1.0
  * @date    2018-07-5
  * @email   
  * @brief   FDC2214寄存器地址及数据读取处理函数
  ******************************************************************************
  */
#ifndef __FDC2214_H
#define __FDC2214_H

#define u8 unsigned char

    
static u8 default_addr; //FDC2214地址选择暂存   
    
//#include "sys.h"




// FDC_XX_ COMMANDS
#define LDC13xx16xx_CMD_DATA_MSB_CH0	      0x00
#define LDC13xx16xx_CMD_DATA_LSB_CH0	      0x01
#define LDC13xx16xx_CMD_DATA_MSB_CH1	      0x02
#define LDC13xx16xx_CMD_DATA_LSB_CH1	      0x03
#define LDC13xx16xx_CMD_DATA_MSB_CH2	      0x04
#define LDC13xx16xx_CMD_DATA_LSB_CH2	      0x05
#define LDC13xx16xx_CMD_DATA_MSB_CH3	      0x06
#define LDC13xx16xx_CMD_DATA_LSB_CH3	      0x07
#define LDC13xx16xx_CMD_REF_COUNT_CH0	      0x08     //参考计数设置
#define LDC13xx16xx_CMD_REF_COUNT_CH1	      0x09
#define LDC13xx16xx_CMD_REF_COUNT_CH2	      0x0A
#define LDC13xx16xx_CMD_REF_COUNT_CH3	      0x0B
#define LDC13xx16xx_CMD_OFFSET_CH0	          0x0C     //补偿值
#define LDC13xx16xx_CMD_OFFSET_CH1	          0x0D
#define LDC13xx16xx_CMD_OFFSET_CH2	          0x0E
#define LDC13xx16xx_CMD_OFFSET_CH3	          0x0F
#define LDC13xx16xx_CMD_SETTLE_COUNT_CH0	  0x10     //解决参考计数
#define LDC13xx16xx_CMD_SETTLE_COUNT_CH1  	  0x11
#define LDC13xx16xx_CMD_SETTLE_COUNT_CH2	  0x12
#define LDC13xx16xx_CMD_SETTLE_COUNT_CH3	  0x13
#define LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH0 	  0x14     //参考和传感器分频设置
#define LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH1 	  0x15
#define LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH2 	  0x16
#define LDC13xx16xx_CMD_CLOCK_DIVIDERS_CH3 	  0x17
#define LDC13xx16xx_CMD_STATUS            	  0x18
#define LDC13xx16xx_CMD_ERROR_CONFIG       	  0x19     //错误报告配置
#define LDC13xx16xx_CMD_CONFIG             	  0x1A     //转换配置
#define LDC13xx16xx_CMD_MUX_CONFIG        	  0x1B     //通道复用
#define LDC13xx16xx_CMD_RESET_DEVICE      	  0x1C     //复位设备
//#define LDC13xx16xx_CMD_SYSTEM_CLOCK_CONFIG	  0x1D     //FDC2214没有这一项
#define LDC13xx16xx_CMD_DRIVE_CURRENT_CH0	  0x1E     //当前驱动设置
#define LDC13xx16xx_CMD_DRIVE_CURRENT_CH1 	  0x1F     //
#define LDC13xx16xx_CMD_DRIVE_CURRENT_CH2 	  0x20     //
#define LDC13xx16xx_CMD_DRIVE_CURRENT_CH3	  0x21     //
#define LDC13xx16xx_CMD_MANUFACTID	          0x7E     //制造商ID
#define LDC13xx16xx_CMD_DEVID	              0x7F     //设备ID

/** @name - Defaults Settings - */
//@{
#define EVM_MIN_I2CADDR     0x2A
#define EVM_MAX_I2CADDR     0x2B
#define EVM_DEFAULT_I2CADDR  0x2A                        //EVM_MIN_I2CADDR
#define EVM_DEFAULTS_SIZE 24 // 13 registers, 0x08 - 0x14
//@}

void ADDR_SD_Init(void) ;
u8 FDC2214_init(void);
void evm_processDRDY(unsigned long  allData[4]);

double GetCapacitance(unsigned long value);

#endif /* LDC13xx16xx_CMD_H_ */

/** @} */

