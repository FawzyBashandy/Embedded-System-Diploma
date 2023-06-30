#include <stdio.h>

int main()
{
    float a,b,c;
    printf("Please Enter Three Numbers :");
    scanf("%f %f %f",&a,&b,&c);
    if(a>b)
    {
        if(a>c)
        {
            printf("Largest Number is : %g",a);
        }
        else
        {
            printf("Largest Number is: %g",c);
        }
    }
    else
    {
        if(b>c)
        {
            printf("Largest Number is : %g",b);
        }
        else
        {
            printf("Largest Number is : %g",c);
        }

    }
}