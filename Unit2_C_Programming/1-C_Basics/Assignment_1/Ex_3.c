#include <stdio.h>


void main() 
{
    int num1,num2;
    printf("Enter two Integers: ");
    fflush(stdout);fflush(stdin);
    scanf("%d %d",&num1,&num2);
    printf("Sum :%d",num1+num2);
}