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

    unsigned int RandomNumber = (rand() % LinesCount) + 1;

    unsigned int CurrentLineNumber = 0;
    char *RandCurrentLine = NULL;
    size_t RandLineLength = 0;
    ssize_t RandRead;

    while (CurrentLineNumber != RandomNumber && (RandRead = getline(&RandCurrentLine, &RandLineLength, DataFile)) != -1)
        CurrentLineNumber += 1;

    fprintf(stdout, "%s\n", RandCurrentLine);

    if (RandCurrentLine != NULL)
        free(RandCurrentLine);

    fclose(DataFile);
    return 0;
}