#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DELIMS " :,"
#define MAX_LINE_LENGTH 50

typedef struct
{
    int min;
    int sec;
    int milisec;
}TIME_FORMAT;


typedef struct
{
    int position;
    char firstname[20];
    char surname[20];
    char nation[4];
    TIME_FORMAT time_format;
}DATA;

DATA *fillData(int *total){
    DATA *temp, *resized;
    char storage[MAX_LINE_LENGTH];

}

int main(){
    int total = 0;
    DATA *data = fillData(&total);


    free(data);
    printf("All done..\n");
    return 0;
}