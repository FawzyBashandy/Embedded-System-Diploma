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
    fgets(ptr->m_name,50,stdin);
    printf("\nEnter roll number : ");
    scanf("%d",&ptr->m_roll);
    printf("\nEnter marks number : ");
    scanf("%d",&ptr->m_marks);
}
void student_Print(struct Sstudent *ptr)
{
    printf("Displaying %s Information: \n",&ptr->m_name);
    printf("Name: %s",ptr->m_name);
    printf("Roll: %d",ptr->m_roll);
    printf("Marks: %f",ptr->m_marks);
}