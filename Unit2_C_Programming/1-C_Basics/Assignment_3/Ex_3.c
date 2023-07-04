#include <stdio.h>

int main()
{
    int matrx[10][10];//assuming max matrx will be 10 rows and 10 col
    int i,k,row,col;
    printf("Enter rows and column of matrix : ");
    scanf("%d %d",&row,&col);
    printf("Enter Elements of matrix: \n");
    for(i=0;i<row;i++)
    {
        for(k=0;k<col;k++)
        {
            printf("Enter elements of a%d%d: ",i+1,k+1);
            scanf("%d",&matrx[i][k]);
        }
    }

    printf("Entered Matrix: \n");
    for(i=0;i<row;i++)
    {
        for(k=0;k<col;k++)
        {
            printf("%d  ",matrx[i][k]);
        }
        printf("\n");
    }
    
    printf("Transpose of Matrix: \n");

    for(i=0;i<col;i++)
    {
        for(k=0;k<row;k++)
        {
        printf("%d  ",matrx[k][i]);
        }
        printf("\n");
    }


}