#include <stdio.h>
#include <string.h>
int main()
{
    char str[50];
    char rev_str[50];
    int length;
    printf("Enter the string: ");
    gets(str);
    length=strlen(str);
    for(int i=0;i<length;i++)
    {
        rev_str[i]=str[length-i-1];
    }
    printf("Reverse string is : %s",rev_str);
}