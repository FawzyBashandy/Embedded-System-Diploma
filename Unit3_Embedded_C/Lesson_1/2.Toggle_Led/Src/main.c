#include "Platform_Types.h"
#define RCC_BASE		0x40021000
#define GPIOA_BASE		0x40010800
#define APB2ENR_OFFSET 	0x18
#define CRH_OFFSET		0x04
#define	ODR_OFFSET		0x0C
#define APB2ENR_R		*(vuint32 *)(RCC_BASE+APB2ENR_OFFSET)
#define CRH_R			*(vuint32 *)(GPIOA_BASE+CRH_OFFSET)


typedef union
{
	vuint32 All_Bits;
	struct{
		vuint32 Reserved:13;
		vuint32 Pin_13	:1;
	}Pin;
}R_ODR_t;


int main(void)
{
    volatile R_ODR_t *ODR_R=(volatile R_ODR_t *)(GPIOA_BASE+ODR_OFFSET);
	APB2ENR_R|=(1<<2);
	CRH_R=(CRH_R&0xFF0FFFFF)+0x00200000;



	for(;;)
	{
		ODR_R->Pin.Pin_13=1;
		for(uint32 i=0;i<5000;i++);//Arbitary Delay
		ODR_R->Pin.Pin_13=0;
		for(uint32 i=0;i<5000;i++);//Arbitary Delay
	}
}
