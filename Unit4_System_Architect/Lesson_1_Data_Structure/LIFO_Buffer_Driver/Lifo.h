#ifndef LIFO_H_
#define LIFO_H_
#include <stdint.h>
#define Element_Size uint32_t //Modify this to modify the size of lifo's elements
//************************************
//***********Typedefs*****************
//************************************
typedef struct 
{
    uint32_t Length;
    uint32_t count;
    Element_Size * base;
    Element_Size * head;
}LIFO_buffer_t;

typedef enum
{
    LIFO_No_Error,
    LIFO_Empty,
    LIFO_Not_Empty,
    LIFO_Full,
    LIFO_Not_Full,
    LIFO_Null
}Buffer_Status;
//************************************
//***************LIFO APIS************
//************************************

Buffer_Status LIFO_Init(LIFO_buffer_t * LIFO , Element_Size * buffer , uint32_t Length);
Buffer_Status LIFO_Push(LIFO_buffer_t * LIFO , Element_Size Item);
Buffer_Status LIFO_Pop(LIFO_buffer_t * LIFO , Element_Size * Item);
Buffer_Status LIFO_Read_All(LIFO_buffer_t * LIFO);
Buffer_Status LIFO_Is_Full(LIFO_buffer_t * LIFO);
Buffer_Status LIFO_Is_Empty(LIFO_buffer_t * LIFO);

//************************************
//***********************************

#endif