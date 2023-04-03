#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <windows.h>

int randomIntegerGenerator(int min, int max)
{
    return min + (int)(rand() / (double)(RAND_MAX + 1) * (max - min + 1));
}

int recursiveMult(int values[], int length, int h, int prod, int maxrecurvedepth)
{
    if (h != length)
    {
        prod *= values[h];
        h++;
        recursiveMult(values, length, h, prod, maxrecurvedepth);
    }
    else
    {
        return prod;
    }
}

int main()
{
    int n;

    printf("Length of array: ");
    scanf("%d", &n);
    int values[n];
    for (int i = 0; i < n; i++)
    {
        values[i] = randomIntegerGenerator(1, 100);
    }

#pragma omp parallel
    {
        int thread_id;
        thread_id = omp_get_thread_num();
        printf("thread_id = %d\n", values[thread_id]);
    }
    int product = 1;
    int productpara = 1;
    for (int i = 0; i < n; i++)
    {
        product *= values[i];
    }
    printf("%d \n", product);
    printf("%d \n", recursiveMult(values, n, 0, 1, 1));
#pragma omp for
    for (int i = 0; i < n; i++)
    {
        productpara *= values[i];
    }
    printf("%d \n", productpara);
    return 0;
}