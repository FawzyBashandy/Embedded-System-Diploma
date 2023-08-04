#include <stdio.h>
#include <string.h>
int maxNum_Ones(int num);

int main()
{
    int number;
    printf("enter the number: ");
    scanf("%d",&number);
    printf("Max number of ones between zeros is : %d ",maxNum_Ones(number));

}

int maxNum_Ones(int num)
{
    int start = -1;
    int maxones = 0;

    for(int i = 0; i < (sizeof(num) * 8); i++)
    {
        if((num & (1 << i)) == 0)
        {
            start = i;
        }
        else
        {
            if((i - start) > maxones)
            {
                maxones = i - start;
            }
        }
    }

    return maxones;
}