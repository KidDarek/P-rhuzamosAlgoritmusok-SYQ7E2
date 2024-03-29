#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <windows.h>

void LinearFindWaldo(int matrixLength, int matrix[matrixLength][matrixLength][matrixLength])
{
    for (int i = 0; i < matrixLength; i++)
    {
        for (int j = 0; j < matrixLength; j++)
        {
            for (int k = 0; k < matrixLength; k++)
            {
                if (matrix[k][j][i] == 1)
                {
                    printf("Waldo is on the %d. X value, %d. Y value and %d. Z value", k + 1, j + 1, i + 1);
                    return;
                }
            }
        }
    }
}

int main()
{

    // generate the matrix
    srand(time(NULL));

    int n;
    printf("Size of the matrix: ");
    scanf("%d", &n);
    int matrix[n][n][n];
    int a = rand() % n;
    int b = rand() % n;
    int c = rand() % n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                if (i == a && j == b && k == c)
                {
                    matrix[i][j][k] = 1;
                }
                else
                {
                    matrix[i][j][k] = 0;
                }
            }
        }
    }
    // linear search for the 1 in the matrix
    clock_t start = clock();
    printf("\n");
    LinearFindWaldo(n, matrix);
    clock_t end = clock();
    printf("\n");
    printf("runtime: %d", (double)(end - start) / CLOCKS_PER_SEC);

    return 0;
}