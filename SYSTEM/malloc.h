#ifndef MALLOC_H
#define MALLOC_H

typedef unsigned long  u32;
typedef unsigned short u16;
typedef unsigned char  u8;	  
#ifndef NULL
	#define NULL 0
#endif


struct _m_mallco_dev			  	//内存管理控制器
{
	void (*init)();					//初始化
	u8 (*perused)();		  	    //内存使用率
	u8 	*membase;					//内存池 管理1个区域的内存
	u16 *memmap; 					//内存管理状态表
	u8  memrdy; 					//内存管理是否就绪
};
extern struct _m_mallco_dev mallco_dev;	 //在mallco.c里面定义


//#########################【可设置参数】############################
#define MEM1_BLOCK_SIZE			32  	  						//内存块大小为32字节
#define MEM1_MAX_SIZE			10*1024  						//最大管理内存 10K
#define MEM1_ALLOC_TABLE_SIZE	MEM1_MAX_SIZE/MEM1_BLOCK_SIZE 	//内存表大小
 
//############################【API】############################
//--------------------【初始化】
void Mem_Init(void);						//内存管理初始化函数
//--------------------【分配和释放】
void *Mem_malloc(u32 size);					//内存分配
void Mem_free(void *ptr);  					//内存释放
//--------------------【其他】
u8 	 Mem_perused(void);						//获得内存使用率（0~100）
void *Mem_realloc(void *ptr,u32 size);		//重新分配内存
void Mem_memset(void *s,u8 c,u32 count);	//设置内存
void Mem_memcpy(void *des,void *src,u32 n);	//复制内存

/*---------------------------------------------------------------
使用范例：

1.结构体变量。
{
	MEMTEST *test1=NULL;							  //防止野指针
	test1=(MEMTEST *)Mem_malloc(sizeof(MEMTEST));	  //申请内存
	if(test1==NULL)	{	//申请失败操作	}			  //申请失败操作

	////////////////程序代码/////////////////////

	Mem_free(test1);							 	 //释放内存
}

2.动态数组。 array[X]
{
	char *array = NULL;								  //防止野指针
	array = (char *)Mem_malloc(X*sizeof(char));		  //X为数组长度
	if(array==NULL)	{	//申请失败操作	}			  //申请失败操作

	////////////////程序代码/////////////////////
	//		使用:*(array+2)或array[2]		   //
	/////////////////////////////////////////////

	Mem_free(array);							 	 //释放内存
}
---------------------------------------------------------------*/


#endif













