#include"pixelC_Hardware_include.h"
//ʹ�üĴ�����Ҫstm32f10x_map.h�ļ�֧��




static void Port_PinInit_GPIO(PIN_PXx PXx,u8 mode)
{
	GPIO_TypeDef *gpoi_reg=(GPIO_TypeDef *)(GPIOA_BASE+bit_getH4((int)PXx)*0x400);
	u8 temp=(bit_getL4((int)PXx)%8)*4;
	RCC->APB2ENR|=1<<(2+bit_getH4((int)PXx));    		//ʹ��ʱ�� 
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
//======��ADC���š�	
 	RCC->APB2ENR|=1<<(2+bit_getH4((int)PXx));    		//ʹ��ʱ�� 
	Port_PinInit_GPIO(PXx,0);	//anolog���루�üĴ�����0��	

//======��ADCʱ�����á�		 
	RCC->APB2ENR|=1<<9;    //ADC1ʱ��ʹ��
	RCC->APB2RSTR|=1<<9;   //ADC1��λ
	RCC->APB2RSTR&=~(1<<9);//��λ����

//======���ɼ��������á�		    
	RCC->CFGR&=~(3<<14);   	//��Ƶ��������	
	RCC->CFGR|=2<<14; 		//SYSCLK/DIV2=12M ADCʱ������Ϊ12M,ADC���ʱ�Ӳ��ܳ���14M!
	//���򽫵���ADC׼ȷ���½�!

//======��ADC���á�	     	 
	ADC1->CR1&=0XF0FFFF;   //����ģʽ����
	ADC1->CR1|=0<<16;      //��������ģʽ  
	ADC1->CR1&=~(1<<8);    //��ɨ��ģʽ	  
	ADC1->CR2&=~(1<<1);    //����ת��ģʽ
	ADC1->CR2&=~(7<<17);	   
	ADC1->CR2|=7<<17;	   //�������ת��  
	ADC1->CR2|=1<<20;      //ʹ�����ⲿ����(SWSTART)!!!	����ʹ��һ���¼�������
	ADC1->CR2&=~(1<<11);   //�Ҷ���	 

//======��ADC����			  
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1&=0<<20; 		//����ͨ������1��

//======��ADC�ٶȡ�		
	ADC1->SMPR2&=~((u32)7<<(3*pin_temp));  //ͨ������ʱ�����	  
 	ADC1->SMPR2|=((u32)7<<(3*pin_temp));   //239.5���ڣ���߲���ʱ�������߾�ȷ��    		
	
//======��У׼��	 
	ADC1->CR2|=1<<0;	   		//����ADת����	 
	ADC1->CR2|=1<<3;       	//ʹ�ܸ�λУ׼  
	while(ADC1->CR2&1<<3); 	//�ȴ�У׼���� 			 
    //��λ��������ò���Ӳ���������У׼�Ĵ�������ʼ�����λ��������� 		 
	ADC1->CR2|=1<<2;        	//����ADУ׼	   
	while(ADC1->CR2&1<<2);  	//�ȴ�У׼����
	//��λ����������Կ�ʼУ׼������У׼����ʱ��Ӳ�����  
}

static void Port_PinInit_PWM(PIN_PXx PXx)
{
	Port_PinInit_GPIO(PXx,0xB);	//����������üĴ�����B��	  
	RCC->APB1ENR|=1<<0; 	//TIM2ʱ��ʹ�� 

	if(bit_getL4((int)PXx)/2){
		TIM2->CCMR1|=7<<((bit_getL4((int)PXx)%2)*8+4);  	//CH1,CH2 PWM2ģʽ
		TIM2->CCMR1|=1<<((bit_getL4((int)PXx)%2)*8+3); 		//CH1,CH2 Ԥװ��ʹ��
	}
	else{
		TIM2->CCMR2|=7<<((bit_getL4((int)PXx)%2)*8+4);  	//CH3,CH4 PWM2ģʽ
		TIM2->CCMR2|=1<<((bit_getL4((int)PXx)%2)*8+3); 		//CH3,CH4 Ԥװ��ʹ��
	}
	TIM2->CR1=0x0080;   	//ARPEʹ��
	TIM2->CR1|=1<<0;    	//ʹ�ܶ�ʱ��2	  	   		
}

//#############################���ⲿ��###############################

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
	ADC1->SQR3&=0XFFFFFFE0;//��������1 ͨ��ch
	ADC1->SQR3|=bit_getL4((int)PXx);				  			    
	ADC1->CR2|=1<<22;       //��������ת��ͨ�� 
	while(!(ADC1->SR&1<<1));//�ȴ�ת������	 	   
	return ADC1->DR;		//����adcֵ		
}

void pixelC_HW_Port_setPWM(PIN_PXx PXx,u16 ccr,u16 arr,u16 psc,u8 pwm_on)
{
	TIM2->ARR=arr;			//�趨�������Զ���װֵ 
	TIM2->PSC=psc;			//Ԥ��Ƶ����Ƶ����
	switch(bit_getL4((int)PXx))
	{
		case 0:TIM2->CCR1=ccr;break;
		case 1:TIM2->CCR2=ccr;break;
		case 2:TIM2->CCR3=ccr;break;
		case 3:TIM2->CCR4=ccr;break;
		default:return;
	}
	TIM2->CCER|=((u32)pwm_on)<<((bit_getL4((int)PXx)*4));   	//OC1 ���ʹ��			 
}










