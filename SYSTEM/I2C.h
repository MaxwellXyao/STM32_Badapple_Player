#ifndef I2C_H
#define I2C_H


typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;	  
#ifndef NULL
	#define NULL 0
#endif


//##############################【硬件】#############################
typedef struct __I2C_HWM{				//I2C硬件管理块
	 void (*I2C_HW_Init)();				//硬件初始化函数
	 void (*I2C_SCL)(u8);	//SCL引脚输出函数
	 void (*I2C_SDA)(u8);	//SDA引脚输出函数
	 unsigned char (*SDA_I)();		//SDA引脚读取函数
}I2C_HWM;								

#define HIGH 1		      //此处重复定义片载库中的电平定义
#define LOW  0



//##############################【API】##############################
//IIC所有操作函数
void I2C_Port_Init(I2C_HWM i2c_hw);           //初始化IIC的IO口				 
void I2C_Start(I2C_HWM i2c_hw);				//发送IIC开始信号 成功则返回1
void I2C_Stop(I2C_HWM i2c_hw);	  			//发送IIC停止信号
void I2C_Send_Byte(I2C_HWM i2c_hw,u8 txd);			//IIC发送一个字节
u8 I2C_Read_Byte(I2C_HWM i2c_hw,u8 ack);//IIC读取一个字节
u8 I2C_Wait_Ack(I2C_HWM i2c_hw); 				//IIC等待ACK信号

/*----------------------------------------------------------
【I2C通用库说明】
1.先按照硬件管理块结构体定义各函数：
typedef struct __I2C_HWM{				//I2C硬件管理结构体
	 void (*I2C_HW_Init)();				//硬件初始化函数
	 void (*I2C_SCL)(u8);	//SCL引脚输出函数
	 void (*I2C_SDA)(u8);	//SDA引脚输出函数
	 u8 (*SDA_I)();			//SDA引脚读取函数
}I2C_HWM;

2.使用I2C库函数

PS：I2C_Send_Byte()和I2C_Wait_Ack()一般连用，
如：
			I2C_Send_Byte();
			I2C_Wait_Ack(); 
----------------------------------------------------------*/

#endif
