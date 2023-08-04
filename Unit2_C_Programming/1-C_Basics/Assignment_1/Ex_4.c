#include <stdio.h>

void main()
{
    float num1,num2;
    printf("Enter two numbers: ");
    fflush(stdout);fflush(stdin);
    scanf("%f %f",&num1,&num2);
    printf("Product: %f",num1*num2);
    
}