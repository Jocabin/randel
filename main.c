#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main(int argc, char **argv)
{
    if (strcmp(argv[1], "help") == 0)
    {
        fprintf(stdout, "HELP FOR RANDEL\n\n");
        fprintf(stdout, "ARG_1 => Data file to select from\n");
        return 0;
    }

    char *DataFilePath = argv[1];

    if (strcmp(argv[1], "ecv") == 0)
    {
        DataFilePath = "/Users/jocabin/dev/c/randel/data.txt";
    }

    FILE *DataFile = fopen(DataFilePath, "r");

    if (DataFile == NULL)
    {
        perror("Data file is NULL");
        exit(1);
    }

    unsigned int LinesCount = 1;
    char *CurrentLine = NULL;
    size_t LineLength = 0;
    ssize_t Read;

    while ((Read = getline(&CurrentLine, &LineLength, DataFile)) != -1)
        LinesCount += 1;

    if (CurrentLine != NULL)
        free(CurrentLine);

    rewind(DataFile);
    srand(time(NULL));

    unsigned int RandomNumber = 1;
    do
    {
        RandomNumber = rand();
    } while (RandomNumber >= (RAND_MAX - RAND_MAX % LinesCount));
    RandomNumber %= LinesCount;

    if (RandomNumber == 0)
        RandomNumber++;

    unsigned int CurrentLineNumber = 1;
    char *RandLine = NULL;
    size_t RandLineLength = 0;
    ssize_t RandRead;

    while ((RandRead = getline(&RandLine, &RandLineLength, DataFile)) != -1)
        if (CurrentLineNumber != RandomNumber)
            CurrentLineNumber += 1;
        else
            break;

    if (CurrentLineNumber == RandomNumber)
        fprintf(stdout, "N°%d => %s\n", RandomNumber, RandLine);
    else
        printf("%s, %d, %d", RandLine, RandomNumber, CurrentLineNumber);

    if (RandLine != NULL)
        free(RandLine);

    fclose(DataFile);
    return 0;
}