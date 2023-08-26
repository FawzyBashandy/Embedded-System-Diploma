#include "Lifo.h"
#include <stdio.h>
Buffer_Status LIFO_Init(LIFO_buffer_t * LIFO , Element_Size * buffer , uint32_t Length)
{
    if(NULL == buffer)
    return LIFO_Null;
    LIFO->base = LIFO->head = buffer; //Initialize Both Head and base to Address of the buffer
    LIFO->Length = Length;
    LIFO->count = 0;
    return LIFO_No_Error;
}
Buffer_Status LIFO_Push(LIFO_buffer_t * LIFO , Element_Size Item)
{
    if(!LIFO->base || !LIFO->head || !LIFO) 
    return LIFO_Null;
    if(LIFO_Full == LIFO_Is_Full(LIFO) )
    return LIFO_Full;
    *(LIFO->head++) = Item; //Put item at head and increment it
    LIFO->count++;
    return LIFO_No_Error;
}
Buffer_Status LIFO_Pop(LIFO_buffer_t * LIFO , Element_Size * Item)
{
    if(!LIFO->base || !LIFO->head || !LIFO) 
    return LIFO_Null;
    if( LIFO_Empty == LIFO_Is_Empty(LIFO) )
    return LIFO_Empty;
    *Item = *(--LIFO->head); //Decrement Head to point to last pushed element 
    LIFO->count--;
    return LIFO_No_Error;
}
Buffer_Status LIFO_Read_All(LIFO_buffer_t * LIFO)
{
    if(!LIFO->base || !LIFO->head || !LIFO) 
    return LIFO_Null;
    if(LIFO_Empty == LIFO_Is_Empty(LIFO))
    return LIFO_Empty;
	printf("========== Items in buffer ========= \n");
    for(int i=0 ; i< LIFO->count ; i++)
    {
	printf("%d \n",LIFO->base[LIFO->count-i-1]);
    }
    return LIFO_No_Error;
}
Buffer_Status LIFO_Is_Full(LIFO_buffer_t * LIFO)
{
    if(!LIFO->base || !LIFO->head || !LIFO) 
    return LIFO_Null;
    if(LIFO->count == LIFO->Length)
    return LIFO_Full;
    else
    return LIFO_No_Error;
}
Buffer_Status LIFO_Is_Empty(LIFO_buffer_t * LIFO)
{
    if(!LIFO->base || !LIFO->head || !LIFO) 
    return LIFO_Null;
    if(!LIFO->count)
    return LIFO_Empty;
    else
    return LIFO_No_Error;
}