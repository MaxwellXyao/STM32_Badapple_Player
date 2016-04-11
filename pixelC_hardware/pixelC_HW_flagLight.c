#include"pixelC_Hardware_include.h"

void pixelC_HW_flagLight_Init(void)
{
	RCC->APB2ENR|=1<<2;    	  												
#if FLAGLIGHT_Pin/8		//CK							
		FLAGLIGHT_GPIOx->CRH&=~((u32)0xf<<((FLAGLIGHT_Pin%8)*4));		
		FLAGLIGHT_GPIOx->CRH|=(u32)0x3<<((FLAGLIGHT_Pin%8)*4);
#else
		FLAGLIGHT_GPIOx->CRL&=~((u32)0xf<<((FLAGLIGHT_Pin%8)*4));
		FLAGLIGHT_GPIOx->CRL|=(u32)0x3<<((FLAGLIGHT_Pin%8)*4);
#endif
	PAout(8)=1;	
}

void pixelC_HW_flagLight_On(void)
{
	PAout(8)=0;
}

void pixelC_HW_flagLight_Off(void)
{
	PAout(8)=1;
}

void pixelC_HW_flagLight_Twinkle(void)
{
	pixelC_HW_flagLight_On();
	delay_ms(TEINKLE_WIDTH);
	pixelC_HW_flagLight_Off();
}
