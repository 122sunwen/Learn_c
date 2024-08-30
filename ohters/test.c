#include <stdio.h>
#include <stdlib.h>

int main()
{
    int **m1 = (int *)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            scanf("%d", m1[i][j]);
        }
    }
    int **m2 = (int *)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            scanf("%d", m2[i][j]);
        }
    }
    int **re = (int *)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {

            re[i][j]=0;
            for (int k = 0; k < 2; k++)
            {
                re[i][j]+=m1[i][k]*m2[k][j];
            }
            
        }
    }
    free(m1);
    free(m2);
    free(re);
}