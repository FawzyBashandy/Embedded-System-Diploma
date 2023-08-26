#include "Linked_List.h"
#include <stdio.h>
#include <stdlib.h>
extern SStudent * gpFirstStudent;
void Fill_Student_Info (SStudent *Student)
{
    uint8_t temp[40];
    printf("Enter Student Name : ");
    fgets(Student->Student_Info.S_Name, sizeof(Student->Student_Info.S_Name), stdin);
    printf("Enter Student ID : ");
    Dscanf("%d",&(Student->Student_Info.ID));
    printf("Enter Student Height : ");
    Dscanf("%g",&(Student->Student_Info.Height));
}
void Add_Student ()
{
    SStudent * Student = (SStudent *)malloc(sizeof(SStudent));
    SStudent * CurrentStudent =gpFirstStudent;
    if(!gpFirstStudent)
    {
        gpFirstStudent = Student;
    }
    else
    {
        while(CurrentStudent->PNextStudent)
        {
            CurrentStudent = CurrentStudent->PNextStudent;
        }
        CurrentStudent->PNextStudent = Student;
    }
    Student->PNextStudent = NULL;

    Fill_Student_Info(Student);

}
void Remove_Student()
{
    SStudent * Selected_Student , * Previous_Student;
    uint32_t Selected_ID;
    if(!gpFirstStudent)
    {
        printf("The List is Empty!!\n");
        return;
    }
    Selected_Student = gpFirstStudent;
    Previous_Student = NULL;
    printf("Enter The student ID that you want to Remove : ");
    Dscanf("%d",&Selected_ID);
    while(Selected_Student)
    {
        if(Selected_Student->Student_Info.ID == Selected_ID)
        {
            if(!Previous_Student)
            {
                gpFirstStudent = Selected_Student->PNextStudent;            }
            else
            {
                Previous_Student->PNextStudent = Selected_Student->PNextStudent;
            }
            printf("Student Removed Succesfully !!\n");
            free(Selected_Student);
            return;
        }
        Previous_Student = Selected_Student;
        Selected_Student = Selected_Student->PNextStudent;
    }
    printf("Error : Student isn't in the list !\n");
}
uint32_t List_Length_Iterative()
{
    uint32_t Counter = 0;
    SStudent * CurrentStudent = gpFirstStudent;
    while(CurrentStudent)
    {
        Counter++;
        CurrentStudent = CurrentStudent->PNextStudent;
    }
    return Counter;
}
void GetNth_From_End(uint32_t Index)
{
    uint32_t temp = List_Length_Iterative();
    if((Index + 1) > temp)
    {
    printf("Error : Index Out of Bounds !!\n");
    return;
    }
    temp = temp - Index - 1; //Index from The start
    GetNth(temp);
}
void Get_Middle()
{
    uint32_t temp = List_Length_Iterative()/2; //Index of the middle student
    GetNth(temp);
}
void List_Reverse()
{
    if(!gpFirstStudent || !gpFirstStudent->PNextStudent)
    {
        printf("Error : Nothing To Reverse or There's only one Student in the list\n");
        return;    
    }
    SStudent * Reference_Node = gpFirstStudent->PNextStudent ,*Previous_Node = gpFirstStudent, * Current_Node = gpFirstStudent->PNextStudent;
    uint8_t flag;
    while(Current_Node->PNextStudent)
    {
        Reference_Node = Current_Node->PNextStudent;
        Current_Node->PNextStudent = Previous_Node;
        Previous_Node = Current_Node;
        Current_Node = Reference_Node;
        if(!Current_Node->PNextStudent)
        {
            gpFirstStudent->PNextStudent = NULL;
            gpFirstStudent = Current_Node;
            Current_Node ->PNextStudent = Previous_Node;
            break;
        }
    }
    printf("The list is Reversed Successfuly !\n");
}
void GetNth(uint32_t Index)
{
    SStudent * CurrentStudent = gpFirstStudent;
    uint32_t i=0;
    if(!gpFirstStudent)
    printf("Error : List is Empty !!\n");
    if((Index + 1) > List_Length_Iterative())
    printf("Error : Index Out of Bounds !!\n");
    else
    {
        for(; i<Index ; i++)
        CurrentStudent=CurrentStudent->PNextStudent;
        printf("Student Found Successfully :\n");
        printf("Student Name  : %sStudent ID : %d\nStudent Height %f\n",CurrentStudent->Student_Info.S_Name , CurrentStudent ->Student_Info.ID , CurrentStudent ->Student_Info.Height);
    }
}
uint32_t List_Length_Recursive(SStudent * Head)
{
    if(Head)
    {
        return 1 + List_Length_Recursive(Head->PNextStudent);
    }
    return 0;
}
void View_Students()
{
    uint32_t counter = 1;
    SStudent * Current_Student = gpFirstStudent;
    if(!Current_Student)
    {
        printf("List Is Empty !!\n");
    }
    else
    {
        while(Current_Student)
        {
            printf("Student Number %d :\n",counter);
            printf("Student Name  : %sStudent ID : %d\nStudent Height %f\n",Current_Student->Student_Info.S_Name , Current_Student ->Student_Info.ID , Current_Student ->Student_Info.Height);
            printf("---------------------------------------------\n");
            Current_Student = Current_Student->PNextStudent;
            counter++;
        }
    }
}
void Delete_All()
{
    SStudent * Current_Student = gpFirstStudent , *Remove_Student = gpFirstStudent;
    if(!Current_Student)
    {
        printf("List Is Already Empty !!\n");
        return;
    }
    gpFirstStudent = NULL;
    while(Current_Student)
    {
        Current_Student=Current_Student->PNextStudent;
        free(Remove_Student);
        Remove_Student = Current_Student;
    }
    printf("List Deleted !!\n");
}