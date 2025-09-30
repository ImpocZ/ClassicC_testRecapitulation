#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define DELIMS " :,"
#define MAX_LINE_LENGTH 50
#define INPUT "startovni_listina_kombinace_zeny.txt"
#define OUTPUT "vysledky_kombinace_zeny.txt"

// Exits --> -101 = fr error, -91 = fw error, -50 memory allocations errors... -999 parsing error...

typedef struct
{
    int min;
    int sec;
    int centisec;
}FIRST_TIME;

typedef struct
{
    int seconds;
    int centisec;
}SECOND_TIME;

typedef struct
{
    int position;
    char firstname[20];
    char surname[20];
    char nation[4];
    FIRST_TIME firstTime;
    SECOND_TIME secondTime;
}DATA;

FILE *openFile(int foMode, const char *file, FILE *fr);

DATA parseData(DATA data, char *storage){
    char *token;
    for (int i = 0; (token = strtok(i == 0 ? storage : NULL, DELIMS)) != NULL; i++)
    {
        switch (i)
        {
        case 0:
            data.position = atoi(token);
            break;
        case 1:
            strcpy(data.firstname, token);
            break;
        case 2:
            strcpy(data.surname, token);
            break;
        case 3:
            strcpy(data.nation, token);
            break;
        case 4:
            data.firstTime.min = atoi(token);
            break;
        case 5:
            data.firstTime.sec = atoi(token);
            break;
        case 6:
            data.firstTime.centisec = atoi(token);
            break;
        case 7:
            data.secondTime.seconds = atoi(token);
            break;
        case 8:
            data.secondTime.centisec = atoi(token);
            break;
        default:
            exit(-999);
            break;
        }
    }
    return data;
}

DATA *fillData(int *total){
    FILE *fr = openFile(0, INPUT, fr);
    DATA *temp, *resized;
    char storage[MAX_LINE_LENGTH];

    while (fgets(storage, MAX_LINE_LENGTH, fr) != NULL)
    {
        temp = (DATA *)realloc(resized, (*total + 1) * sizeof(DATA));
        resized = temp;
        if (resized == NULL)
        {
            exit(-50);
        }
        resized[*total] = parseData(resized[*total], storage);
        *total += 1;
    }
    fr = openFile(1, INPUT, fr);
    return resized;
}

FILE *openFile(int foMode, const char *file, FILE *fName){
    
    if (foMode == 0)
    {
        fName = fopen(file, file == INPUT ? "r" : "w");
        if (fName == NULL)
        {
            printf("Error encountere while tring to close the file %s!\n", file);
            exit(file == INPUT ? -101 : -91);
        }
        return fName;
    } else if (foMode == 1)
    {
        if (!(fclose(fName)))
        {
            printf("File %s closed successfully.\n", file);
        }
        else {
            printf("Error encountere while tring to close the file %s!\n", file);
            exit(file == INPUT ? -101 : - 91);
        }
        return fName;    
    } else {
        exit(-192);
    }
}

void printOut(DATA *data, int total){
    printf("Alpske lyzovani startovni listina K O M B I N A C E  Z E N Y\n"
        "--------------------------------------------------------------------------------\n"
        "startovni cislo    jmeno       prijmeni  stat      sjezd  slalom\n"
        "--------------------------------------------------------------------------------\n"
    );
    for (int i = 0; i < total; i++)
    {
        printf("        %02d  %20s   %20s   %s  %d:%02d,%02d  %2d,%02d\n", data[i].position, data[i].firstname,
            data[i].surname, data[i].nation, data[i].firstTime.min, data[i].firstTime.sec, data[i].firstTime.centisec,
            data[i].secondTime.seconds, data[i].secondTime.seconds);
    }
    
}

int main(){
    int total = 0;
    DATA *data = fillData(&total);
    printOut(data, total);

    free(data);
    printf("All done..\n");
    return 0;
}