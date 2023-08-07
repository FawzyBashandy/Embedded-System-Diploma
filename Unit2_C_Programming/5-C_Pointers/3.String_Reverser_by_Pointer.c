#include <stdio.h>
#include <string.h>
int main()
{
    char string[50],*ptrc;
    ptrc=string;
    printf("Enter the string: ");
    fgets(string,50,stdin);
    printf("The string in reverse order is :");
    for(int i=strlen(string)-1;i>=0;i--)
    {
        printf("%c",ptrc[i]);
    }
}