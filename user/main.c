#include"pixelC_Hardware_include.h"


extern MENU_PAGE page;

//##############################【主函数】##############################

int main()
{
	Stm32_Clock_Init();					//系统时钟初始化
	delay_init(72);						//72MHz内部频率

	pixelC_HW_flagLight_Init();
	pixelC_HW_Key_Init();
	SOLGUI_Init(&page);

	BP_Init();
	BP_Play_On();				//开始播放

	while(1);
}





