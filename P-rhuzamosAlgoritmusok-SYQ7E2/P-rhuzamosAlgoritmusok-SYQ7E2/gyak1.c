#include <stdio.h> 
#include <stdlib.h>
#include <time.h>
#include <windows.h>


int randInRange(int min, int max)
{
  return min + (int) (rand() / (double) (RAND_MAX + 1) * (max - min + 1));
}
double randInRange2(int min, int max)
{
  return min + (double) (rand() / (double) (RAND_MAX + 1) * (max - min));
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
    clock_t begin = clock();
    int i;
    for (i = 0; i < 8; i++)
    {
        printf("%d \n", randInRange(min , max));
        Sleep(10);
        printf("%f \n", randInRange2(min , max));
    }
    
    clock_t end = clock();
double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
printf("runtime: %f \n", time_spent);

FILE *file;
int tests = 10;
double randtime[10];
int filetime[10];
int j;
for (j = 0; j < tests; j++)
{
 char asd[64];
    int count;
    printf("file Neve: ");
    scanf("%s", &asd);
    printf("\n");
    printf("adat szám: ");
    scanf("%d", &count);
    file = fopen(asd, "w");
int ertekek[count];
clock_t numbegin = clock();
   for (i = 0; i < count; i++)
   {
     ertekek[i] = randInRange(min , max);
   }
      clock_t numend = clock();
      double time_spent_on_nums = (double)(numend - numbegin) / CLOCKS_PER_SEC;
      printf("numtime: %f \n", time_spent_on_nums);
    randtime[j] = time_spent_on_nums;

      clock_t writebegin = clock();
   for (i = 0; i < count; i++)
   {
    fprintf(file,"Ertek: %d \n", randInRange(min , max));
    Sleep(10);
   }
         clock_t writeend = clock();
      double time_spent_on_write = (double)(writeend - writebegin) / CLOCKS_PER_SEC;
      printf("write time: %f \n", time_spent_on_write);
      filetime[j] = time_spent_on_write;
}
fclose(file);



  return 0;
}
