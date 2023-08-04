#include <stdio.h>
struct Sstudent
{
    char m_name[50];
    int m_roll;
    float m_marks;
};
void student_Read(struct Sstudent *ptr);
void student_Print(struct Sstudent *ptr);
// i will use pointers as they are readeable and faster
int main()
{
    struct Sstudent student1; 
    student_Read(&student1);
    student_Print(&student1);

}
void student_Read(struct Sstudent *ptr)
{
    printf("Please Enter Name : ");
    gets(ptr->m_name);
    printf("Enter roll number : ");
    scanf("%d",&ptr->m_roll);
    fflush(stdin);
    printf("Enter marks number : ");
    fflush(stdin);
    scanf("%f",&ptr->m_marks);
}
void student_Print(struct Sstudent *ptr)
{
    printf("______________________________________________\n\n");
    printf("Displaying %s Information: \n",&ptr->m_name);
    printf("Name: %s",ptr->m_name);
    printf("\nRoll: %d",ptr->m_roll);
    printf("\nMarks: %f",ptr->m_marks);
}