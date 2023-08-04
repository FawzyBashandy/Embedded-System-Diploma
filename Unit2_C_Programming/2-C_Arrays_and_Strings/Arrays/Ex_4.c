#include <stdio.h>

int main()
{
    int numbers[50];
    int n,element,loc;
    printf("enter no of elements: ");
    scanf("%d",&n);
    printf("enter values of the elements: ");
    for(int i=0 ; i<n ; i++)
    {
        scanf("%d",&numbers[i]);
    }
    printf("enter the element to be inserted : ");
    scanf("%d",&element);
    printf("enter the location: ");
    scanf("%d",&loc);
    
    for(int i=n ; i>=loc-1 ;i--) //Shifting the numbers to insert the element
    {
        numbers[i+1]=numbers[i];
    }
    numbers[loc-1]=element;
    
    for(int i=0 ; i<=n ; i++)
    {
        printf("%d ",numbers[i]);
    }
}