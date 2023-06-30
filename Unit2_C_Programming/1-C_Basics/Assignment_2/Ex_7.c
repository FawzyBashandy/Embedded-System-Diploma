#include <stdio.h>

int main()
{
    int n,result=1;
    printf("Enter a number: ");
    scanf("%d",&n);
    if(n<0)
    {
        printf("Error!!! Factorial of negative number doesn't exist.");    
    }
    else
    {
        for(int i=n;i>0;i--)
        {
           result*=i;
        }
    printf("Factorial = %d",result);
    }

}