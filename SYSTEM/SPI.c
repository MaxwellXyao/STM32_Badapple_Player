#include"delay.h"
#include"SPI.h"

u8 speed_m=0;

void SPI_Port_Init(SPI_HWM spi_hw)
{					     
	spi_hw.SPI_HW_Init();
}

u8 SPI_ReadWrite_Byte(SPI_HWM spi_hw,u8 data)   
{   
    u8 i=0;   
    u8 temp=0;
	spi_hw.SPI_SCLK(0);   
    for(i=0;i<8;i++)   
    {   
        if(data&0x80)spi_hw.SPI_MOSI(1);   
        else spi_hw.SPI_MOSI(0);   
        data<<=1;   
        spi_hw.SPI_SCLK(1);
		   
        if(speed_m==1)delay_us(HIGH_SPEED);
		else delay_us(LOW_SPEED);
		   
        temp<<=1;   
        if(spi_hw.MISO_READ())temp++; 
		  
		if(speed_m==1)delay_us(HIGH_SPEED);
		else delay_us(LOW_SPEED); 
		  
        spi_hw.SPI_SCLK(0);   
    }   
    return temp;   
}

void SPI_Speed_Set(SPI_HWM spi_hw,u8 speed)
{	
	spi_hw.speed_mode=speed;
	if(spi_hw.speed_mode>=1) speed_m=1;
	else	speed_m=0;	
}

