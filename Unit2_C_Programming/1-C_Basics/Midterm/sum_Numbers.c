#include <stdio.h>
int sum_Numbers();
int main()
{
    printf("Sum of numbers between 1 and 100 is : %d",sum_Numbers());

}

int sum_Numbers()
{
    static int sum=0,i=1;
    if(i>100)
    {
        return 0;
    }
    sum+=i++;
    sum_Numbers();
    return sum;

}