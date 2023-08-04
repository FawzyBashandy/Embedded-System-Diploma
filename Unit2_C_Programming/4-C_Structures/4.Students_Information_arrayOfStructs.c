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
    struct Sstudent students[10];
    for(int i=0;i<10;i++)
    {
        student_Read(&students[i]);
    }
    for(int i=0;i<10;i++)
    {
        student_Print(&students[i]);
    }



}
void student_Read(struct Sstudent *ptr)
{
    printf("Please Enter Name : ");
    fflush(stdin);
    scanf("%s",&ptr->m_name);
    fflush(stdin);
    printf("Enter roll number : ");
    scanf("%d",&ptr->m_roll);
    fflush(stdin);
    printf("Enter marks number : ");
    scanf("%f",&ptr->m_marks);
    fflush(stdin);
}
void student_Print(struct Sstudent *ptr)
{
    printf("\nDisplaying %s Information: \n",&ptr->m_name);
    printf("Name: %s\n",ptr->m_name);
    printf("Roll: %d\n",ptr->m_roll);
    printf("Marks: %f\n",ptr->m_marks);
}