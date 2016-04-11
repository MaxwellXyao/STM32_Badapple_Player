#include"pixelC_Hardware_include.h"

//##############################【相关变量】##############################

FATFS FatFs;   				//存放文件系统信息
FIL file;	   				//存放文件信息

static u8 BP_FLG_OnXOff=0;			//标志_播放开关	
u8 BP_Frame_cache[BP_FRAME_SIZE];	//帧临时存放
volatile u16 BP_Current_Frame=0;	//当前帧
unsigned int num=0;

//##############################【操作页面】##############################
MENU_PAGE page;

__M_PAGE(page,"badapple",PAGE_NULL,{

	 SOLGUI_Widget_Picture(0,0,74,56,(const u8*)BP_Frame_cache,74,56,FRM|REV); //图片
	 SOLGUI_Widget_Bar(74,0,4,55,BP_FRAME_NUM,0,BP_Current_Frame,DIREC_Y);
	 SOLGUI_Widget_Text(79,0,F6X8,"%d",BP_Current_Frame);
});

//##############################【内部调用】##############################

static void TIMER2_Init(u16 psr,u16 arr)			   		//使用定时器2（通用）,定时0.1s(10Hz)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;	 //定义初始化变量
	NVIC_InitTypeDef NVIC_InitStructure;
		
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    TIM_TimeBaseStructure.TIM_Period = psr-1; 		    	
    TIM_TimeBaseStructure.TIM_Prescaler = arr-1;    	     
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1; 	 
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  	
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE); 	//TIM2溢出中断允许

	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);				//中断优先级分组2
	NVIC_InitStructure.NVIC_IRQChannel=TIM2_IRQChannel;			//进入TIM2_IRQ服务函数
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=1;		//抢占优先级2
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=1;			//子优先级2
	NVIC_InitStructure.NVIC_IRQChannelCmd=ENABLE;		  		//NVIC使能
	NVIC_Init(&NVIC_InitStructure);						  //设置中断服务函数和优先级
}

void TIM2_IRQHandler(void) 						//TIM2定时器中断函数
{
	if(TIM_GetITStatus(TIM2,TIM_IT_Update)!=RESET)
	{
		if(BP_FLG_OnXOff==1)
		{
			f_lseek(&file,BP_Current_Frame*BP_FRAME_SIZE);		//文件指针移
			f_read(&file,BP_Frame_cache,BP_FRAME_SIZE,&num);	//读取
			SOLGUI_Menu_PageStage();		//前台
			SOLGUI_Refresh();				//更新屏幕
			if(BP_Current_Frame<BP_FRAME_NUM) BP_Current_Frame++;
			else BP_FLG_OnXOff=0;
		}
		else
		{
			TIM_Cmd(TIM2,DISABLE); 	 		//关闭tim2计数
			f_close(&file);	
		}
		TIM_ClearITPendingBit(TIM2,TIM_FLAG_Update);
	}
}

//##############################【外部调用】##############################

void BP_Init(void)
{
//==================【无卡显示】
	while(SD_Init()){			
		SOLGUI_printf(0,0,F6X8,"No SDcard!");	
		SOLGUI_Refresh();				//更新屏幕
	}
//==================【挂载SD卡】
	f_mount(SD_CARD,&FatFs);		//先挂载SD卡
	TIMER2_Init(667,3600); 			//初始化定时器
}

void BP_Play_On(void)
{
	BP_FLG_OnXOff=1;
	f_open(&file,(const TCHAR*)"badapple.bin", FA_READ);   	//以读方式打开文件，字符串要加(const TCHAR*)转换类型
	TIM_Cmd(TIM2, ENABLE); 	 		//开启tim2计数
}



void BP_test(u16 Frame_Num)
{
	f_open(&file,(const TCHAR*)"badapple.bin", FA_READ);   	//以读方式打开文件，字符串要加(const TCHAR*)转换类型
	f_lseek(&file,Frame_Num*BP_FRAME_SIZE);		//文件指针移
	f_read(&file,BP_Frame_cache,BP_FRAME_SIZE,&num);	//读取	
}























