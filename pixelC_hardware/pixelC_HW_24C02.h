#ifndef pixelC_HW_24C02_H
#define pixelC_HW_24C02_H

/*-------------------------------------------------------------------

��pixelC2����24C02��
	
	������ѹ��1.8v~5.5v
	ͨ��Э�飺I2C
	�洢������256�ֽ�
	��ַ��Χ��0x00~0xFF

--------------------------------------------------------------------*/

//############################��Ӳ�����塿##############################	
#define SCL_GPIOx GPIOA
#define SCL_Pin 11 	//PA11
#define SDA_GPIOx GPIOA
#define SDA_Pin 12	//PA12

//##############################��API��##############################					 
void pixelC_HW_24C02_Init(void);											//24c02��ʼ��																												
//д����ʱע���ַ�����ⷢ����ͻ
void pixelC_HW_24C02_MemcpyToEEPROM(u8 destination,void *source,u16 size); 	   //24c02д������(��У��λ)
void pixelC_HW_24C02_MemcpyFromEEPROM(void *destination,u8 source,u16 size);   //24c02��������(��У��λ)

#endif

