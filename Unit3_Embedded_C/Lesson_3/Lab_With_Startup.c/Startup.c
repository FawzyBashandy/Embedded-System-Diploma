#include "Platform_Types.h"
extern uint32 Stack_Top;
extern uint32 _E_Text;
extern uint32 _S_Data;
extern uint32 _E_Data;
extern uint32 _S_Bss;
extern uint32 _E_Bss;
extern void main (void);
void _Reset()
{
	//Copy Data section from ROM To RAM
	uint32 DataSize =(uint32)&_E_Data - (uint32)&_S_Data;
	uint32 Bss_Size =(uint32)&_E_Bss - (uint32)&_E_Bss;
	vuint8 * P_Src = (vuint8 *)&_E_Text;
	vuint8 * P_Dst = (vuint8 *)&_S_Data;
	for(int i=0 ; i<DataSize ; i++)
	{
		P_Dst[i]=(uint8)P_Src[i];
	}
	//Init bss with zeros in RAM
	P_Dst=(uint8 *)&_S_Bss;
	for(int i=0 ; i<Bss_Size ; i++)
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
void NMI_Handler() __attribute__((weak,alias("_Default_Handler")));;
void Hard_Fault_Handler() __attribute__((weak,alias("_Default_Handler")));;
void Bus_Fault_Handler() __attribute__((weak,alias("_Default_Handler")));;

uint32 Vectors[] __attribute__((section("._Vectors"))) =
{
	(uint32)&Stack_Top,
	(uint32)_Reset, //Name of function equivalent to address of first instruction in this function
	(uint32)NMI_Handler,
	(uint32)Bus_Fault_Handler,
	(uint32)_Default_Handler,
	(uint32)_Default_Handler,
	(uint32)_Default_Handler,
	(uint32)_Default_Handler
};



