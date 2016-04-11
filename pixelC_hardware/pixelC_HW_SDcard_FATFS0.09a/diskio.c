/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2012        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control module to the FatFs module with a defined API.        */
/*-----------------------------------------------------------------------*/

#include"diskio.h"		/* FatFs lower layer API */
#include"pixelC_Hardware_include.h"	/* Example: MMC/SDC contorl */

/* Definitions of physical drive number for each media */
#define SD_CARD 0 		//SDπ“‘ÿµΩ¬ﬂº≠…Ë±∏0


/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE drv				/* Physical drive nmuber (0..) */
)
{
	
	unsigned char res;

	switch (drv) {
	case SD_CARD :
		res=SD_Init();
		break;
	}
	
	if(res)return STA_NOINIT;
	else return 0;	
}



/*-----------------------------------------------------------------------*/
/* Get Disk Status                                                       */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE drv		/* Physical drive nmuber (0..) */
)
{
	return 0;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address (LBA) */
	BYTE count		/* Number of sectors to read (1..128) */
)
{
	unsigned char res=0;
	if (!count)return RES_PARERR;
	switch (drv) {
	case SD_CARD :
		res=SD_ReadDisk(buff,sector,count);
		break;
	}
	if(res==0x00)return RES_OK;
	else return RES_ERROR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE drv,			/* Physical drive nmuber (0..) */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address (LBA) */
	BYTE count			/* Number of sectors to write (1..128) */
)
{
	unsigned char res=0;
	if (!count)return RES_PARERR;
	switch (drv) {
	case SD_CARD :
		res=SD_WriteDisk((u8*)buff,sector,count);
		break;
	}
	if(res == 0x00)return RES_OK;
	else return RES_ERROR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE drv,		/* Physical drive nmuber (0..) */
	BYTE ctrl,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;
	if(drv==SD_CARD)
	{
		switch(ctrl)
		{
			case CTRL_SYNC:
				PAout(4)=0;
				if(SD_WaitReady()==0)res = RES_OK;
				else res = RES_ERROR;
				PAout(4)=1;
				break;
			case GET_SECTOR_SIZE:
				*(WORD*)buff = 512; res = RES_OK;
				break;
			case GET_BLOCK_SIZE:
				*(WORD*)buff = 8; res = RES_OK;
				break;
			case GET_SECTOR_COUNT:
				*(DWORD*)buff = SD_GetSectorCount();res = RES_OK;
				break;
			default:
				res = RES_PARERR;
				break;
		}
	}else res=RES_ERROR;

	return res;
}


//User defined function to give a current time to fatfs module */
//31-25: Year(0-127 org.1980), 24-21: Month(1-12), 20-16: Day(1-31) */
//15-11: Hour(0-23), 10-5: Minute(0-59), 4-0: Second(0-29 *2) */

DWORD get_fattime(void)
{
	return 0;
}


#endif




