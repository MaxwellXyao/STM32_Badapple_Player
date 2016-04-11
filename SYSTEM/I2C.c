#include"delay.h"
#include"I2C.h"

//##############################���ڲ���#############################

//IIC�ڲ���������
void I2C_Ack(I2C_HWM i2c_hw);					//IIC����ACK�ź�
void I2C_NAck(I2C_HWM i2c_hw);					//IIC������ACK�ź�

//��ʼ��IIC
void I2C_Port_Init(I2C_HWM i2c_hw)
{					     
	i2c_hw.I2C_HW_Init();
}

//����IIC��ʼ�ź�
void I2C_Start(I2C_HWM i2c_hw)
{
	i2c_hw.I2C_SDA(1);	  	  
	i2c_hw.I2C_SCL(1);
	delay_us(4);
 	i2c_hw.I2C_SDA(0);//START:when CLK is high,DATA change form high to low 
	delay_us(4);
	i2c_hw.I2C_SCL(0);//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  
//����IICֹͣ�ź�
void I2C_Stop(I2C_HWM i2c_hw)
{
	i2c_hw.I2C_SCL(0);
	i2c_hw.I2C_SDA(0);//STOP:when CLK is high DATA change form low to high
 	delay_us(4);
	i2c_hw.I2C_SCL(1); 
	i2c_hw.I2C_SDA(1);//����I2C���߽����ź�
	delay_us(4);							   	
}
//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 I2C_Wait_Ack(I2C_HWM i2c_hw)
{
	u8 ucErrTime=0;  
	i2c_hw.I2C_SDA(1);delay_us(1);	   
	i2c_hw.I2C_SCL(1);delay_us(1);
//	SDA_IN();      //SDA����Ϊ����	 
	while(i2c_hw.SDA_I())
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			I2C_Stop(i2c_hw);
			return 1;
		}
	}
	i2c_hw.I2C_SCL(0);//ʱ�����0 	   
	return 0;  
} 
//����ACKӦ��
void I2C_Ack(I2C_HWM i2c_hw)
{
	i2c_hw.I2C_SCL(0);
	i2c_hw.I2C_SDA(0);
	delay_us(2);
	i2c_hw.I2C_SCL(1);
	delay_us(2);
	i2c_hw.I2C_SCL(0);
}
//������ACKӦ��		    
void I2C_NAck(I2C_HWM i2c_hw)
{
	i2c_hw.I2C_SCL(0);
	i2c_hw.I2C_SDA(1);
	delay_us(2);
	i2c_hw.I2C_SCL(1);
	delay_us(2);
	i2c_hw.I2C_SCL(0);
}					 				     
//IIC����һ���ֽ�
//���شӻ�����Ӧ��
//1����Ӧ��
//0����Ӧ��			  
void I2C_Send_Byte(I2C_HWM i2c_hw,u8 txd)
{                        
    u8 t;   	    
    i2c_hw.I2C_SCL(0);//����ʱ�ӿ�ʼ���ݴ���
    for(t=0;t<8;t++)
    {              
        i2c_hw.I2C_SDA((txd&0x80)>>7);
        txd<<=1; 	  
		delay_us(2);   //��TEA5767��������ʱ���Ǳ����
		i2c_hw.I2C_SCL(1);
		delay_us(2); 
		i2c_hw.I2C_SCL(0);	
		delay_us(2);
    }	 
} 	    
//��1���ֽڣ�ack=1ʱ������ACK��ack=0������nACK   
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
        I2C_NAck(i2c_hw);//����nACK
    else
        I2C_Ack(i2c_hw); //����ACK   
    return receive;
}
