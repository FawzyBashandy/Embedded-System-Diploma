#include <stdint.h>

extern uint32_t Stack_Top , _S_DATA , _E_DATA , _S_BSS , _E_BSS , _E_RODATA ;
extern int main ();
void Reset_Handler();

void NMI_Handler() __attribute__((weak,alias ("Default_Handler")));;
void Hard_Fault_Handler() __attribute__((weak,alias ("Default_Handler")));;
void Memory_Management_Handler() __attribute__((weak,alias ("Default_Handler")));;
void Bus_Fault_Handler() __attribute__((weak,alias ("Default_Handler")));;
void Usage_Fault_Handler() __attribute__((weak,alias ("Default_Handler")));;

void (* const Vectors[]) () __attribute__((section(".vectors"))) =
{
    (void (*) ())&Stack_Top,
    Reset_Handler,
    NMI_Handler,
    Hard_Fault_Handler,
    Memory_Management_Handler,
    Bus_Fault_Handler,
    Usage_Fault_Handler
};
void DATA_Section_Copying()
{
    uint32_t i , DataSize = (uint8_t *)(&_E_DATA) - (uint8_t *)(&_S_DATA) ; //Size in bytes 
    uint8_t * P_Src = (uint8_t *)(&_E_RODATA);
    uint8_t * P_Dst = (uint8_t *)(&_S_DATA);
    for( i = 0 ; i < DataSize ; i++)
    {
        *((uint8_t *)P_Dst++) = *((uint8_t *)P_Src++);
    }
}
void BSS_Section_Init()
{
    uint32_t i , BssSize = (uint8_t *)(&_E_BSS) - (uint8_t *)(&_S_BSS) ; //Size in bytes 
    uint8_t * P_Dst = (uint8_t *)(&_S_BSS);
    for( i = 0 ; i < BssSize ; i++)
    *((uint8_t *)P_Dst++) = (uint8_t)0;
}


void Reset_Handler()
{
    DATA_Section_Copying();
    BSS_Section_Init();
    //Jump to main
    main();
}
void Default_Handler()
{
    Reset_Handler();
}
