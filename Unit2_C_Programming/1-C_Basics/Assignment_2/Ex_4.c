#include <stdio.h>

int main()
{
    float num;
    printf("Enter a number: ");
    scanf("%f",&num);
    if(num>0)
    {
        printf("%g is positive.",num);
    }
    else if(num<0)
    {
        printf("%g is negative.",num);
    }
    else
    {
        printf("You Entered Zero");
    }
}