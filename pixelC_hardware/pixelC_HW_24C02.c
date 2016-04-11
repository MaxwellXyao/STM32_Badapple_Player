#include"system.h"
#include"pixelC_Hardware_include.h"
#include"I2C.h"

//##############################【硬件定义】##############################

void pixelC_HW_24C02_SCL(u8 val)
{
	PAout(11)=val; //SCL
}

void pixelC_HW_24C02_SDA(u8 val)
{
	#if SDA_Pin/8									
			SDA_GPIOx->CRH&=~((u32)0xf<<((SDA_Pin%8)*4));		
			SDA_GPIOx->CRH|=(u32)0x3<<((SDA_Pin%8)*4);
	#else
			SDA_GPIOx->CRL&=~((u32)0xf<<((SDA_Pin%8)*4));
			SDA_GPIOx->CRL|=(u32)0x3<<((SDA_Pin%8)*4);
	#endif
	PAout(SDA_Pin)=val; //SDA	 
}

u8 pixelC_24C02_SDA_I(void)
{
	#if SDA_Pin/8									
			SDA_GPIOx->CRH&=~((u32)0xf<<((SDA_Pin%8)*4));		
			SDA_GPIOx->CRH|=(u32)0x8<<((SDA_Pin%8)*4);
	#else
			SDA_GPIOx->CRL&=~((u32)0xf<<((SDA_Pin%8)*4));
			SDA_GPIOx->CRL|=(u32)0x8<<((SDA_Pin%8)*4);
	#endif
	return (PAin(SDA_Pin));   //输入SDA 
}

void pixelC_HW_24C02_Port_Init(void)
{
	RCC->APB2ENR|=1<<2;    		//使能PORTA时钟  	   
	#if SDA_Pin/8									
			SDA_GPIOx->CRH&=~((u32)0xf<<((SDA_Pin%8)*4));		
			SDA_GPIOx->CRH|=(u32)0x3<<((SDA_Pin%8)*4);
	#else
			SDA_GPIOx->CRL&=~((u32)0xf<<((SDA_Pin%8)*4));
			SDA_GPIOx->CRL|=(u32)0x3<<((SDA_Pin%8)*4);
	#endif

	#if SCL_Pin/8									
			SCL_GPIOx->CRH&=~((u32)0xf<<((SCL_Pin%8)*4));		
			SCL_GPIOx->CRH|=(u32)0x3<<((SCL_Pin%8)*4);
	#else
			SCL_GPIOx->CRL&=~((u32)0xf<<((SCL_Pin%8)*4));
			SCL_GPIOx->CRL|=(u32)0x3<<((SCL_Pin%8)*4);
	#endif
	
	pixelC_HW_24C02_SCL(1);
	pixelC_HW_24C02_SDA(1);	
}

I2C_HWM pixelC_HW_24C02={
 	pixelC_HW_24C02_Port_Init,
	pixelC_HW_24C02_SCL,
	pixelC_HW_24C02_SDA,
	pixelC_24C02_SDA_I
};//定义硬件信息管理块

//##############################【API】##############################
//【24c02应用函数族】------------------------------------------------------

void pixelC_HW_24C02_Init(void)
{
	 I2C_Port_Init(pixelC_HW_24C02);
}

void pixelC_HW_24C02_WriteChar(u8 addr,u8 data)	//24c02单字节写
{
	I2C_Start(pixelC_HW_24C02);
	I2C_Send_Byte(pixelC_HW_24C02,0xa0);
	I2C_Wait_Ack(pixelC_HW_24C02);
	I2C_Send_Byte(pixelC_HW_24C02,addr);
	I2C_Wait_Ack(pixelC_HW_24C02);
	I2C_Send_Byte(pixelC_HW_24C02,data);
	I2C_Wait_Ack(pixelC_HW_24C02);
	I2C_Stop(pixelC_HW_24C02);

	delay_ms(15);		//【写完以后一定要加10ms以上的延时固化写入的数据】
}

u8 pixelC_HW_24C02_ReadChar(u8 addr)	 			//24c02单字节读
{
	unsigned char data=0;
	I2C_Start(pixelC_HW_24C02);

	I2C_Send_Byte(pixelC_HW_24C02,0xa0);
	I2C_Wait_Ack(pixelC_HW_24C02);
	I2C_Send_Byte(pixelC_HW_24C02,addr);
	I2C_Wait_Ack(pixelC_HW_24C02);	

	I2C_Start(pixelC_HW_24C02);
	I2C_Send_Byte(pixelC_HW_24C02,0xa1);
	I2C_Wait_Ack(pixelC_HW_24C02);	
	data=I2C_Read_Byte(pixelC_HW_24C02,0); 
	I2C_Stop(pixelC_HW_24C02);
	
	return(data);
}
/******************************************************************************************/

void pixelC_HW_24C02_MemcpyToEEPROM(u8 destination,void *source,u16 size) 
{
	u8 *_source=(u8 *)source;
	for(;size>0;size--) { 
		pixelC_HW_24C02_WriteChar(destination++,*(_source++)); 
	}
}

void pixelC_HW_24C02_MemcpyFromEEPROM(void *destination,u8 source,u16 size)
{
	u8 data;
	u8 *_destination=(u8 *)destination;
	for(;size>0;size--){ 
		data=pixelC_HW_24C02_ReadChar(source++);   
		*(_destination++)=data; 
	}
}



















//
//void pixelC_HW_24C02_Write_LenByte(unsigned char addr,unsigned char len,unsigned long data)	//24c02写特定长度的数据
//{
//	unsigned char t=0;
//	for(t=0;t<len;t++)
//	{ 
//		pixelC_HW_24C02_Write_Char(addr+t,(data>>(8*t))&0xff);
//	}
//}
//
//unsigned long pixelC_HW_24C02_Read_LenByte(unsigned char addr,unsigned char len)	//24c02读特定长度的数据
//{
//	unsigned char t=0;
//	unsigned long temp=0;
//	for(t=0;t<len;t++)
//	{ 
//		temp<<=8;
//		temp+=pixelC_HW_24C02_Read_Char(addr+len-t-1);
//	}
//	return temp;
//}
//
///******************************************************************************************/
//
//void pixelC_HW_24C02_Write_Buf(unsigned char addr,unsigned char len,unsigned char *buf)	//24c02写数组
//{
//	while(len--)
//	{ 
//		pixelC_HW_24C02_Write_Char(addr,*buf);
//		addr++;
//		buf++;
//	}
//}
//
//void pixelC_HW_24C02_Read_Buf(unsigned char addr,unsigned char len,unsigned char *buf)	//24c02读数组
//{
//	while(len)
//	{ 
//		*buf++=pixelC_HW_24C02_Read_Char(addr++);
//		len--;
//	}
//}
//



