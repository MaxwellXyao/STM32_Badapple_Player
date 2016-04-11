#ifndef PIXELC_HW_FLAGLIGHT_H
#define	PIXELC_HW_FLAGLIGHT_H

//###############################【硬件】####################################
#define FLAGLIGHT_GPIOx GPIOA
#define FLAGLIGHT_Pin 8	 //PA8

//###############################【参数】####################################

#define TEINKLE_WIDTH 10 //闪烁持续时间ms

//###############################【API】####################################
void pixelC_HW_flagLight_Init(void);		//板载信号灯初始化,PA.8(TIM1_CH1)

void pixelC_HW_flagLight_On(void);			//板载信号灯亮
void pixelC_HW_flagLight_Off(void);			//板载信号灯灭
void pixelC_HW_flagLight_Twinkle(void);		//板载信号灯闪烁

#endif

