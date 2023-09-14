#include "../inc/Student_Management_System.h"

int main ()
{
    uint8_t Choice;
    FIFO_Init();
    printf("Welcome to the Student Management System\n");
    while(1)
    {
        Introduce_Program();
        printf("Enter you Choice to preform the Task : ");
        scanf("%d",&Choice);
        switch(Choice)
        {
            case 1 :
            {
                Add_Student();
                Number_of_Students();
                break;
            }
            case 2 :
            {
                Add_Student_File();
                Number_of_Students();
                break;
            }
            case 3 :
            {
                Get_Student(Roll_Search);
                break;
            }
            case 4 :
            {
                Get_Student(Name_Search);
                break;
            }
            case 5 :
            {
                Get_Student(Course_Search);
                break;
            }
            case 6 :
            {
                Number_of_Students();
                break;
            }
            case 7 :
            {
                Delete_Student();
                break;
            }
            case 8 :
            {
                Update_Student();
                break;
            }
            case 9 :
            {
                Print_All_Students();
                break;
            }
            case 10 :
            {
                return 1;
            }
            default :
            {
                printf("Invalid Choice ! try again ..");
            }
        }
        printf("\nPress any key to continue ...\n");\
        getch();
    }
}