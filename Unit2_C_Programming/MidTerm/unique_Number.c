#include <stdio.h>

int unique_Number(int arr[],int size);

int main()
{
    int arr[]={4,2,5,2,5,7,4};
    int arr2[]={4,2,4};
    int size1=sizeof(arr) / sizeof(arr[0]);
    int size2=sizeof(arr2) / sizeof(arr2[0]);
    printf("for array 1 the unique number is: %d \n",unique_Number(arr,size1));
    printf("for array 2 the unique number is: %d",unique_Number(arr2,size2));

    int a=1;
    int x=(a++,++a,a);

}

int unique_Number(int arr[],int size)
{
    int unique;
    for(int i=0;i<size;i++)
    {
        unique^=arr[i];
    }
    return unique;
}