#include <stdio.h>

int sum_digits(int);

int main()
{
    int number;
    printf("Enter the number: ");
    scanf("%d",&number);
    printf("sum of number digits is : %d",sum_digits(number));
}

int sum_digits(int num)
{
    int static rem_acc=0;
    int rem,n;
    if(num!=0)
    {
        rem=num%10;
        n=num/10;
        rem_acc+=rem;
        sum_digits(n);
    }
    else
    return 0;
    return rem_acc;
}