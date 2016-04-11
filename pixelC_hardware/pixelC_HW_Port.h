#ifndef PIXELC_HW_PORT_H
#define PIXELC_HW_PORT_H

#define bit_getH4(x) ((x&0xf0)>>4)
#define bit_getL4(x) (x&0x0f)

//#############################【常用】###############################

typedef enum _PIN_PXx{
	PA0=0x00,		
	PA1=0x01,
	PA2=0x02,
	PA3=0x03,
	PB12=0x1c,		
	PB13=0x1d,
	PB14=0x1e,
	PB15=0x1f	
}PIN_PXx; 	//引脚编号:
/*
	低4位：引脚bit（0~15）	
	高4位：寄存器名（A~G:0~6）
*/

typedef enum _MODE{
	OUTPUT=0,	 	//推挽输出，最大速度50MHz
	INPUT,	 		//上拉\下拉输入
	ADC_IN,			//使用ADC输入(ADC1，单次模式)
	PWM_OUT			//使用PWM输出
}PIN_MODE; 			//功能模式


//#############################【内置协议】###############################

//SPI2

//USART2


//#############################【API】###############################

void pixelC_HW_Port_PinInit(PIN_PXx PXx,PIN_MODE mode);		//初始化引脚（模式：OUTPUT，INPUT，ADC，PWM）
/*----------------------------------------------------
引脚电平控制:使用位带操作宏：
PAout(n)=1;
PBout(n)=0;
value1=PAin(n);
value2=PBin(n);
----------------------------------------------------*/
u16 pixelC_HW_Port_getADC(PIN_PXx PXx);		//获取引脚AD值
void pixelC_HW_Port_setPWM(PIN_PXx PXx,u16 ccr,u16 arr,u16 psc,u8 pwm_on);	//设置PWM值




#endif
