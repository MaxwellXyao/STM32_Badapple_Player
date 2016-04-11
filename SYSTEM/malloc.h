#ifndef MALLOC_H
#define MALLOC_H

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;	  
#ifndef NULL
	#define NULL 0
#endif


struct _m_mallco_dev			  	//�ڴ���������
{
	void (*init)();					//��ʼ��
	u8 (*perused)();		  	    //�ڴ�ʹ����
	u8 	*membase;					//�ڴ�� ����1��������ڴ�
	u16 *memmap; 					//�ڴ����״̬��
	u8  memrdy; 					//�ڴ�����Ƿ����
};
extern struct _m_mallco_dev mallco_dev;	 //��mallco.c���涨��


//#########################�������ò�����############################
#define MEM1_BLOCK_SIZE			32  	  						//�ڴ���СΪ32�ֽ�
#define MEM1_MAX_SIZE			10*1024  						//�������ڴ� 10K
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	//�ڴ���С
 
//############################��API��############################
//--------------------����ʼ����
void Mem_Init(void);						//�ڴ�����ʼ������
//--------------------��������ͷš�
void *Mem_malloc(u32 size);					//�ڴ����
void Mem_free(void *ptr);  					//�ڴ��ͷ�
//--------------------��������
u8 	 Mem_perused(void);						//����ڴ�ʹ���ʣ�0~100��
void *Mem_realloc(void *ptr,u32 size);		//���·����ڴ�
void Mem_memset(void *s,u8 c,u32 count);	//�����ڴ�
void Mem_memcpy(void *des,void *src,u32 n);	//�����ڴ�

/*---------------------------------------------------------------
ʹ�÷�����

1.�ṹ�������
{
	MEMTEST *test1=NULL;							  //��ֹҰָ��
	test1=(MEMTEST *)Mem_malloc(sizeof(MEMTEST));	  //�����ڴ�
	if(test1==NULL)	{	//����ʧ�ܲ���	}			  //����ʧ�ܲ���

	////////////////�������/////////////////////

	Mem_free(test1);							 	 //�ͷ��ڴ�
}

2.��̬���顣 array[X]
{
	char *array = NULL;								  //��ֹҰָ��
	array = (char *)Mem_malloc(X*sizeof(char));		  //XΪ���鳤��
	if(array==NULL)	{	//����ʧ�ܲ���	}			  //����ʧ�ܲ���

	////////////////�������/////////////////////
	//		ʹ��:*(array+2)��array[2]		   //
	/////////////////////////////////////////////

	Mem_free(array);							 	 //�ͷ��ڴ�
}
---------------------------------------------------------------*/


#endif













