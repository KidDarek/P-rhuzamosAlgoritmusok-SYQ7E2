#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

int SUM(int values[])
{
    int sum;
    int i;
    for (i = 0; i < sizeof(values) / sizeof(values[0]); i++)
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
    int i;
    for (i = 0; i < lenght; i++)
    {
        printf("%d. value: ", (i + 1));
        scanf("%d", &lenght);
    }
    SUM(values);
    return 0;
}