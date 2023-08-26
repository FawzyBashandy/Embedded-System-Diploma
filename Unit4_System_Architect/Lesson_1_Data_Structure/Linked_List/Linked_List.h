#ifndef Linked_List_H_
#define Linked_List_H_
#include <stdint.h>
#include <stdio.h>
#define Dscanf(...) scanf(__VA_ARGS__);\
                    getchar() 
//Structure
typedef struct SStudent SStudent;
struct SStudent
{
    struct
    {
        uint8_t S_Name[40];
        uint32_t ID;
        float Height;
    }Student_Info;
    SStudent * PNextStudent;
};
typedef struct SStudent SStudent;
//APIs
void Fill_Student_Info (SStudent *Student);
void Add_Student ();
void Remove_Student();
uint32_t List_Length_Iterative();
uint32_t List_Length_Recursive();
void GetNth(uint32_t Index);
void GetNth_From_End(uint32_t Index);
void Get_Middle();
void List_Reverse();
void View_Students();
void Delete_All();


#endif