#include"system.h"


//###############################���ڲ�ʹ�á�####################################
//����������ƫ�Ƶ�ַ
//NVIC_VectTab:��ַ
//Offset:ƫ����
void System_NVIC_SetVectorTable(u32 NVIC_VectTab, u32 Offset)	 
{ 
  	//�������Ϸ���
	assert_param(IS_NVIC_VECTTAB(NVIC_VectTab));
	assert_param(IS_NVIC_OFFSET(Offset));  	 
	SCB->VTOR = NVIC_VectTab|(Offset & (u32)0x1FFFFF80);//����NVIC��������ƫ�ƼĴ���
	//���ڱ�ʶ����������CODE��������RAM��
}
//����NVIC����
//NVIC_Group:NVIC���� 0~4 �ܹ�5�� 
void System_NVIC_PriorityGroupConfig(u8 NVIC_Group)	 
{ 
	u32 temp,temp1;	  
	temp1=(~NVIC_Group)&0x07;//ȡ����λ
	temp1<<=8;
	temp=SCB->AIRCR;  //��ȡ��ǰ������
	temp&=0X0000F8FF; //�����ǰ����
	temp|=0X05FA0000; //д��Կ��
	temp|=temp1;	   
	SCB->AIRCR=temp;  //���÷���	    	  				   
}
//����������ִ���������踴λ!�����������𴮿ڲ�����.		    
//������ʱ�ӼĴ�����λ
void MYRCC_DeInit(void)
{										  					   
	RCC->APB1RSTR = 0x00000000;//��λ����			 
	RCC->APB2RSTR = 0x00000000; 
	  
  	RCC->AHBENR = 0x00000014;  //˯��ģʽ�����SRAMʱ��ʹ��.�����ر�.	  
  	RCC->APB2ENR = 0x00000000; //����ʱ�ӹر�.			   
  	RCC->APB1ENR = 0x00000000;   
	RCC->CR |= 0x00000001;     //ʹ���ڲ�����ʱ��HSION	 															 
	RCC->CFGR &= 0xF8FF0000;   //��λSW[1:0],HPRE[3:0],PPRE1[2:0],PPRE2[2:0],ADCPRE[1:0],MCO[2:0]					 
	RCC->CR &= 0xFEF6FFFF;     //��λHSEON,CSSON,PLLON
	RCC->CR &= 0xFFFBFFFF;     //��λHSEBYP	   	  
	RCC->CFGR &= 0xFF80FFFF;   //��λPLLSRC, PLLXTPRE, PLLMUL[3:0] and USBPRE 
	RCC->CIR = 0x00000000;     //�ر������ж�
	//����������				  
#ifdef  VECT_TAB_RAM
	System_NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0);
#else   
	System_NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);
#endif
}
//THUMBָ�֧�ֻ������
//�������·���ʵ��ִ�л��ָ��WFI
__asm void WFI_SET(void)
{
	WFI;    
}

//###############################������&��λ��####################################	 
void System_Standby(void)				//�������ģʽ
{
	SCB->SCR|=1<<2;			//ʹ��SLEEPDEEPλ (SYS->CTRL)	   
  	RCC->APB1ENR|=1<<28;     //ʹ�ܵ�Դʱ��	    
	RCC->APB1ENR|=1<<27;     //ʹ�ܱ���ʱ��	    
	PWR->CSR|=1<<8;          //����WKUP���ڻ���
	PWR->CR|=1<<2;           //���Wake-up ��־
	PWR->CR|=1<<1;           //PDDS��λ		  
	WFI_SET();				 //ִ��WFIָ��		 
}	  

void System_Soft_Reset(void)			//ϵͳ��λ
{   
	SCB->AIRCR =0X05FA0000|(u32)0x04;	  
} 

//###############################���жϷ������á�####################################
//����NVIC 
//NVIC_PreemptionPriority:��ռ���ȼ�
//NVIC_SubPriority       :��Ӧ���ȼ�
//NVIC_Channel           :�жϱ��
//NVIC_Group             :�жϷ��� 0~4
//ע�����ȼ����ܳ����趨����ķ�Χ!����������벻���Ĵ���
//�黮��:
//��0:	0λ��ռ���ȼ�,4λ��Ӧ���ȼ�
//��1:	1λ��ռ���ȼ�,3λ��Ӧ���ȼ�
//��2:	2λ��ռ���ȼ�,2λ��Ӧ���ȼ�
//��3:	3λ��ռ���ȼ�,1λ��Ӧ���ȼ�
//��4:	4λ��ռ���ȼ�,0λ��Ӧ���ȼ�
//NVIC_SubPriority��NVIC_PreemptionPriority��ԭ����,��ֵԽС,Խ����
void System_NVIC_Init(u8 NVIC_PreemptionPriority,u8 NVIC_SubPriority,u8 NVIC_Channel,u8 NVIC_Group)	 
{ 
	u32 temp;	
	u8 IPRADDR=NVIC_Channel/4;  //ÿ��ֻ�ܴ�4��,�õ����ַ 
	u8 IPROFFSET=NVIC_Channel%4;//�����ڵ�ƫ��
	IPROFFSET=IPROFFSET*8+4;    //�õ�ƫ�Ƶ�ȷ��λ��
	System_NVIC_PriorityGroupConfig(NVIC_Group);//���÷���
	temp=NVIC_PreemptionPriority<<(4-NVIC_Group);	  
	temp|=NVIC_SubPriority&(0x0f>>NVIC_Group);
	temp&=0xf;//ȡ����λ

	if(NVIC_Channel<32)NVIC->ISER[0]|=1<<NVIC_Channel;//ʹ���ж�λ(Ҫ����Ļ�,�෴������OK)
	else NVIC->ISER[1]|=1<<(NVIC_Channel-32);    
	NVIC->IPR[IPRADDR]|=temp<<IPROFFSET;//������Ӧ���ȼ����������ȼ�   	    	  				   
} 

//###############################���ⲿ�жϿ������á�####################################
//�ⲿ�ж����ú���
//ֻ���GPIOA~G;������PVD,RTC��USB����������
//����:GPIOx:0~6,����GPIOA~G;Pinx:��Ҫʹ�ܵ�λ;TRIM:����ģʽ,1,������;2,�Ͻ���;3�������ƽ����
//�ú���һ��ֻ������1��IO��,���IO��,���ε���
//�ú������Զ�������Ӧ�ж�,�Լ�������
void System_EXTI_Init(u8 GPIOx,u8 Pinx,u8 TRIM) 
{
	u8 EXTADDR;
	u8 EXTOFFSET;
	EXTADDR=Pinx/4;//�õ��жϼĴ�����ı��
	EXTOFFSET=(Pinx%4)*4;

	RCC->APB2ENR|=0x01;//ʹ��io����ʱ��
	AFIO->EXTICR[EXTADDR]|=GPIOx<<EXTOFFSET;//EXTI.Pinxӳ�䵽GPIOx.Pinx
	
	//�Զ�����
	EXTI->IMR|=1<<Pinx;//  ����line Pinx�ϵ��ж�
	//EXTI->EMR|=1<<BITx;//������line Pinx�ϵ��¼� (������������,��Ӳ�����ǿ��Ե�,��������������ʱ���޷������ж�!)
 	if(TRIM&0x01)EXTI->FTSR|=1<<Pinx;//line BITx���¼��½��ش���
	if(TRIM&0x02)EXTI->RTSR|=1<<Pinx;//line BITx���¼��������ش���
}

//###############################��ʱ�ӳ�ʼ����####################################
void Stm32_Clock_Init(void)
{
	unsigned char temp=0;   
	MYRCC_DeInit();		  //��λ������������
	RCC->CR|=0x00010000;  //�ⲿ����ʱ��ʹ��HSEON
	while(!(RCC->CR>>17));//�ȴ��ⲿʱ�Ӿ���
	RCC->CFGR=0X00000400; //APB1=DIV2;APB2=DIV1;AHB=DIV1;
	RCC->CFGR|=(SYS_PLL-2)<<18;   //����PLLֵ 
	RCC->CFGR|=1<<16;	  //PLLSRC ON 
	FLASH->ACR|=0x32;	  //FLASH 2����ʱ����

	RCC->CR|=0x01000000;  //PLLON
	while(!(RCC->CR>>25));//�ȴ�PLL����
	RCC->CFGR|=0x00000002;//PLL��Ϊϵͳʱ��	 
	while(temp!=0x02)     //�ȴ�PLL��Ϊϵͳʱ�����óɹ�
	{   
		temp=RCC->CFGR>>2;
		temp&=0x03;
	}    
}		    



















