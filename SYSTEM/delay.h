#ifndef DELAY_H
#define DELAY_H

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;	  
#ifndef NULL
	#define NULL 0
#endif


//###############################��ϵͳ������####################################
void SysTick_Handler(void);

//###############################��API��####################################

void delay_init(u8 SYSCLK);		//��ʼ���ӳٺ�����SYSCLK:ϵͳʱ��,һ��д72

void delay_us(u32 nus);			//��ʱnus,nusΪҪ��ʱ��us��
void delay_ms(u16 nms);			//��ʱnms,nmsΪҪ��ʱ��ms��

#endif
