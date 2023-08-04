#include <stdio.h>
void Prime_Numbers(int start , int end);

int main()
{
    int start,end;
    printf("Enter two numbers(intervals): ");
    scanf("%d %d",&start,&end);
    Prime_Numbers(start,end);
}

void Prime_Numbers(int start , int end)
{
    char prime=1;
    for(int i=start;i<=end;i++)
    {
        prime=1;
        for(int j=2;j<i;j++)
        {
            if(i%j==0)
            {
                prime=0;
                break;
            }
        }
        
        if(prime)
        printf("%d ",i);
        
    }
}