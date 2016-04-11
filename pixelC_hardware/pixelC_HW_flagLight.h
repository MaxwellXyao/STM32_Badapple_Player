#ifndef PIXELC_HW_FLAGLIGHT_H
#define	PIXELC_HW_FLAGLIGHT_H

//###############################��Ӳ����####################################
#define FLAGLIGHT_GPIOx GPIOA
#define FLAGLIGHT_Pin 8	 //PA8

//###############################��������####################################

#define TEINKLE_WIDTH 10 //��˸����ʱ��ms

//###############################��API��####################################
void pixelC_HW_flagLight_Init(void);		//�����źŵƳ�ʼ��,PA.8(TIM1_CH1)

void pixelC_HW_flagLight_On(void);			//�����źŵ���
void pixelC_HW_flagLight_Off(void);			//�����źŵ���
void pixelC_HW_flagLight_Twinkle(void);		//�����źŵ���˸

#endif

