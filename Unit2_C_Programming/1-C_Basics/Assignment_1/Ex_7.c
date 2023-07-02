#include <stdio.h>

int main()
{
    int x,y;
    printf("Enter the value of x and y in order: ");
    scanf("%d %d",&x,&y);
    x=x+y;
    y=x-y;
    x=x-y;
    printf("The Value of x and y after swapping in order: %d %d",x,y);
}