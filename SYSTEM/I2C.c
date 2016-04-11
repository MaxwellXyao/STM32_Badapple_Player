#include"delay.h"
#include"I2C.h"

//##############################【内部】#############################

//IIC内部操作函数
void I2C_Ack(I2C_HWM i2c_hw);					//IIC发送ACK信号
void I2C_NAck(I2C_HWM i2c_hw);					//IIC不发送ACK信号

//初始化IIC
void I2C_Port_Init(I2C_HWM i2c_hw)
{					     
	i2c_hw.I2C_HW_Init();
}

//产生IIC起始信号
void I2C_Start(I2C_HWM i2c_hw)
{
	i2c_hw.I2C_SDA(1);	  	  
	i2c_hw.I2C_SCL(1);
	delay_us(4);
 	i2c_hw.I2C_SDA(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	i2c_hw.I2C_SCL(0);//钳住I2C总线，准备发送或接收数据 
}	  
//产生IIC停止信号
void I2C_Stop(I2C_HWM i2c_hw)
{
	i2c_hw.I2C_SCL(0);
	i2c_hw.I2C_SDA(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	i2c_hw.I2C_SCL(1); 
	i2c_hw.I2C_SDA(1);//发送I2C总线结束信号
	delay_us(4);							   	
}
//等待应答信号到来
//返回值：1，接收应答失败
//        0，接收应答成功
u8 I2C_Wait_Ack(I2C_HWM i2c_hw)
{
	u8 ucErrTime=0;  
	i2c_hw.I2C_SDA(1);delay_us(1);	   
	i2c_hw.I2C_SCL(1);delay_us(1);
//	SDA_IN();      //SDA设置为输入	 
	while(i2c_hw.SDA_I())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			I2C_Stop(i2c_hw);
			return 1;
		}
	}
	i2c_hw.I2C_SCL(0);//时钟输出0 	   
	return 0;  
} 
//产生ACK应答
void I2C_Ack(I2C_HWM i2c_hw)
{
	i2c_hw.I2C_SCL(0);
	i2c_hw.I2C_SDA(0);
	delay_us(2);
	i2c_hw.I2C_SCL(1);
	delay_us(2);
	i2c_hw.I2C_SCL(0);
}
//不产生ACK应答		    
void I2C_NAck(I2C_HWM i2c_hw)
{
	i2c_hw.I2C_SCL(0);
	i2c_hw.I2C_SDA(1);
	delay_us(2);
	i2c_hw.I2C_SCL(1);
	delay_us(2);
	i2c_hw.I2C_SCL(0);
}					 				     
//IIC发送一个字节
//返回从机有无应答
//1，有应答
//0，无应答			  
void I2C_Send_Byte(I2C_HWM i2c_hw,u8 txd)
{                        
    u8 t;   	    
    i2c_hw.I2C_SCL(0);//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
        i2c_hw.I2C_SDA((txd&0x80)>>7);
        txd<<=1; 	  
		delay_us(2);   //对TEA5767这三个延时都是必须的
		i2c_hw.I2C_SCL(1);
		delay_us(2); 
		i2c_hw.I2C_SCL(0);	
		delay_us(2);
    }	 
} 	    
//读1个字节，ack=1时，发送ACK，ack=0，发送nACK   
u8 I2C_Read_Byte(I2C_HWM i2c_hw,u8 ack)
{
	u8 i,receive=0;
    for(i=0;i<8;i++ )
	{
        i2c_hw.I2C_SCL(0); 
        delay_us(2);
		i2c_hw.I2C_SCL(1);
        receive<<=1;
        if(i2c_hw.SDA_I())receive++;   
		delay_us(1); 
    }					 
    if (!ack)
        I2C_NAck(i2c_hw);//发送nACK
    else
        I2C_Ack(i2c_hw); //发送ACK   
    return receive;
}
