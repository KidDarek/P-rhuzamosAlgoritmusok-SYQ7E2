#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  
#include <pthread.h>
  
void GiveValuesToArray(int values[], int length){
for (int i = 0; i < length; i++)
{
    printf("Set %d, value to: ", i+1);
    scanf("%d", &values[i]);
}
}

void WriteValuesOut(int values[], int length){
for (int i = 0; i < length; i++)
{
    printf("%d. value is: %d \n", (i+1) , values[i]);

}

}
   
int main()
{
    int length;
    printf("give lenght here: ");
    scanf("%d", &length);
    int values[length];
    GiveValuesToArray(values,length);
    printf("");
 pthread_t id;
 pthread_create(&id, NULL, WriteValuesOut(values,length), NULL);
    WriteValuesOut(values,length);
    return(0);
}