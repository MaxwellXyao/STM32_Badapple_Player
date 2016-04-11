#ifndef DELAY_H
#define DELAY_H

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;	  
#ifndef NULL
	#define NULL 0
#endif


//###############################【系统函数】####################################
void SysTick_Handler(void);

//###############################【API】####################################

void delay_init(u8 SYSCLK);		//初始化延迟函数，SYSCLK:系统时钟,一般写72

void delay_us(u32 nus);			//延时nus,nus为要延时的us数
void delay_ms(u16 nms);			//延时nms,nms为要延时的ms数

#endif
