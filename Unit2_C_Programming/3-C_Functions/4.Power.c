#include <stdio.h>

int Power(int number,int power);

int main()
{
    int number,power;
    printf("Enter base number: ");
    scanf("%d",&number);
    printf("Enter power number(positive integer): ");
    scanf("%d",&power);
    printf("%d*%d = %d",number,power,Power(number,power));
}

int Power(int number,int power)
{
    if(power==0)
    return 1;
    return number*Power(number,power-1);
}