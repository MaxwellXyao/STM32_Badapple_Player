#ifndef PIXELC_HARDWARE_INCLUDE_H
#define PIXELC_HARDWARE_INCLUDE_H

//###########################������ѡ��############################

/*----------------------------------------------------------------------		
	pixelC2		 ������8·GPIO��4·ADC��4·PWM��8·�ⲿ�жϣ�2·���ڣ�1·Ӳ��SPI������SD������FATFS����24c02�������3.3v��5v��ѹ��

��������IO�ڣ�������Դ����				
	PA0��GPIO���жϣ�PWM(TIM2)��ADC��
	PA1��GPIO���жϣ�PWM(TIM2)��ADC��
	PA2��GPIO���жϣ�PWM(TIM2)��ADC��UART2_TX��
	PA3��GPIO���жϣ�PWM(TIM2)��ADC��UART2_RX��
	PB12��GPIO���жϣ�
	PB13��GPIO���жϣ�SPI2_SCK��
	PB14��GPIO���жϣ�SPI2_MISO��
	PB15��GPIO���жϣ�SPI2_MOSI��
	PA9��System_UART1_TX��
	PA10��System_UART1_RX��

PS:	STM32F103C8T6	[	ROM:64k,RAM:20k		]
				
											
----------------------------------------------------------------------*/

//############################�����ؿ⡿############################
#include"stm32f10x_lib.h"

//------------------��system��
#include"system.h"						//ϵͳʹ��
#include"delay.h"						//��ʱ
#include"malloc.h"	    				//��̬�ڴ�


//------------------��pixelC_HW��
#include"pixelC_HW_flagLight.h"		   	//����ָʾ��
#include"pixelC_HW_Key.h"			   	//����
#include"pixelC_HW_OLED.h"			   	//OLEDӲ������
#include"pixelC_HW_Port.h"				//����IO�ӿ�
#include"pixelC_HW_24C02.h"			   	//����24c02
#include"pixelC_HW_SDcard.h"		   	//����SD��


//------------------��SOLGUI��
#include"SOLGUI_Include.h"			

//------------------��FATFS��
#include"ff.h"						  


//############################������ͷ�ļ���ӡ�############################
//#include "indclude.h"

#include"Badapple_player.h"				//��ƻ��������



//############################�����ù��ܷ�����############################
/*

//============��SOLGUI���ٲ���������============
��1���ַ����ĸ�ʽ�����:
SOLGUI_printf(0,0,F6X8,"helloworld!");

��2��ҳ���ܲ���:

	SOLGUI_Init(&index);			//��ʼ��

	while(1)
	{
		kv=pixelC_HW_Key_GetValue();	//��ֵ��ȡ
		SOLGUI_InputKey(kv);			//��ֵ����
		SOLGUI_Menu_PageStage();	 	//ǰ̨
		SOLGUI_Refresh();				//������Ļ
	}


��3��ҳ�洴��:
MENU_PAGE index;						//ҳ������
 __M_PAGE(index,"test",PAGE_NULL,{		//�귽ʽ����ҳ��
	//////////////��ӿؼ�//////////////
});

��3����ӿؼ�:
//---------------��ҳ����ơ�
SOLGUI_Cursor(u8 rowBorder_Top,u8 rowBorder_Bottom,u8 option_num);					//��꣨�ϱ߽��У��±߽��У�ѡ�������
//---------------��ѡ��ʽ�ؼ���
SOLGUI_Widget_GotoPage(u8 USN,MENU_PAGE *page);										//ҳ����ת
SOLGUI_Widget_Spin(u8 USN,const u8 *name,u8 type,double max,double min,void* value);//������ť
SOLGUI_Widget_OptionText(u8 USN,const u8* str,...);									//ѡ���ı���̫��������str���ڸǹ�������
SOLGUI_Widget_Button(u8 USN,const u8 *name,void (*func)(void));						//����
SOLGUI_Widget_Switch(u8 USN,const u8 *name,u32 *mem_value,u8 L_shift);				//�������أ�mem_value��һ���ⲿ����ķ���ʧ�Դ洢��������
SOLGUI_Widget_Edit(u8 USN,const u8 *name,u16 char_num,u8 *buf);						//�ı��༭����char_num���޸ĳ��ȣ�
//---------------������ʽ�ؼ���
SOLGUI_Widget_Text(u32 x0,u32 y0,u8 mode,const u8* str,...);										//���֣��ڸò�Ӧ�����������printf��
SOLGUI_Widget_Bar(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,s32 value,u8 mode);				//��
SOLGUI_Widget_Spectrum(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,u16 val_num,s32 value[]);	//��
SOLGUI_Widget_Oscillogram(u32 x0,u32 y0,u32 xsize,u32 ysize,s32 max,s32 min,WaveMemBlk *wmb);  		//����ʾ��Ҫͨ����̽���������ݸ���
SOLGUI_Widget_Picture(u32 x0,u32 y0,u32 xsize,u32 ysize,const u8 *pic,u32 x_len,u32 y_len,u8 mode); //ͼƬ	
//---------------��������
SOLGUI_Oscillogram_Probe(WaveMemBlk *wmb,s32 value);												//��̽��







//============��FATFS���ٲ���������============
��1������ȫ�ֱ�����
FATFS FatFs;   				//����ļ�ϵͳ��Ϣ
FIL file;	   				//����ļ���Ϣ

��2����ʼ��
while(SD_Init()){
	�޿�����;
}

��3������sd��(�൱��FATFS��ʼ��)
f_mount(SD_CARD,&FatFs);	//�ȹ���SD��

��4�����ö�д����
��1���������ļ�
f_open(&file,"test\temp.txt",FA_CREATE_NEW);    //�������ļ�
f_close(&file); 
��2���������ļ�׷��д
f_open(&file,(const TCHAR*)"test\temp.txt", FA_OPEN_EXISTING|FA_WRITE);   //д��ʽ���ļ�
f_lseek(&file,file.fsize);  								//�ļ�ָ���Ƶ�ĩβ
f_printf(&file,"%d\r\n",123); 								//��ǰ���д��һ����ʽ���ַ���(\r\n����)
f_puts((char *)buf,&file);  								//��ǰ��괦д���ַ������˴������(char *)����ת����
f_close(&file); 	
��3�����ļ��ж�����\�ַ���
��ע�⣡�����������建��bufʱҪ����Ϊ������ʽbuf[n]����Ҫ����Ϊָ��ʽ*buf��ָ�벻�����ڴ棬��ȥд���ݣ��������Ľ��డ����ѭ��������������
f_open(&file,(const TCHAR*)"test\temp.txt", FA_READ);   	//�Զ���ʽ���ļ����ַ���Ҫ��(const TCHAR*)ת������
f_read(&file,buf,128,&num);  								//���ļ��ڶ�128�ֽڸ���buf����\���飨&num�Ƕ�ȡ�ɹ��ĸ�����num�������ж��壬����ΪNULL!��
f_gets(buf,128,&file); 										//���ļ���ȡ�ַ�����β��'\0'����buf���飨����128���ַ�����\r\n�س����н�����
f_lseek(&file,5000);										//�ļ�ָ���Ƶ�5000���ֽں�
f_close(&file);
��4���ļ�����
f_sync(&file);      							//���̳�ϴ�����ڳ�ʱ��д������;���棩
f_unlink("test\temp.txt");   					//ɾ���ļ�
f_rename("test1\temp1.txt", "test2\temp2.txt");	//�������ļ���Ҳ���������ƶ��ļ���

-----------------------------------------*/


#endif
