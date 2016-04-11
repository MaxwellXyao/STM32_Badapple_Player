#include"pixelC_Hardware_include.h"



//###########################�����塿##############################

static u8 Is_Key_R_Down(void)	{ 	return PBin(8); 	}
static u8 Is_Key_D_Down(void)	{ 	return PBin(9); 	}
static u8 Is_Key_L_Down(void)	{ 	return PBin(5); 	}
static u8 Is_Key_OK_Down(void)	{ 	return PBin(6); 	}
static u8 Is_Key_U_Down(void)	{ 	return PBin(7); 	}

static u8 Is_Key_BK_Down(void)	{ 	return PAin(13); 	}
static u8 Is_Key_A_Down(void)	{ 	return PBin(3); 	}
static u8 Is_Key_B_Down(void)	{ 	return PBin(4); 	}

static u8 Is_Key_1_Down(void)	{ 	return PAin(14); 	}
static u8 Is_Key_2_Down(void)	{ 	return PAin(15); 	}

KEY_T _Key_R={Is_Key_R_Down,0,0,0,KEY_R_S,KEY_R_L};
KEY_T _Key_D={Is_Key_D_Down,0,0,0,KEY_D_S,KEY_D_L};
KEY_T _Key_L={Is_Key_L_Down,0,0,0,KEY_L_S,KEY_L_L};
KEY_T _Key_OK={Is_Key_OK_Down,0,0,0,KEY_OK_S,KEY_OK_L};
KEY_T _Key_U={Is_Key_U_Down,0,0,0,KEY_U_S,KEY_U_L};
KEY_T _Key_BK={Is_Key_BK_Down,0,0,0,KEY_BK_S,KEY_BK_L};
KEY_T _Key_A={Is_Key_A_Down,0,0,0,KEY_A_S,KEY_A_L};
KEY_T _Key_B={Is_Key_B_Down,0,0,0,KEY_B_S,KEY_B_L};

KEY_T *Key[KEY_NUM]={
&_Key_R,
&_Key_D,
&_Key_L,
&_Key_OK,
&_Key_U,
&_Key_BK,

&_Key_A,
&_Key_B

};


KEY_T Switch_1={Is_Key_1_Down,0,0,0,KEY_NULL,KEY_NULL};
KEY_T Switch_2={Is_Key_2_Down,0,0,0,KEY_NULL,KEY_NULL};

//###########################���ڲ���##############################

static void pixelC_HW_Key_PinInit(void)				//Ӳ������
{
	RCC->APB2ENR |= 0x00000001; //����afioʱ�� 
	AFIO->MAPR = (0x00FFFFFF & AFIO->MAPR)|0x04000000;          //�ر�JTAG 

	RCC->APB2ENR|=1<<3|1<<2;    		//ʹ��PORTB,PORTAʱ��  
#if Key_R_Pin/8									
		Key_R_GPIOx->CRH&=~((u32)0xf<<((Key_R_Pin%8)*4));		
		Key_R_GPIOx->CRH|=(u32)0x8<<((Key_R_Pin%8)*4);
#else
		Key_R_GPIOx->CRL&=~((u32)0xf<<((Key_R_Pin%8)*4));
		Key_R_GPIOx->CRL|=(u32)0x8<<((Key_R_Pin%8)*4);
#endif

#if Key_D_Pin/8									
		Key_D_GPIOx->CRH&=~((u32)0xf<<((Key_D_Pin%8)*4));		
		Key_D_GPIOx->CRH|=(u32)0x8<<((Key_D_Pin%8)*4);
#else
		Key_D_GPIOx->CRL&=~((u32)0xf<<((Key_D_Pin%8)*4));
		Key_D_GPIOx->CRL|=(u32)0x8<<((Key_D_Pin%8)*4);
#endif

#if Key_L_Pin/8									
		Key_L_GPIOx->CRH&=~((u32)0xf<<((Key_L_Pin%8)*4));		
		Key_L_GPIOx->CRH|=(u32)0x8<<((Key_L_Pin%8)*4);
#else
		Key_L_GPIOx->CRL&=~((u32)0xf<<((Key_L_Pin%8)*4));
		Key_L_GPIOx->CRL|=(u32)0x8<<((Key_L_Pin%8)*4);
#endif

#if Key_OK_Pin/8									
		Key_OK_GPIOx->CRH&=~((u32)0xf<<((Key_OK_Pin%8)*4));		
		Key_OK_GPIOx->CRH|=(u32)0x8<<((Key_OK_Pin%8)*4);
#else
		Key_OK_GPIOx->CRL&=~((u32)0xf<<((Key_OK_Pin%8)*4));
		Key_OK_GPIOx->CRL|=(u32)0x8<<((Key_OK_Pin%8)*4);
#endif

#if Key_U_Pin/8									
		Key_U_GPIOx->CRH&=~((u32)0xf<<((Key_U_Pin%8)*4));		
		Key_U_GPIOx->CRH|=(u32)0x8<<((Key_U_Pin%8)*4);
#else
		Key_U_GPIOx->CRL&=~((u32)0xf<<((Key_U_Pin%8)*4));
		Key_U_GPIOx->CRL|=(u32)0x8<<((Key_U_Pin%8)*4);
#endif

#if Key_BK_Pin/8									
		Key_BK_GPIOx->CRH&=~((u32)0xf<<((Key_BK_Pin%8)*4));		
		Key_BK_GPIOx->CRH|=(u32)0x8<<((Key_BK_Pin%8)*4);
#else
		Key_BK_GPIOx->CRL&=~((u32)0xf<<((Key_BK_Pin%8)*4));
		Key_BK_GPIOx->CRL|=(u32)0x8<<((Key_BK_Pin%8)*4);
#endif

#if Key_A_Pin/8									
		Key_A_GPIOx->CRH&=~((u32)0xf<<((Key_A_Pin%8)*4));		
		Key_A_GPIOx->CRH|=(u32)0x8<<((Key_A_Pin%8)*4);
#else
		Key_A_GPIOx->CRL&=~((u32)0xf<<((Key_A_Pin%8)*4));
		Key_A_GPIOx->CRL|=(u32)0x8<<((Key_A_Pin%8)*4);
#endif

#if Key_B_Pin/8									
		Key_B_GPIOx->CRH&=~((u32)0xf<<((Key_B_Pin%8)*4));		
		Key_B_GPIOx->CRH|=(u32)0x8<<((Key_B_Pin%8)*4);
#else
		Key_B_GPIOx->CRL&=~((u32)0xf<<((Key_B_Pin%8)*4));
		Key_B_GPIOx->CRL|=(u32)0x8<<((Key_B_Pin%8)*4);
#endif

#if Switch_1_Pin/8									
		Switch_1_GPIOx->CRH&=~((u32)0xf<<((Switch_1_Pin%8)*4));		
		Switch_1_GPIOx->CRH|=(u32)0x8<<((Switch_1_Pin%8)*4);
#else
		Switch_1_GPIOx->CRL&=~((u32)0xf<<((Switch_1_Pin%8)*4));
		Switch_1_GPIOx->CRL|=(u32)0x8<<((Switch_1_Pin%8)*4);
#endif

#if Switch_2_Pin/8									
		Switch_2_GPIOx->CRH&=~((u32)0xf<<((Switch_2_Pin%8)*4));		
		Switch_2_GPIOx->CRH|=(u32)0x8<<((Switch_2_Pin%8)*4);
#else
		Switch_2_GPIOx->CRL&=~((u32)0xf<<((Switch_2_Pin%8)*4));
		Switch_2_GPIOx->CRL|=(u32)0x8<<((Switch_2_Pin%8)*4);
#endif	
}

void pixelC_HW_Key_Init(void)						//����ɨ���ʼ��
{
	 pixelC_HW_Key_PinInit();
}

static void KeyRead(KEY_T *key) 							   //����ĳ��̰����㷨���������жϣ�
{ 
    unsigned char ReadData=key->Is_Key_Down()^1;		   
    key->Trg=ReadData&(ReadData^key->Cont);      
    key->Cont=ReadData;                    
}

//###########################��API��##############################

u8 pixelC_HW_Key_GetValue(void)		
{
	static u8 key_value=0;
	u8 i=0;
	key_value=KEY_NULL;
	for(i=0;i<KEY_NUM;i++)
	{
		KeyRead(Key[i]); 						//��ȡ��ֵ
		if(Key[i]->Trg==1)
		{
			key_value=Key[i]->S_Value;			//���ض̰�
		}
		if (Key[i]->Cont==1)
	    { 
	         Key[i]->fliter_cont++;       		
	         if(Key[i]->fliter_cont>Long_Press_Time) 
	         { 
	             Key[i]->fliter_cont=0;
				 key_value=Key[i]->L_Value;  	//���س���	  
	         }        
	    }
		if(Key[i]->Cont==0&&Key[i]->Trg==0) 
		{
		 	Key[i]->fliter_cont=0;
		} 
	}
	return(key_value);		
}

u8 pixelC_HW_Switch_GetValue(void)
{
	KeyRead(&Switch_1);
	KeyRead(&Switch_2);
	return (Switch_2.Cont*2+Switch_1.Cont);	
}
