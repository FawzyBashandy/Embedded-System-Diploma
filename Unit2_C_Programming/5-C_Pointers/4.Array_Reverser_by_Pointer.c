#include <stdio.h>

int main()
{
    int arr[15],n,i;
    printf("Enter number of elements (maximum 15): ");
    scanf("%d",&n);
    printf("input %d number of elements in the array : \n",n);
    for(i=0;i<n;i++)
    {
        printf("element-%d : ",i+1);
        scanf("%d",arr+i);
    }
    printf("\nThe elements of array in reverse order are :");
    for(i=n-1;i>=0;i--)
    {
        printf("\nelement-%d : %d",i+1,arr[i]);
    }
}