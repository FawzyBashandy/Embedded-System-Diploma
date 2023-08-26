#include "Fifo.h"
#include <stdio.h>

Buffer_Status FIFO_Init(FIFO_Buff_t * FIFO , Elements_type * buff , uint32_t Length)
{
	if(!buff)
		return FIFO_Null;
	FIFO->Base = FIFO->Head = FIFO->Tail = buff; //Initialize the three pointer to address of array(Static)
	FIFO->Length=Length;
	FIFO->Count=0;
	return FIFO_No_Error;
}
Buffer_Status FIFO_Enqueue(FIFO_Buff_t * FIFO , Elements_type item)
{
	if( !FIFO || !FIFO->Base)
		return FIFO_Null;
	if(FIFO_Full == FIFO_Is_Full(FIFO))
		return FIFO_Full;
	if(((FIFO->Count+1) == FIFO->Length))
	{
		*(FIFO->Head) = item ;
		FIFO->Head = FIFO->Base;
	}
	else
	{
		*(FIFO->Head++) = item;
	}
	FIFO->Count++;
	return FIFO_No_Error;
}
Buffer_Status FIFO_Dequeue(FIFO_Buff_t * FIFO , Elements_type * target)
{
	if( !FIFO || !FIFO->Base)
		return FIFO_Null;
	if(FIFO_Empty == FIFO_Is_Empty(FIFO))
		return FIFO_Empty;
	if((FIFO->Tail + 1) == (FIFO->Base + FIFO->Length))
	{
		*target = *(FIFO->Tail);
		FIFO->Tail = FIFO->Base;
	}
	else
	{
		*target = *(FIFO->Tail++);
	}
	FIFO->Count--;
	return FIFO_No_Error;
}
Buffer_Status FIFO_Read_All(FIFO_Buff_t * FIFO)
{
	if(!FIFO || !FIFO->Base)
		return FIFO_Null;
	if(FIFO_Empty == FIFO_Is_Empty(FIFO))
		return FIFO_Empty;
	
	printf("=============Items in Buffer ============\n");
	int i=0,temp;
	for( ;i<FIFO->Count;i++)
	{
		if((FIFO->Tail+i) >= (Elements_type *)(FIFO->Base + FIFO->Length))
		{
			temp = (FIFO->Count - (i + 1)) % FIFO->Length;
			printf("%d\n",FIFO->Base[temp]);
		}
		else
		{
		printf("%d\n",*(FIFO->Tail + i));
		}
	}
	return FIFO_No_Error;
}
Buffer_Status FIFO_Is_Full(FIFO_Buff_t * FIFO)
{
	return (FIFO->Count == FIFO->Length) ? FIFO_Full : FIFO_Not_Full;
}
Buffer_Status FIFO_Is_Empty(FIFO_Buff_t * FIFO)
{
	return (0 == FIFO->Count) ? FIFO_Empty : FIFO_Not_Empty;
}

