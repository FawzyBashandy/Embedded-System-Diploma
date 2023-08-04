#include <stdio.h>

int main()
{
    int numbers[50];
    int n,element;
    printf("enter no of elements: ");
    scanf("%d",&n);
    printf("enter values of the elements: ");
    for(int i=0 ; i<n ; i++)
    {
        scanf("%d",&numbers[i]);
    }
    printf("enter the element to be searched : ");
    scanf("%d",&element);
    int i=0;
    while(numbers[i]!=element)
    {
        i++;
    }
    printf("Number found at the location = %d",i+1);
}