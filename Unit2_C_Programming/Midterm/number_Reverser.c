#include <stdio.h>
#include <stdlib.h>

int number_Reverser(int);

int main()
{
    int number,num;
    printf("Enter the number: ");
    scanf("%d",&number);
    printf("The Number after reversing digits : %d",number_Reverser(number));
}

int number_Reverser(int num)
{
    char reverser[11]; // Maximum number of digits in an int + 1 for the null terminator
    int rem,isNegative=0;
    int i = 0;
    if(num<0) //Handling the negative numbers
    {
        isNegative=1;
        num=-num;
    }
    while (num != 0) {
        rem = num % 10;
        reverser[i++] = rem + '0'; //'0' to convert the rem to char to be stored as a char
        num /= 10;
    }
    if(isNegative)
    {
        reverser[i++]='-';
    }
    reverser[i]='\0';
    if(isNegative)
    return -1*atoi(reverser); //Since atoi doesn't return the negative sign in the string
    return atoi(reverser);
}