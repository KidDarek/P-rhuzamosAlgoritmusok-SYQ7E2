#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <windows.h>

void GuarantedLinearSearch(int length, int buckets[length], int checked, int currentBucket)
{
}

int main()
{
    srand(time(NULL));
    int n;
    printf("How manny buckets should there be? : ");
    scanf("%d", &n);
    int buckets[n];
    int duckfirstlocaltion = rand() % n;
    for (int i = 0; i < n; i++)
    {
        if (i == duckfirstlocaltion)
        {
            buckets[i] = 1;
        }
        else
        {
            buckets[i];
        }
    }

    return 0;
}