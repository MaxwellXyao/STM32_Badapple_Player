#ifndef SPI_H
#define SPI_H

/*��˵����------------------------------------------
���SPIͨ�ÿ���Ϊ�ϰ汾��pixelCд�ģ�Ҳ������ֲ����
����Ƭ���ϡ������ϰ汾pixelC���ʧ��δ����Ӳ��SPI
IO����pixelC2��������Ƭ��Ӳ��SPI2�������д�������
��ģ��SPI�⡣���ģ��SPI�ٶ��ϻ�Զ����Ӳ��SPI��ֻ��
����������һЩ���ٶ�Ҫ�󲻸ߵ�ģ��.	��pixelC��pixelC2
�Կ��á�

��pixelC2��pixelC2�ڴ˿�������Ӳ��SPI2�ķ�ʽ��

SCK		------->	PB13
MISO	------->	PB14
MOSI	------->	PB15
CS		------->	�Զ���

--------------------------------------------------*/

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;	  
#ifndef NULL
	#define NULL 0
#endif


//##############################���ڲ���#############################
typedef struct __SPI_HWM{				//SPIӲ�������
	 void (*SPI_HW_Init)();				//Ӳ����ʼ������
	 void (*SPI_MOSI)(u8);	//MOSI�����������
	 void (*SPI_SCLK)(u8);	//SCLK�����������
	 u8 (*MISO_READ)();		//MISO���Ŷ�ȡ����
	 u8 speed_mode;			//�ٶ�ģʽ��1������ģʽ��0������ģʽ��
}SPI_HWM;								

#define HIGH 1		      //�˴��ظ�����Ƭ�ؿ��еĵ�ƽ����
#define LOW  0

//##############################��API��##############################
void SPI_Port_Init(SPI_HWM spi_hw);										//SPI�������ų�ʼ��
u8 SPI_ReadWrite_Byte(SPI_HWM spi_hw,u8 data);	//SPI���ߴ�������(����ʱ����0xff,����ȡ����ֵ����)
void SPI_Speed_Set(SPI_HWM spi_hw,u8 speed);					//�ٶ����ã���0�����٣�1�����٣�Ĭ�ϵ��٣�

//�趨���ٵ��ټ������λ��us��
#define LOW_SPEED 	200
#define HIGH_SPEED 	3

#endif
