#ifndef pixelC_HW_24C02_H
#define pixelC_HW_24C02_H

/*-------------------------------------------------------------------

【pixelC2板载24C02】
	
	工作电压：1.8v~5.5v
	通信协议：I2C
	存储容量：256字节
	地址范围：0x00~0xFF

--------------------------------------------------------------------*/

//############################【硬件定义】##############################	
#define SCL_GPIOx GPIOA
#define SCL_Pin 11 	//PA11
#define SDA_GPIOx GPIOA
#define SDA_Pin 12	//PA12

//##############################【API】##############################					 
void pixelC_HW_24C02_Init(void);											//24c02初始化																												
//写数据时注意地址，以免发生冲突
void pixelC_HW_24C02_MemcpyToEEPROM(u8 destination,void *source,u16 size); 	   //24c02写入数据(无校验位)
void pixelC_HW_24C02_MemcpyFromEEPROM(void *destination,u8 source,u16 size);   //24c02读出数据(无校验位)

#endif

