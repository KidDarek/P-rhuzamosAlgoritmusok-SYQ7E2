#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int SUM(int values[], int lenght)
{
    int sum = 0;
    int i;
    for (i = 0; i < lenght; i++)
    {
        sum += values[i];
    }
    return sum;
}

int MIN(int values[])
{
}

int main()
{
    int lenght;
    printf("value amount: ");
    scanf("%d", &lenght);
    int values[lenght];
    int i = 0;
    for (i = 0; i < lenght; i++)
    {
        printf("%d. value: ", (i + 1));
        scanf("%d \n ", &values[i]);
    }
    printf("sum amount: %d", SUM(values, lenght));
    return 0;
}