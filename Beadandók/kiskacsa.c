#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>
#include <windows.h>

int found = 0;

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

void FillArray(int *Array, int *Source, int length)
{
    for (int i = 0; i < length; i++)
    {
        Array[i] = Source[i];
    }
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

/* void *GuarantedLinearSearch(void *param)
{
    Data *data = (Data *)param;
    int newLocation = data->duckLocation;
    // printf("Duck %d \n", newLocation);
    // printf("Our local %d \n", currentBucket);
    if (data->buckets[data->currentBucket] == 1)
    {
        printf("The Duck Has Been Found On %d !!! (Gar)\n", data->currentBucket);
    }
    else
    {
        data->buckets[newLocation] = 0;
        newLocation = RelocateDuck(newLocation, data->length);
        data->buckets[newLocation] = 1;
        if (data->checked < data->clength)
        {
            data->checked += 1;
        }
        else
        {
            data->checked = 0;
            data->clength--;
            data->currentBucket++;
        }
        data->duckLocation = newLocation;
        GuarantedLinearSearch((void *)data);
    }
}
*/
void *GuarantedLinearSearch(void *param)
{
    Data *data = (Data *)param;
    int newLocation = data->duckLocation;
    // printf("Duck %d \n", newLocation);
    // printf("Our local %d \n", currentBucket);
    while (found != 1)
    {
        if (found == 1)
        {
            pthread_exit(NULL);
        }

        if (data->buckets[data->currentBucket] == 1)
        {
            printf("The Duck Has Been Found On %d !!! (Gar)\n", data->currentBucket);
            found = 1;
        }
        else
        {
            data->buckets[newLocation] = 0;
            newLocation = RelocateDuck(newLocation, data->length);
            data->buckets[newLocation] = 1;
            if (data->checked < data->clength)
            {
                data->checked += 1;
            }
            else
            {
                data->checked = 0;
                data->clength--;
                data->currentBucket++;
            }
        }
    }
}

void *HopSearch(void *param)
{
    Data *data = (Data *)param;
    int newLocation = data->duckLocation;
    while (data->currentBucket < data->length)
    {
        if (found == 1)
        {
            pthread_exit(NULL);
        }
        if (data->buckets[data->currentBucket] == 1)
        {
            printf("The Duck Has Been Found On %d !!! (Hop)\n", data->currentBucket);
            found = 1;
            break;
        }
        else
        {
            // printf("Duck %d \n", newLocation);
            // printf("Our local %d \n", currentBucket);
            data->currentBucket += 2;
            data->buckets[newLocation] = 0;
            newLocation = RelocateDuck(newLocation, data->length);
            data->buckets[newLocation] = 1;
        }
        if (data->buckets[data->currentBucket] == 1)
        {
            printf("The Duck Has Been Found On %d !!! (Hop)\n", data->currentBucket);
            found = 1;
            break;
        }
        else
        {
            // printf("Duck %d \n", newLocation);
            // printf("Our local %d \n", currentBucket);
            data->currentBucket--;
            data->buckets[newLocation] = 0;
            newLocation = RelocateDuck(newLocation, data->length);
            data->buckets[newLocation] = 1;
        }
    }
    if (data->currentBucket >= data->length)
    {
        printf("Couldn't find it :c (Hop)\n");
    }
}

void *FullLinear(void *param)
{
    Data *data = (Data *)param;
    int newLocation = data->duckLocation;
    int i;
    for (i = 0; i < data->length; i++)
    {
        if (found == 1)
        {
            pthread_exit(NULL);
        }
        // printf("Duck %d \n", newLocation);
        // printf("Our local %d \n", i);
        if (data->buckets[i] == 1)
        {
            printf("The Duck Has Been Found On %d !!! (Lin)\n", i);
            i = data->length + 1;
            found = 1;
        }
        data->buckets[newLocation] = 0;
        newLocation = RelocateDuck(newLocation, data->length);
        data->buckets[newLocation] = 1;
    }
    if (i == data->length)
    {
        printf("Couldn't find it :c (Lin)\n");
    }
}

void *HalvingLinear(void *param)
{
    Data *data = (Data *)param;
    int newLocation = data->duckLocation;
    int i;
    for (i = data->length / 2; i > 0; i--)
    {
        if (found == 1)
        {
            pthread_exit(NULL);
        }
        // printf("Duck %d \n", newLocation);
        // printf("Our local %d \n", i);
        if (data->buckets[i] == 1)
        {
            printf("The Duck Has Been Found On %d !!! (Half)\n", i);
            i = -1;
            found = 1;
        }
        data->buckets[newLocation] = 0;
        newLocation = RelocateDuck(newLocation, data->length);
        data->buckets[newLocation] = 1;
    }
    if (i == 0)
    {
        for (i = data->length / 2; i < data->length; i++)
        {
            // printf("Duck %d \n", newLocation);
            // printf("Our local %d \n", i);
            if (data->buckets[i] == 1)
            {
                printf("The Duck Has Been Found On %d !!! (Half)\n", i);
                i = data->length + 1;
                found = 1;
            }
            data->buckets[newLocation] = 0;
            newLocation = RelocateDuck(newLocation, data->length);
            data->buckets[newLocation] = 1;
        }
        if (i == data->length)
        {
            printf("Couldn't find it :c (half)\n");
        }
    }
}

void *FullRandom(void *param)
{
    Data *data = (Data *)param;
    int newLocation = data->duckLocation;
    int i;
    unsigned long index;
    for (i = 0; i < data->length; i++)
    {
        index = rand();
        index <<= 15;
        index ^= rand();
        index %= data->length;
        if (found == 1)
        {
            pthread_exit(NULL);
        }
        // printf("Duck %d \n", newLocation);
        // printf("Our local %d \n", i);
        if (data->buckets[index] == 1)
        {
            printf("The Duck Has Been Found On %d !!! (Rand)\n", index);
            found = 1;
            i = data->length + 1;
        }
        data->buckets[newLocation] = 0;
        newLocation = RelocateDuck(newLocation, data->length);
        data->buckets[newLocation] = 1;
    }
    if (i == data->length)
    {
        printf("Couldn't find it :c (Rand)\n");
    }
}

int main()
{
    srand(time(NULL));
    int n;
    printf("How manny buckets should there be? : ");
    scanf("%d", &n);
    int buckets[n];
    unsigned long duckfirstlocaltion;
    duckfirstlocaltion = rand();
    duckfirstlocaltion <<= 15;
    duckfirstlocaltion ^= rand();
    duckfirstlocaltion %= n;
    printf("%d \n", duckfirstlocaltion);
    double RunT;
    Data data[5];
    GenerateDuck(n, buckets, duckfirstlocaltion);
    for (int i = 0; i < 6; i++)
    {
        data[i].buckets = malloc(sizeof(int) * n);
        FillArray(data[i].buckets, buckets, n);
        data[i].length = n;
        data[i].checked = 0;
        data[i].clength = n;
        data[i].currentBucket = 0;
        data[i].duckLocation = duckfirstlocaltion;
    }

    clock_t start1 = clock();
    // GuarantedLinearSearch((void *)&data[5]);
    clock_t end1 = clock();
    RunT = (double)(end1 - start1) / CLOCKS_PER_SEC;
    printf("runtime: %f \n", RunT);
    /*
        GenerateDuck(n, buckets, duckfirstlocaltion);
        clock_t start2 = clock();
        HopSearch(data);
        clock_t end2 = clock();
        RunT = (double)(end2 - start2) / CLOCKS_PER_SEC;
        printf("runtime: %f \n", RunT);

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
    found = 0;
    pthread_t threads[5];
    clock_t start2 = clock();
    pthread_create(&threads[0], NULL, GuarantedLinearSearch, (void *)&data[0]);
    GenerateDuck(n, buckets, duckfirstlocaltion);
    pthread_create(&threads[1], NULL, HopSearch, (void *)&data[1]);
    GenerateDuck(n, buckets, duckfirstlocaltion);
    pthread_create(&threads[2], NULL, FullLinear, (void *)&data[2]);
    GenerateDuck(n, buckets, duckfirstlocaltion);
    pthread_create(&threads[3], NULL, HalvingLinear, (void *)&data[3]);
    GenerateDuck(n, buckets, duckfirstlocaltion);
    pthread_create(&threads[4], NULL, FullRandom, (void *)&data[4]);
    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    clock_t end2 = clock();
    RunT = (double)(end2 - start2) / CLOCKS_PER_SEC;
    printf("runtime: %f \n", RunT);
    return 0;
}