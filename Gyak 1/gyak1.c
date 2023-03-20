#include <stdio.h> 
#include <stdlib.h>
#include <windows.h>


int randInRange(int min, int max)
{
  return min + (int) (rand() / (double) (RAND_MAX + 1) * (max - min + 1));
}
double randInRange2(int min, int max)
{
  return min + (double) (rand() / (double) (RAND_MAX + 1) * (max - min + 1));
}


int main()
{
    int min;
    int max;
    printf("min szám: ");
    scanf("%d", &min);
    printf("\n");
    printf("max szám: ");
    scanf("%d", &max);
    int i;
    for (i = 0; i < 8; i++)
    {
        printf("%d \n", randInRange(min , max));
        Sleep(1000);
        printf("%f \n", randInRange2(min , max));
    }
    
  return 0;
}
