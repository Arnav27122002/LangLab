#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Namtab
{
    char name[20];
    int start;
    int end;
    int clcnt;
};

char Deftab[1000];
struct Namtab Namtabs[20];
int NamtabCount = 0;

int isMacro(char *word)
{
    for (int i = 0; i < NamtabCount; i++)
    {
        if (strcmp(word, Namtabs[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void stripSymbols(char *line)
{
    int size = strlen(line);
    for (int i = 0; i < size; i++)
    {
        if (line[i] == '\t' || line[i] == ',')
        {
            line[i] = ' ';
        }
    }
    if (line[size - 1] == '\n')
    {
        line[size - 1] = '\0';
    }
}

void getInstructions(char *line, char *instructions[], int *instructionCount)
{
    stripSymbols(line);
    int i = 0;

    char *token = strtok(line, " ");
    while (token != NULL)
    {
        if (strlen(token) > 0)
        {
            instructions[i] = token;
            i++;
        }
        token = strtok(NULL, " ");
    }
    *instructionCount = i;
}

void defineMacro(FILE *inputFile, char *macroDefinition[], int macroDefCount)
{
    char *macroName = macroDefinition[0];
    int argCount = macroDefCount - 2;
    Namtabs[NamtabCount].clcnt = 0;
    strcpy(Namtabs[NamtabCount].name, macroName);

    // Calculate start address based on current length of Deftab
    Namtabs[NamtabCount].start = strlen(Deftab);

    // Add the macro definition line to Deftab
    for (int i = 0; i < macroDefCount; i++)
    {
        strcat(Deftab, macroDefinition[i]);
        strcat(Deftab, " ");
    }
    strcat(Deftab, "\n");

    char macroLine[100];
    char *macroInstructions[20];
    int macroInstructionCount;

    while (fgets(macroLine, 100, inputFile))
    {
        getInstructions(macroLine, macroInstructions, &macroInstructionCount);
        if (macroInstructionCount == 0)
        {
            continue;
        }
        if (strcmp(macroInstructions[0], "MEND") == 0)
        {
            break;
        }

        // Add each line of the macro to Deftab
        strcat(Deftab, macroInstructions[0]);
        strcat(Deftab, " ");
        for (int i = 1; i < macroInstructionCount; i++)
        {
            char *word = macroInstructions[i];
            int replaced = 0;
            for (int j = 0; j < argCount; j++)
            {
                if (strcmp(word, macroDefinition[j + 2]) == 0)
                {
                    strcat(Deftab, "#");
                    char num[2];
                    sprintf(num, "%d", j);
                    strcat(Deftab, num);
                    replaced = 1;
                    break;
                }
            }
            if (!replaced)
            {
                strcat(Deftab, word);
            }
            strcat(Deftab, " ");
        }
        strcat(Deftab, "\n");
    }

    // Calculate end address based on current length of Deftab
    Namtabs[NamtabCount].end = strlen(Deftab) - 1;
    NamtabCount++;
}

void expandMacro(FILE *outputFile, char *macroName, char *argTab[], int macroArgCount)
{
    int macroIndex = isMacro(macroName);
    int macroStart = Namtabs[macroIndex].start;
    int macroEnd = Namtabs[macroIndex].end;
    Namtabs[macroIndex].clcnt++;

    int callCount = Namtabs[macroIndex].clcnt;

    // Print the arguments passed to the macro
    printf("Expanding macro: %s\n", macroName);
    printf("Arguments passed to macro:\n");
    for (int i = 0; i < macroArgCount; i++)
    {
        printf("argTab[%d]: %s\n", i, argTab[i]);
    }
    printf("\n");

    int i = macroStart;

    // Skip the first line (macro definition line)
    while (Deftab[i] != '\n' && i < macroEnd)
    {
        i++;
    }
    i++;  // Move to the next character after '\n'

    // Process the rest of the macro
    for (; i < macroEnd; i++)
    {
        char c = Deftab[i];

        if (c == '#')
        {
            int argNumber = Deftab[i + 1] - '0';
            fprintf(outputFile, "%s ", argTab[argNumber]);
            i++;
        }
        else if (Deftab[i] == '$')
        {
            fprintf(outputFile, "%d", callCount);
        }
        else
        {
            fprintf(outputFile, "%c", c);
        }
    }
    fprintf(outputFile, "\n");
}


int main()
{
    FILE *inputFile = fopen("input1.txt", "r");
    FILE *outputFile = fopen("output.txt", "w");

    if (!inputFile || !outputFile)
    {
        printf("Error opening files.\n");
        return 1;
    }

    char line[100];
    char *instructions[10];
    int instructionCount;

    while (fgets(line, 100, inputFile))
    {
        getInstructions(line, instructions, &instructionCount);
        if (instructionCount == 0)
        {
            continue;
        }
        if (strcmp(instructions[0], "END") == 0)
        {
            fprintf(outputFile, "END\n");
            break;
        }
        else if (strcmp(instructions[1], "MACRO") == 0)
        {
            defineMacro(inputFile, instructions, instructionCount);
        }
        else if (isMacro(instructions[0]) != -1)
        {
            // Handle macro expansion with possible label
            expandMacro(outputFile, instructions[0], &instructions[1], instructionCount - 1);
        }
        else if (isMacro(instructions[1]) != -1)
        {
            // Handle label + macro expansion
            fprintf(outputFile, "%s ", instructions[0]);  // Print the label
            expandMacro(outputFile, instructions[1], &instructions[2], instructionCount - 2);
        }
        else
        {
            for (int i = 0; i < instructionCount; i++)
            {
                fprintf(outputFile, "%s ", instructions[i]);
            }
            fprintf(outputFile, "\n");
        }
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Namtab:\n");
    for (int i = 0; i < NamtabCount; i++)
    {
        printf("%s\n", Namtabs[i].name);
        printf("Start Address: %d\n", Namtabs[i].start);
        printf("End Address: %d\n", Namtabs[i].end);
    }

    printf("\nDeftab:\n%s\n", Deftab);
    printf("Check output.txt for expanded code\n");
    return 0;
}