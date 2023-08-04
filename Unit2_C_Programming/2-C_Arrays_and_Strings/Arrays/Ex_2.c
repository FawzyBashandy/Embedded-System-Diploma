#include <stdio.h>

int main()
{
    int i,n;
    float sum=0;
    float numbers[100];//assuming maximum number of elements will be 100
    printf("Enter the numbers of data: ");
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        printf("%d. Enter number: ",i+1);
        scanf("%f",&numbers[i]);   
    }
    for(i=0;i<n;i++)
    {
        sum+=numbers[i];
    }
    printf("Average = %.3f",sum/n);
}