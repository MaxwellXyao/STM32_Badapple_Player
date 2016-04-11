#ifndef PIXELC_HW_PORT_H
#define PIXELC_HW_PORT_H

#define bit_getH4(x) ((x&0xf0)>>4)
#define bit_getL4(x) (x&0x0f)

//#############################�����á�###############################

typedef enum _PIN_PXx{
	PA0=0x00,		
	PA1=0x01,
	PA2=0x02,
	PA3=0x03,
	PB12=0x1c,		
	PB13=0x1d,
	PB14=0x1e,
	PB15=0x1f	
}PIN_PXx; 	//���ű��:
/*
	��4λ������bit��0~15��	
	��4λ���Ĵ�������A~G:0~6��
*/

typedef enum _MODE{
	OUTPUT=0,	 	//�������������ٶ�50MHz
	INPUT,	 		//����\��������
	ADC_IN,			//ʹ��ADC����(ADC1������ģʽ)
	PWM_OUT			//ʹ��PWM���
}PIN_MODE; 			//����ģʽ


//#############################������Э�顿###############################

//SPI2

//USART2


//#############################��API��###############################

void pixelC_HW_Port_PinInit(PIN_PXx PXx,PIN_MODE mode);		//��ʼ�����ţ�ģʽ��OUTPUT��INPUT��ADC��PWM��
/*----------------------------------------------------
���ŵ�ƽ����:ʹ��λ�������꣺
PAout(n)=1;
PBout(n)=0;
value1=PAin(n);
value2=PBin(n);
----------------------------------------------------*/
u16 pixelC_HW_Port_getADC(PIN_PXx PXx);		//��ȡ����ADֵ
void pixelC_HW_Port_setPWM(PIN_PXx PXx,u16 ccr,u16 arr,u16 psc,u8 pwm_on);	//����PWMֵ




#endif
