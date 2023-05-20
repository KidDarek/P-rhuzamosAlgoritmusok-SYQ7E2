#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <windows.h>

void LinearFindWaldo(int matrixX, int matrixY, int matrixZ, int matrix[matrixX][matrixY][matrixZ], int waldo)
{
    int found = 0;
    while (waldo != found)
    {
        for (int i = 0; i < matrixX; i++)
        {
            for (int j = 0; j < matrixY; j++)
            {
                for (int k = 0; k < matrixZ; k++)
                {
                    if (matrix[k][j][i] == 1)
                    {
                        printf("Waldo is on the %d. X value, %d. Y value and %d. Z value \n", k + 1, j + 1, i + 1);
                        found++;
                        matrix[k][j][i] = 0;
                        matrix[rand() % matrixX][rand() % matrixY][rand() % matrixZ] = 1;
                    }
                    if (waldo == found)
                    {
                        i = matrixX;
                        j = matrixY;
                        k = matrixZ;
                    }
                }
                // Sokszor fut le
            }
        }
    }
    return;
}

int main()
{

    // generate the matrix
    srand(time(NULL));

    int x;
    int y;
    int z;
    int waldo;
    printf("X lenght of the matrix: ");
    scanf("%d", &x);
    printf("Y lenght of the matrix: ");
    scanf("%d", &y);
    printf("Z lenght of the matrix: ");
    scanf("%d", &z);
    printf("How many times should Waldo hide: ");
    scanf("%d", &waldo);
    int matrix[x][y][z];
    int a = rand() % x;
    int b = rand() % y;
    int c = rand() % z;
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < y; j++)
        {
            for (int k = 0; k < z; k++)
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
    LinearFindWaldo(x, y, z, matrix, waldo);
    clock_t end = clock();
    printf("\n");
    double linRun = (double)(end - start) / CLOCKS_PER_SEC;
    printf("runtime: %f \n", (double)(end - start) / CLOCKS_PER_SEC);

    clock_t start2 = clock();

    int found = 0;
#pragma omp for
    for (int q = 0; q < 1; q++)
    {
        while (found != waldo)
        {
            for (int i = 0; i < x; i++)
            {
                for (int j = 0; j < y; j++)
                {
                    for (int k = 0; k < z; k++)
                    {
                        if (matrix[k][j][i] == 1)
                        {
                            printf("Waldo is on the %d. X value, %d. Y value and %d. Z value \n", k + 1, j + 1, i + 1);
                            found++;
                            matrix[k][j][i] = 0;
                            matrix[rand() % x][rand() % y][rand() % z] = 1;
                        }
                        if (waldo == found)
                        {
                            i = x;
                            j = y;
                            k = z;
                        }
                    }
                }
            }
        }
    }

    clock_t end2 = clock();
    double parRun = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("runtime: %f \n", (double)(end2 - start2) / CLOCKS_PER_SEC);
    printf("\n");
    printf("Runtime: %f \n", linRun);
    printf("\n");
    printf("Runtime: %f \n", parRun);

    return 0;
}