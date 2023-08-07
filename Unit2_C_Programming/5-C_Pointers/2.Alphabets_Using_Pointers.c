#include <stdio.h>

int main()
{
    char start='A',*ptr;
    ptr=&start;
    while(*ptr<='Z')
    {
        printf("%c ",(*ptr)++);
    }
}