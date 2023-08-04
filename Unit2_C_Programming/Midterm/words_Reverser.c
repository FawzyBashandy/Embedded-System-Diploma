#include <stdio.h>
#include <string.h>
void words_Reverser(char string[],int length);

int main()
{
    char string[100]="Fawzy Mohamed";
    words_Reverser(string,strlen(string));

}

void words_Reverser(char string[],int length)
{
    int i;
    char temp[100];
    char reverse[100]={0};

    for(i=0;i<length;i++)
    {
        temp[i]=string[i];
        if(temp[i]==' ')
        {
            temp[i]=0;
            strcat(reverse,string + i + 1);
            strcat(reverse," ");
            strcat(reverse,temp);

        }


    }
    printf("%s",reverse);
}