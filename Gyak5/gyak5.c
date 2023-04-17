#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main()
{
    int n;
    int a = 9;
    int b = 3;
    prinf("Size of the matrix: ");
    scanf("%d",&n);
int matrix[n][n];
for (int i = 0; i < n; i++)
{
    for (int j = 0; j < n; j++)
    {
        if(i == a && j == b)
        {
            matrix[i][j] = 1;
        }
        else
        {
matrix[i][j] = 0;
        }
    }

}

    return 0;
}