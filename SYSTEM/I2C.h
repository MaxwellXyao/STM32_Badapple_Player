#ifndef I2C_H
#define I2C_H


typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;	  
#ifndef NULL
	#define NULL 0
#endif


//##############################��Ӳ����#############################
typedef struct __I2C_HWM{				//I2CӲ�������
	 void (*I2C_HW_Init)();				//Ӳ����ʼ������
	 void (*I2C_SCL)(u8);	//SCL�����������
	 void (*I2C_SDA)(u8);	//SDA�����������
	 unsigned char (*SDA_I)();		//SDA���Ŷ�ȡ����
}I2C_HWM;								

#define HIGH 1		      //�˴��ظ�����Ƭ�ؿ��еĵ�ƽ����
#define LOW  0



//##############################��API��##############################
//IIC���в�������
void I2C_Port_Init(I2C_HWM i2c_hw);           //��ʼ��IIC��IO��				 
void I2C_Start(I2C_HWM i2c_hw);				//����IIC��ʼ�ź� �ɹ��򷵻�1
void I2C_Stop(I2C_HWM i2c_hw);	  			//����IICֹͣ�ź�
void I2C_Send_Byte(I2C_HWM i2c_hw,u8 txd);			//IIC����һ���ֽ�
u8 I2C_Read_Byte(I2C_HWM i2c_hw,u8 ack);//IIC��ȡһ���ֽ�
u8 I2C_Wait_Ack(I2C_HWM i2c_hw); 				//IIC�ȴ�ACK�ź�

/*----------------------------------------------------------
��I2Cͨ�ÿ�˵����
1.�Ȱ���Ӳ�������ṹ�嶨���������
typedef struct __I2C_HWM{				//I2CӲ������ṹ��
	 void (*I2C_HW_Init)();				//Ӳ����ʼ������
	 void (*I2C_SCL)(u8);	//SCL�����������
	 void (*I2C_SDA)(u8);	//SDA�����������
	 u8 (*SDA_I)();			//SDA���Ŷ�ȡ����
}I2C_HWM;

2.ʹ��I2C�⺯��

PS��I2C_Send_Byte()��I2C_Wait_Ack()һ�����ã�
�磺
			I2C_Send_Byte();
			I2C_Wait_Ack(); 
----------------------------------------------------------*/

#endif
