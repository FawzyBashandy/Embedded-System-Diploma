#include <stdio.h>

int main()
{
    int x=10;
    int *px;  //or int *px=&x;
    px=&x;
    printf("%x %x \n",&x,px);
    printf("%d %d",x,*px);
}