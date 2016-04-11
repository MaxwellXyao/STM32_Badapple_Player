#include"pixelC_Hardware_include.h"

//##############################����ر�����##############################

FATFS FatFs;   				//����ļ�ϵͳ��Ϣ
FIL file;	   				//����ļ���Ϣ

static u8 BP_FLG_OnXOff=0;			//��־_���ſ���	
u8 BP_Frame_cache[BP_FRAME_SIZE];	//֡��ʱ���
volatile u16 BP_Current_Frame=0;	//��ǰ֡
unsigned int num=0;

//##############################������ҳ�桿##############################
MENU_PAGE page;

__M_PAGE(page,"badapple",PAGE_NULL,{

	 SOLGUI_Widget_Picture(0,0,74,56,(const u8*)BP_Frame_cache,74,56,FRM|REV); //ͼƬ
	 SOLGUI_Widget_Bar(74,0,4,55,BP_FRAME_NUM,0,BP_Current_Frame,DIREC_Y);
	 SOLGUI_Widget_Text(79,0,F6X8,"%d",BP_Current_Frame);
});

//##############################���ڲ����á�##############################

static void TIMER2_Init(u16 psr,u16 arr)			   		//ʹ�ö�ʱ��2��ͨ�ã�,��ʱ0.1s(10Hz)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	 //�����ʼ������
	NVIC_InitTypeDef NVIC_InitStructure;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    TIM_TimeBaseStructure.TIM_Period = psr-1; 		    	
    TIM_TimeBaseStructure.TIM_Prescaler = arr-1;    	     
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 	//TIM2����ж�����

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//�ж����ȼ�����2
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQChannel;			//����TIM2_IRQ������
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;		//��ռ���ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;			//�����ȼ�2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		  		//NVICʹ��
	NVIC_Init(&NVIC_InitStructure);						  //�����жϷ����������ȼ�
}

void TIM2_IRQHandler(void) 						//TIM2��ʱ���жϺ���
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		if(BP_FLG_OnXOff==1)
		{
			f_lseek(&file,BP_Current_Frame*BP_FRAME_SIZE);		//�ļ�ָ����
			f_read(&file,BP_Frame_cache,BP_FRAME_SIZE,&num);	//��ȡ
			SOLGUI_Menu_PageStage();		//ǰ̨
			SOLGUI_Refresh();				//������Ļ
			if(BP_Current_Frame<BP_FRAME_NUM) BP_Current_Frame++;
			else BP_FLG_OnXOff=0;
		}
		else
		{
			TIM_Cmd(TIM2,DISABLE); 	 		//�ر�tim2����
			f_close(&file);	
		}
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
	}
}

//##############################���ⲿ���á�##############################

void BP_Init(void)
{
//==================���޿���ʾ��
	while(SD_Init()){			
		SOLGUI_printf(0,0,F6X8,"No SDcard!");	
		SOLGUI_Refresh();				//������Ļ
	}
//==================������SD����
	f_mount(SD_CARD,&FatFs);		//�ȹ���SD��
	TIMER2_Init(667,3600); 			//��ʼ����ʱ��
}

void BP_Play_On(void)
{
	BP_FLG_OnXOff=1;
	f_open(&file,(const TCHAR*)"badapple.bin", FA_READ);   	//�Զ���ʽ���ļ����ַ���Ҫ��(const TCHAR*)ת������
	TIM_Cmd(TIM2, ENABLE); 	 		//����tim2����
}



void BP_test(u16 Frame_Num)
{
	f_open(&file,(const TCHAR*)"badapple.bin", FA_READ);   	//�Զ���ʽ���ļ����ַ���Ҫ��(const TCHAR*)ת������
	f_lseek(&file,Frame_Num*BP_FRAME_SIZE);		//�ļ�ָ����
	f_read(&file,BP_Frame_cache,BP_FRAME_SIZE,&num);	//��ȡ	
}























