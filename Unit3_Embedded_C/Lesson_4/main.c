#include "Platform_Types.h"
#define SYSCTL_RCGC2_R		*(vuint32 *)((vuint32*)(0x400FE108))
#define GPIO_PORTF_DATA_R	*(vuint32 *)((vuint32*)(0x400253FC))
#define GPIO_PORTF_DIR_R	*(vuint32 *)((vuint32*)(0x40025400))
#define GPIO_PORTF_DEN_R	*(vuint32 *)((vuint32*)(0x4002551C))

void main(void)
{
	uint32 delay;
	SYSCTL_RCGC2_R |= 0x20; //Enable Clock for GPIOF
	for(delay =0 ; delay <300000 ; delay++); //Delay for clock to stableize
	GPIO_PORTF_DEN_R |=(1<<3);	//PF3 Is digital pin
	GPIO_PORTF_DIR_R |=(1<<3);	//PF3 Is Output
	while(1)
	{
		GPIO_PORTF_DATA_R |=(1<<3); //Output High
		for(delay =0 ; delay <3000 ; delay++); //Delay
		GPIO_PORTF_DATA_R &=~(1<<3);//Output Low
		for(delay =0 ; delay <3000 ; delay++);
	}
	
}