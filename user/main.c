#include"pixelC_Hardware_include.h"


extern MENU_PAGE page;

//##############################����������##############################

int main()
{
	Stm32_Clock_Init();					//ϵͳʱ�ӳ�ʼ��
	delay_init(72);						//72MHz�ڲ�Ƶ��

	pixelC_HW_flagLight_Init();
	pixelC_HW_Key_Init();
	SOLGUI_Init(&page);

	BP_Init();
	BP_Play_On();				//��ʼ����

	while(1);
}





