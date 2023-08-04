#include <stdio.h>

int main()
{
    int i,k;
    float matrx_1[2][2];
    float matrx_2[2][2];
    printf("Please enter elements of the first array\n");
    for(i=0; i<2;i++)
    {
        for(k=0; k<2 ; k++)
        {
            printf("Please enter element a%d%d: ",i+1,k+1);
            scanf("%f",&matrx_1[i][k]);
        }
    }
    printf("Please enter elements of the second array\n");
    for(i=0; i<2;i++)
    {
        for(k=0; k<2 ; k++)
        {
            printf("Please enter element b%d%d: ",i+1,k+1);
            scanf("%f",&matrx_2[i][k]);
        }
    }
    printf("Sum of Matrix is :\n");
    for(i=0; i<2;i++)
    {
        for(k=0; k<2 ; k++)
        {
            printf("%.2f  ",matrx_1[i][k]+matrx_2[i][k]);
        }
        printf("\n");
    }
}