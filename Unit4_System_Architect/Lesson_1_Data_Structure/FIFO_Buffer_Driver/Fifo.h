#ifndef FIFO_H_
#define FIFO_H_
#include <stdint.h>

#define Elements_type uint32_t
//####################
//######Typedefs######
//####################
typedef struct 
{
	Elements_type Length;
	Elements_type Count;
	Elements_type * Base;
	Elements_type * Head;
	Elements_type * Tail;
}FIFO_Buff_t;

typedef enum 
{
	FIFO_No_Error,
	FIFO_Null,
	FIFO_Full,
	FIFO_Not_Full,
	FIFO_Empty,
	FIFO_Not_Empty
}Buffer_Status;
//####################
//######FIFO Apis#####
//####################
Buffer_Status FIFO_Init(FIFO_Buff_t * FIFO , Elements_type * buff , uint32_t Length);
Buffer_Status FIFO_Enqueue(FIFO_Buff_t * FIFO , Elements_type item);
Buffer_Status FIFO_Dequeue(FIFO_Buff_t * FIFO , Elements_type * target);
Buffer_Status FIFO_Read_All(FIFO_Buff_t * FIFO);
Buffer_Status FIFO_Is_Full(FIFO_Buff_t * FIFO);
Buffer_Status FIFO_Is_Empty(FIFO_Buff_t * FIFO);

#endif