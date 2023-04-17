#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <omp.h>

int main()
{
    int* ptr;
    int size;
  
    printf("Enter size of elements:");
    scanf("%d", &size);
  
    ptr = (int*)malloc(size * sizeof(int));
  
    if (ptr == NULL) {
        printf("Memory not allocated.\n");
    }
    else {

        for (int j = 0; j < size; ++j) {
            ptr[j] = j + 1;
        }
    } 
    
    return 0;
}