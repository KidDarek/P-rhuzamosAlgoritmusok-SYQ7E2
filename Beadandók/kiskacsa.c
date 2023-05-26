#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <windows.h>

typedef struct Data
{
    int length;
    int clength;
    int *buckets;
    int checked;
    int currentBucket;
    int duckLocation;
} Data;

int RelocateDuck(int duckLocation, int length)
{
    int newLocation = duckLocation;
    if (newLocation == length)
    {
        newLocation = length - 1;
    }
    else if (newLocation == 0)
    {
        newLocation = 1;
    }
    else
    {
        int r = rand() % 2;
        if (r == 0)
        {
            newLocation -= 1;
        }
        else
        {
            newLocation += 1;
        }
    }
    return newLocation;
}

void GenerateDuck(int length, int *buckets, int duckStartLocation)
{
    for (int i = 0; i < length; i++)
    {
        if (i == duckStartLocation)
        {
            buckets[i] = 1;
        }
        else
        {
            buckets[i] = 0;
        }
    }
}

void GuarantedLinearSearch(Data data)
{
    int newLocation = data.duckLocation;
    // printf("Duck %d \n", newLocation);
    // printf("Our local %d \n", currentBucket);
    if (data.buckets[data.currentBucket] == 1)
    {
        printf("The Duck Has Been Found On %d !!! \n", data.currentBucket);
    }
    else
    {
        data.buckets[newLocation] = 0;
        newLocation = RelocateDuck(newLocation, data.length);
        data.buckets[newLocation] = 1;
        if (data.checked < data.clength)
        {
            data.checked += 1;
        }
        else
        {
            data.checked = 0;
            data.clength--;
            data.currentBucket++;
        }
        data.duckLocation = newLocation;
        GuarantedLinearSearch(data);
    }
}

void HopSearch(Data data)
{
    int newLocation = data.duckLocation;
    while (data.currentBucket < data.length)
    {
        if (data.buckets[data.currentBucket] == 1)
        {
            printf("The Duck Has Been Found On %d !!!\n", data.currentBucket);
            break;
        }
        else
        {
            // printf("Duck %d \n", newLocation);
            // printf("Our local %d \n", currentBucket);
            data.currentBucket += 2;
            data.buckets[newLocation] = 0;
            newLocation = RelocateDuck(newLocation, data.length);
            data.buckets[newLocation] = 1;
        }
        if (data.buckets[data.currentBucket] == 1)
        {
            printf("The Duck Has Been Found On %d !!!\n", data.currentBucket);
            break;
        }
        else
        {
            // printf("Duck %d \n", newLocation);
            // printf("Our local %d \n", currentBucket);
            data.currentBucket--;
            data.buckets[newLocation] = 0;
            newLocation = RelocateDuck(newLocation, data.length);
            data.buckets[newLocation] = 1;
        }
    }
    if (data.currentBucket >= data.length)
    {
        printf("Couldn't find it :c\n");
    }
}

void FullLinear(int length, int *buckets, int duckLocation)
{
    int newLocation = duckLocation;
    int i;
    for (i = 0; i < length; i++)
    {
        // printf("Duck %d \n", newLocation);
        // printf("Our local %d \n", i);
        if (buckets[i] == 1)
        {
            printf("The Duck Has Been Found On %d !!!\n", i);
            i = length + 1;
        }
        buckets[newLocation] = 0;
        newLocation = RelocateDuck(newLocation, length);
        buckets[newLocation] = 1;
    }
    if (i == length)
    {
        printf("Couldn't find it :c\n");
    }
}

void HalvingLinear(int length, int *buckets, int duckLocation)
{
    int newLocation = duckLocation;
    int i;
    for (i = length / 2; i > 0; i--)
    {
        // printf("Duck %d \n", newLocation);
        // printf("Our local %d \n", i);
        if (buckets[i] == 1)
        {
            printf("The Duck Has Been Found On %d !!!\n", i);
            i = -1;
        }
        buckets[newLocation] = 0;
        newLocation = RelocateDuck(newLocation, length);
        buckets[newLocation] = 1;
    }
    if (i == 0)
    {
        for (i = length / 2; i < length; i++)
        {
            // printf("Duck %d \n", newLocation);
            // printf("Our local %d \n", i);
            if (buckets[i] == 1)
            {
                printf("The Duck Has Been Found On %d !!!\n", i);
                i = length + 1;
            }
            buckets[newLocation] = 0;
            newLocation = RelocateDuck(newLocation, length);
            buckets[newLocation] = 1;
        }
        if (i == length)
        {
            printf("Couldn't find it :c\n");
        }
    }
}

void FullRandom(int length, int *buckets, int duckLocation)
{
    int newLocation = duckLocation;
    int i;
    for (i = 0; i < length; i++)
    {
        // printf("Duck %d \n", newLocation);
        // printf("Our local %d \n", i);
        if (buckets[rand() % length] == 1)
        {
            printf("The Duck Has Been Found On %d !!!\n", i);
            i = length + 1;
        }
        buckets[newLocation] = 0;
        newLocation = RelocateDuck(newLocation, length);
        buckets[newLocation] = 1;
    }
    if (i == length)
    {
        printf("Couldn't find it :c\n");
    }
}

int main()
{
    srand(time(NULL));
    int n;
    printf("How manny buckets should there be? : ");
    scanf("%d", &n);
    int buckets[n];
    int duckfirstlocaltion = rand() % n;
    double RunT;
    Data data;
    data.buckets = buckets;
    data.length = n;
    data.checked = 0;
    data.clength = n;
    data.currentBucket = 0;
    data.duckLocation = duckfirstlocaltion;
    /*
    GenerateDuck(n, buckets, duckfirstlocaltion);
    clock_t start1 = clock();
    GuarantedLinearSearch(data);
    clock_t end1 = clock();
    RunT = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf("runtime: %f \n", RunT);
    */
    GenerateDuck(n, buckets, duckfirstlocaltion);
    clock_t start2 = clock();
    HopSearch(data);
    clock_t end2 = clock();
    RunT = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("runtime: %f \n", RunT);
    /*
    GenerateDuck(n, buckets, duckfirstlocaltion);
    clock_t start3 = clock();
    FullLinear(n, buckets, duckfirstlocaltion);
    clock_t end3 = clock();
    RunT = (double)(end3 - start3) / CLOCKS_PER_SEC;
    printf("runtime: %f \n", RunT);
    //
    GenerateDuck(n, buckets, duckfirstlocaltion);
    clock_t start4 = clock();
    HalvingLinear(n, buckets, duckfirstlocaltion);
    clock_t end4 = clock();
    RunT = (double)(end4 - start4) / CLOCKS_PER_SEC;
    printf("runtime: %f \n", RunT);
    //
    GenerateDuck(n, buckets, duckfirstlocaltion);
    clock_t start5 = clock();
    FullRandom(n, buckets, duckfirstlocaltion);
    clock_t end5 = clock();
    RunT = (double)(end5 - start5) / CLOCKS_PER_SEC;
    printf("runtime: %f \n", RunT);
*/

    pthread_t threads[5];
    pthread_create(&threads[0], NULL, GuarantedLinearSearch(data), NULL);
    pthread_create(&threads[1], NULL, HopSearch(data), NULL);
    /*  int th3 = pthread_create(&threads[2], NULL, FullLinear, [ n, buckets, duckfirstlocaltion ]);
      int th4 = pthread_create(&threads[3], NULL, HalvingLinear, [ n, buckets, duckfirstlocaltion ]);
      int th5 = pthread_create(&threads[4], NULL, FullRandom, [ n, buckets, duckfirstlocaltion ]);
      if (th1 == 0 || th2 == 0 || th3 == 0 || th4 == 0 || th5 == 0)
      {
          int pthread_cancel(pthread_t threads[0]);
          int pthread_cancel(pthread_t threads[1]);
          int pthread_cancel(pthread_t threads[2]);
          int pthread_cancel(pthread_t threads[3]);
          int pthread_cancel(pthread_t threads[4]);
      }
  */
    return 0;
}