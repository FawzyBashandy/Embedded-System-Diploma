//Prepared by Fawzy Mohamed
#include "Platform_Types.h"
extern uint32 _E_Text;
extern uint32 _S_Data;
extern uint32 _E_Data;
extern uint32 _S_Bss;
extern uint32 _E_Bss;
extern void main (void);

void _Reset ();
void NMI_Handler() __attribute__((weak,alias("_Default_Handler")));;
void Hard_Fault_Handler() __attribute__((weak,alias("_Default_Handler")));;
void Bus_Fault_Handler() __attribute__((weak,alias("_Default_Handler")));;
void _Default_Handler ();

static uint32 Stack[256]; //Static here to limit scopt of Stack array to be within Startup.c ONLY

void (* const G_P_Fn[])() __attribute__((section("._Vectors"))) =
{
	(void (*) ())((uint32)Stack + sizeof(Stack)), //Address of The last element in Stack array ((stack + sizeof(stack)))
	_Reset,
	NMI_Handler,
	Bus_Fault_Handler,
	NMI_Handler,
	_Default_Handler,
	_Default_Handler
};





void _Reset()
{
	//Copy Data section from ROM To RAM
	uint32 DataSize =(uint32)&_E_Data - (uint32)&_S_Data;
	uint32 Bss_Size =(uint32)&_E_Bss - (uint32)&_E_Bss;
	vuint8 * P_Src = (vuint8 *)&_E_Text;
	vuint8 * P_Dst = (vuint8 *)&_S_Data;
	for(uint32 i=0 ; i<DataSize ; i++)
	{
		P_Dst[i]=(uint8)P_Src[i];
	}
	//Init bss with zeros in RAM
	P_Dst=(uint8 *)&_S_Bss;
	for(uint32 i=0 ; i<Bss_Size ; i++)
	{
		P_Dst[i]=(uint8)0;
	}
	//Jump To main :)
	main();
}
void _Default_Handler()
{
	_Reset();
}





