#include <stdio.h>

int factorial(int num);

int main()
{
    int number;
    printf("Enter an positive integer: ");
    scanf("%d",&number);
    printf("Factorial of %d = %d",number,factorial(number));
}

int factorial(int num)
{
    if(num==1)
    return 1;
    return num*factorial(num-1);
}