#include <stdio.h>

struct ScomplexNumber
{
    float real;
    float imj;
}num1,num2,result;

struct ScomplexNumber Complex_Read();
struct ScomplexNumber Complex_Add(struct ScomplexNumber n1,struct ScomplexNumber n2);
void Complex_Print(struct ScomplexNumber n);
// i will use pointers as they are readeable and faster
int main()
{
    printf("For 1st complexnumber\n");
    num1=Complex_Read();
    printf("For 2st complexnumber\n");
    num2=Complex_Read();
    result=Complex_Add(num1,num2);
    printf("Sum is: ");
    Complex_Print(result);
}
struct ScomplexNumber Complex_Read()
{
    struct ScomplexNumber temp;
    printf("Enter Real and imaginary parts respectively : ");
    scanf("%f %f",&temp.real,&temp.imj);
    return temp;
}
struct ScomplexNumber Complex_Add(struct ScomplexNumber n1,struct ScomplexNumber n2)
{
    struct ScomplexNumber result;
    result.real=n1.real+n2.real;
    result.imj=n1.imj+n2.imj;
    return result;
}
void Complex_Print(struct ScomplexNumber n)
{
    if(n.imj>=0)
    printf("%g+%gi",n.real,n.imj);
    else
    printf("%g%gi",n.real,n.imj);
}