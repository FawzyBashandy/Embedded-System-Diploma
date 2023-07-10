#include <stdio.h>

void array_Reverser(int numbers[],int size);

int main()
{
    int a[6]={1,2,3,4,5,6};
    int size=sizeof(a)/sizeof(a[0]);
    printf("Before reversing : \n");
    for(int i=0;i<size;i++)
    {
        printf("%d ",a[i]);
    }
    printf("\n After reversing : \n");
    array_Reverser(a,size);
    for(int i=0;i<size;i++)
    {
        printf("%d ",a[i]);
    }

}

void array_Reverser(int numbers[],int size)
{
    int temp;
    for(int i=0;i<size/2;i++)
    {
        temp=numbers[i];
        numbers[i]=numbers[size-i-1];
        numbers[size-1-i]=temp;
    }

}