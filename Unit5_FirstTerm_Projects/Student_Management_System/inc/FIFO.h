#ifndef FIFO_H_
#define FIFO_H_
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <conio.h>
#define FIFO_Capacity 50
#define Courses_Number 5

//####################
//######FIFO typdefs#####
//####################

typedef struct 
{
    uint8_t First_Name[40];
    uint8_t Last_Name[40];
    uint32_t Roll_Number;
    float Student_GPA ;
    uint8_t Registered_Courses[Courses_Number];    
}sStudent_t;

typedef struct Snode
{
    sStudent_t * StudentData;
    struct Snode * P_Next_Student;
    
}SNode_t;

typedef struct
{
    uint32_t Length;
    uint32_t Count;
    SNode_t * Head;
    SNode_t * Tail;
    SNode_t * Base;
}sFIFO_t;

typedef enum
{
    FIFO_Null,
    FIFO_Error,
    FIFO_No_Error,
    FIFO_Full,
    FIFO_Not_Full,
    FIFO_Empty,
    FIFO_Not_Empty,
    Roll_Found,
    Allocation_Failed
}eFIFO_Status_t;

typedef enum
{
    Roll_Search,
    Name_Search,
    Course_Search
}Search_status;

sFIFO_t * Students_FIFO;

//####################
//######FIFO Apis#####
//####################
eFIFO_Status_t FIFO_Init();
eFIFO_Status_t FIFO_Enqueue(sStudent_t * New_Student);
eFIFO_Status_t FIFO_Dequeue();
eFIFO_Status_t FIFO_Search_Roll(uint32_t Roll_Number);
eFIFO_Status_t FIFO_Search_Name(uint8_t Name[]);
eFIFO_Status_t FIFO_Search_Course(uint8_t Course[]);
eFIFO_Status_t FIFO_Read_All();
eFIFO_Status_t FIFO_Is_Full();
eFIFO_Status_t FIFO_Is_Empty();

#endif
