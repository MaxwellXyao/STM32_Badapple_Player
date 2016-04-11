#ifndef PIXELC_HW_OLED_H
#define PIXELC_HW_OLED_H

#include"system.h"
#include"delay.h"

//##############################【硬件定义】##############################
//-------------引脚定义
#define SPI_CK_GPIOx GPIOB
#define SPI_CK_Pin 	10	//PB.10

#define SPI_DI_GPIOx GPIOB
#define SPI_DI_Pin 	11	//PB.11

#define SPI_RST_GPIOx GPIOB
#define SPI_RST_Pin 0	//PB.0

#define SPI_DC_GPIOx GPIOB
#define SPI_DC_Pin 	1	//PB.1

//------------电平变化函数
//****CK****
#define OLED_CK_HIGH() 		PBout(10)=1
#define OLED_CK_LOW()		PBout(10)=0
//****DI****
#define OLED_DI_HIGH()		PBout(11)=1
#define OLED_DI_LOW()		PBout(11)=0
//****RST****
#define OLED_RST_HIGH()		PBout(0)=1
#define OLED_RST_LOW()		PBout(0)=0
//****DC****
#define OLED_DC_HIGH()		PBout(1)=1
#define OLED_DC_LOW()		PBout(1)=0

//------------延时函数
#define OLED_Delay() delay_ms(10)

//##############################【参数】##############################
#define OLED_X_WIDTH        	128		//X像素长
#define OLED_Y_WIDTH        	64		//Y像素长
#define OLED_Y_PAGE				8		//Y方向页长度

//############################【功能开关】############################
#define OLED_USE_SOLGUI		//使用SOL_GUI，不编译硬件字库

//##############################【内部】##############################
void pixelC_HW_OLED_PinInit(void);
void pixelC_HW_OLED_WrDat(unsigned char dat);
void pixelC_HW_OLED_WrCmd(unsigned char cmd);
void pixelC_HW_OLED_Set_Pos(unsigned char x, unsigned char y);
void pixelC_HW_OLED_Fill(unsigned char bmp_dat);

//##############################【API】##############################
void pixelC_HW_OLED_Init(void);			//OLED硬件初始化
void pixelC_HW_OLED_P6x8Str(unsigned char x,unsigned char y,unsigned char ch[]); 	//硬件写字符串:硬件测试
void pixelC_HW_OLED_CLS(void);			//硬件清屏

//##############################【移植用】##############################
void pixelC_HW_OLED_FillScreen(u8 gram[OLED_X_WIDTH][OLED_Y_PAGE]);

#endif
