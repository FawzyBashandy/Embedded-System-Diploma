#include <stdio.h>
#include <string.h>
void Str_Reverese(char str[],int str_length);

int main()
{
    char sentence[70];
    printf("Enter a sentence: ");
    fgets(sentence,70,stdin);
    Str_Reverese(sentence,strlen(sentence));
}

void Str_Reverese(char str[],int str_length)
{
    for(int i=str_length-1;i>=0;i--)
    {
        printf("%c",str[i]);
    }
    
}
