#include <stdio.h>

int main()
{
    char ch;
    float a,b;
    printf("Enter operator either + or - or * or divide: ");
    scanf("%c",&ch);
    printf("Enter two operands: ");
    scanf("%f %f",&a,&b);
    switch(ch)
    {
        case '+':
        {
            printf("%g %c %g = %g",a,ch,b,a+b);
        }
        break;
        case '-':
        {
            printf("%g %c %g = %g",a,ch,b,a-b);
        }
        break;
        case '*':
        {
            printf("%g %c %g = %g",a,ch,b,a*b);
        }
        break;
        case '/':
        {
            printf("%g %c %g = %g",a,ch,b,a/b);
        }
        break;
        default:
        {
            printf("please enter a valid operator");
        }
        break;
    }
}