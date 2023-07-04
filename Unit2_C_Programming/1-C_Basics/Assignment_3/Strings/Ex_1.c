#include <stdio.h>
#include <string.h>
int main()
{
    char str[50];
    char ch;
    int count=0;
    printf("Enter a string: ");
    gets(str);
    printf("enter a character to find frequency: ");
    scanf("%c",&ch);
    for(int i=0;i<strlen(str);i++)
    {
        if(str[i]==ch)
        {
            count++;
        }
    }
    printf("Frequency of %c is : %d",ch,count);
}