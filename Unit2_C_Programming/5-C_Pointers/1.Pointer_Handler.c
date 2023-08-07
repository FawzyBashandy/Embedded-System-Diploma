#include <stdio.h>

int main()
{
    int m=29,*ab;
    printf("Address of m : 0x%X\nValue of m : %d",&m,m);
    ab=&m;
    printf("\nNow ab is assigned with the address of m.\nAddress of pointer ab : 0x%X\nContent of pointer ab : %d",ab,*ab);
    m=34;
    printf("\nThe value of m assigned to 34 now.\nAddress of pointer ab : 0x%X\nContent of pointer ab : %d",ab,*ab);
    *ab=7;
    printf("\nThe pointer variable ab is assigned with the value 7 now.\nAddress of m : 0x%X\nValue of m : %d",&m,m);

}