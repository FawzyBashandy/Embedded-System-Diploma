#include <stdio.h>

int main ()
{
    float a,b,temp;
    printf("Enter value of a: ");
    scanf("%f",&a);
    printf("Enter value of b: ");
    scanf("%f",&b);
    temp=b;
    b=a;
    a=temp;
    printf("After swapping, Value of a is: %.2f\n",a);
    printf("After swapping, Value of b is: %.2f",b);

}