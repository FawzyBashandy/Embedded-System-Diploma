#include <stdio.h>
int Ones_Counter(int num);

int main()
{
    int number;
    printf("Enter the number : ");
    scanf("%d",&number);
    printf("The number of binary ones in %d is %d",number,Ones_Counter(number));
}

int Ones_Counter(int num)
{
    int count=0;
    for(int i=0;i<i<(sizeof(num)*8);i++)
    {
        (num&(1<<i))!=0?count++:count;
    }
    return count;
}