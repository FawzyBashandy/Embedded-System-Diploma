#include "../inc/FIFO.h"

eFIFO_Status_t FIFO_Init()
{
    Students_FIFO = (sFIFO_t *)malloc(sizeof(sFIFO_t));
    //Check if memory allocated
    if(!Students_FIFO)
    {
        return FIFO_Error;
    }
    //Initialize the members
    Students_FIFO->Length = FIFO_Capacity;
    Students_FIFO->Count = 0;
    Students_FIFO->Base = NULL;
    Students_FIFO->Head = NULL;
    Students_FIFO->Tail = NULL;
    
    return FIFO_No_Error;
}
eFIFO_Status_t FIFO_Enqueue(sStudent_t * New_Student)
{   
    SNode_t * New_Student_Node = (SNode_t *)malloc(sizeof(SNode_t));
    New_Student_Node->StudentData = New_Student;
    //Check if Node is valid and there's a fifo
    if(!New_Student || !Students_FIFO)
    {
        free(New_Student_Node);
        return FIFO_Error;
    }
    //Check if FIFO is full
    else if(FIFO_Full == FIFO_Is_Full())
    {
        free(New_Student_Node);
        return FIFO_Full;
    }
    else if(!New_Student || !New_Student_Node)
    {
        printf("[ERROR] : Memory Allocation Failed !\n");
        free(New_Student_Node);
        return FIFO_Error;
    }
    if(!Students_FIFO->Base)
    {
        Students_FIFO->Base = Students_FIFO->Head = Students_FIFO->Tail = New_Student_Node;
    }
    else
    {
        Students_FIFO->Head->P_Next_Student = New_Student_Node;
        Students_FIFO->Head = New_Student_Node;
    }
    Students_FIFO->Count++;
    New_Student_Node->P_Next_Student = NULL;
    return FIFO_No_Error;
}
eFIFO_Status_t FIFO_Dequeue()
{
    SNode_t * Required_Node = Students_FIFO->Tail ;
    //Check if there's a fifo
    if (!Students_FIFO || !Students_FIFO->Head || !Students_FIFO->Tail)
    {
    return FIFO_Null;
    }
    //Check if FIFO is empty
    if(FIFO_Empty == FIFO_Is_Empty())
    {
        return FIFO_Empty;
    }
    Students_FIFO->Tail = Students_FIFO->Tail->P_Next_Student;
    free(Required_Node);
    return FIFO_No_Error;
}
eFIFO_Status_t FIFO_Search_Roll(uint32_t Roll_Number)
{
    SNode_t * Current_Student = Students_FIFO->Tail;
    while(Current_Student)
    {
        if(Roll_Number == Current_Student->StudentData->Roll_Number)
        {
            return Roll_Found;
        }
        Current_Student = Current_Student->P_Next_Student;
    }
}
eFIFO_Status_t FIFO_Is_Full()
{
    return (Students_FIFO->Count < Students_FIFO->Length)?FIFO_Not_Full:FIFO_Full; 
}
eFIFO_Status_t FIFO_Is_Empty()
{
    if(!Students_FIFO->Count)
    {
    return FIFO_Empty;
    }
    return FIFO_Not_Empty;
}