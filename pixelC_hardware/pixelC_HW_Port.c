#include"pixelC_Hardware_include.h"
//使用寄存器需要stm32f10x_map.h文件支持




static void Port_PinInit_GPIO(PIN_PXx PXx,u8 mode)
{
	GPIO_TypeDef *gpoi_reg=(GPIO_TypeDef *)(GPIOA_BASE+bit_getH4((int)PXx)*0x400);
	u8 temp=(bit_getL4((int)PXx)%8)*4;
	RCC->APB2ENR|=1<<(2+bit_getH4((int)PXx));    		//使能时钟 
	if(bit_getL4((int)PXx)/8){
		gpoi_reg->CRH&=~((u32)0xf<<temp);		
		gpoi_reg->CRH|=(u32)mode<<temp;
	}
	else{
		gpoi_reg->CRL&=~((u32)0xf<<temp);
		gpoi_reg->CRL|=(u32)mode<<temp;
	}
}

static void Port_PinInit_ADC(PIN_PXx PXx)
{
	u8 pin_temp=bit_getL4((int)PXx);
//======【ADC引脚】	
 	RCC->APB2ENR|=1<<(2+bit_getH4((int)PXx));    		//使能时钟 
	Port_PinInit_GPIO(PXx,0);	//anolog输入（该寄存器置0）	

//======【ADC时钟设置】		 
	RCC->APB2ENR|=1<<9;    //ADC1时钟使能
	RCC->APB2RSTR|=1<<9;   //ADC1复位
	RCC->APB2RSTR&=~(1<<9);//复位结束

//======【采集周期设置】		    
	RCC->CFGR&=~(3<<14);   	//分频因子清零	
	RCC->CFGR|=2<<14; 		//SYSCLK/DIV2=12M ADC时钟设置为12M,ADC最大时钟不能超过14M!
	//否则将导致ADC准确度下降!

//======【ADC设置】	     	 
	ADC1->CR1&=0XF0FFFF;   //工作模式清零
	ADC1->CR1|=0<<16;      //独立工作模式  
	ADC1->CR1&=~(1<<8);    //非扫描模式	  
	ADC1->CR2&=~(1<<1);    //单次转换模式
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //软件控制转换  
	ADC1->CR2|=1<<20;      //使用用外部触发(SWSTART)!!!	必须使用一个事件来触发
	ADC1->CR2&=~(1<<11);   //右对齐	 

//======【ADC规则】			  
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1&=0<<20; 		//规则通道总数1个

//======【ADC速度】		
	ADC1->SMPR2&=~((u32)7<<(3*pin_temp));  //通道采样时间清空	  
 	ADC1->SMPR2|=((u32)7<<(3*pin_temp));   //239.5周期，提高采样时间可以提高精确度    		
	
//======【校准】	 
	ADC1->CR2|=1<<0;	   		//开启AD转换器	 
	ADC1->CR2|=1<<3;       	//使能复位校准  
	while(ADC1->CR2&1<<3); 	//等待校准结束 			 
    //该位由软件设置并由硬件清除。在校准寄存器被初始化后该位将被清除。 		 
	ADC1->CR2|=1<<2;        	//开启AD校准	   
	while(ADC1->CR2&1<<2);  	//等待校准结束
	//该位由软件设置以开始校准，并在校准结束时由硬件清除  
}

static void Port_PinInit_PWM(PIN_PXx PXx)
{
	Port_PinInit_GPIO(PXx,0xB);	//复用输出（该寄存器置B）	  
	RCC->APB1ENR|=1<<0; 	//TIM2时钟使能 

	if(bit_getL4((int)PXx)/2){
		TIM2->CCMR1|=7<<((bit_getL4((int)PXx)%2)*8+4);  	//CH1,CH2 PWM2模式
		TIM2->CCMR1|=1<<((bit_getL4((int)PXx)%2)*8+3); 		//CH1,CH2 预装载使能
	}
	else{
		TIM2->CCMR2|=7<<((bit_getL4((int)PXx)%2)*8+4);  	//CH3,CH4 PWM2模式
		TIM2->CCMR2|=1<<((bit_getL4((int)PXx)%2)*8+3); 		//CH3,CH4 预装载使能
	}
	TIM2->CR1=0x0080;   	//ARPE使能
	TIM2->CR1|=1<<0;    	//使能定时器2	  	   		
}

//#############################【外部】###############################

void pixelC_HW_Port_PinInit(PIN_PXx PXx,PIN_MODE mode)
{
	switch(mode)
	{
		case OUTPUT:	Port_PinInit_GPIO(PXx,0x3);	break;
		case INPUT:		Port_PinInit_GPIO(PXx,0x8);	break;
		case ADC_IN:	Port_PinInit_ADC(PXx);		break;
		case PWM_OUT:	Port_PinInit_PWM(PXx);		break;
		default:;
	}	
}



u16 pixelC_HW_Port_getADC(PIN_PXx PXx)   
{	   
	ADC1->SQR3&=0XFFFFFFE0;//规则序列1 通道ch
	ADC1->SQR3|=bit_getL4((int)PXx);				  			    
	ADC1->CR2|=1<<22;       //启动规则转换通道 
	while(!(ADC1->SR&1<<1));//等待转换结束	 	   
	return ADC1->DR;		//返回adc值		
}

void pixelC_HW_Port_setPWM(PIN_PXx PXx,u16 ccr,u16 arr,u16 psc,u8 pwm_on)
{
	TIM2->ARR=arr;			//设定计数器自动重装值 
	TIM2->PSC=psc;			//预分频器分频设置
	switch(bit_getL4((int)PXx))
	{
		case 0:TIM2->CCR1=ccr;break;
		case 1:TIM2->CCR2=ccr;break;
		case 2:TIM2->CCR3=ccr;break;
		case 3:TIM2->CCR4=ccr;break;
		default:return;
	}
	TIM2->CCER|=((u32)pwm_on)<<((bit_getL4((int)PXx)*4));   	//OC1 输出使能			 
}










