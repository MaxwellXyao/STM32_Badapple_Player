#ifndef SPI_H
#define SPI_H

/*【说明】------------------------------------------
这个SPI通用库是为老版本的pixelC写的，也可以移植到其
他单片机上。由于老版本pixelC设计失误，未引出硬件SPI
IO（在pixelC2中已引入片载硬件SPI2），因此写出这个软
件模拟SPI库。软件模拟SPI速度上会远低于硬件SPI，只推
荐用于驱动一些对速度要求不高的模块.	【pixelC，pixelC2
皆可用】

【pixelC2】pixelC2在此库中增加硬件SPI2的方式：

SCK		------->	PB13
MISO	------->	PB14
MOSI	------->	PB15
CS		------->	自定义

--------------------------------------------------*/

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;	  
#ifndef NULL
	#define NULL 0
#endif


//##############################【内部】#############################
typedef struct __SPI_HWM{				//SPI硬件管理块
	 void (*SPI_HW_Init)();				//硬件初始化函数
	 void (*SPI_MOSI)(u8);	//MOSI引脚输出函数
	 void (*SPI_SCLK)(u8);	//SCLK引脚输出函数
	 u8 (*MISO_READ)();		//MISO引脚读取函数
	 u8 speed_mode;			//速度模式（1：高速模式，0：低速模式）
}SPI_HWM;								

#define HIGH 1		      //此处重复定义片载库中的电平定义
#define LOW  0

//##############################【API】##############################
void SPI_Port_Init(SPI_HWM spi_hw);										//SPI总线引脚初始化
u8 SPI_ReadWrite_Byte(SPI_HWM spi_hw,u8 data);	//SPI总线传输数据(接收时发送0xff,不读取返回值即可)
void SPI_Speed_Set(SPI_HWM spi_hw,u8 speed);					//速度设置，（0：低速，1：高速，默认低速）

//设定高速低速间隔（单位：us）
#define LOW_SPEED 	200
#define HIGH_SPEED 	3

#endif
