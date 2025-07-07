#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char lines[100]; 

struct nam {
    char label[30];
    int start;
    int end;
} names[10];

struct def {
    char label[30];
    char opcode[30];
    char operand[30];
} defs[100];

int main() {
    int parts;
    int isMacro = 0;
    int namIndex = 0;
    int defIndex = 0;
    int lineCounter = 0;

    FILE *fp = fopen("macro.txt", "r");
    if (fp == NULL) {
        printf("Error: Could not open file\n");
        return 1;
    }

    char label[30], opcode[30], operand[30];
    char word1[30], word2[30], word3[30];

    while (fgets(lines, 100, fp)) {
        lineCounter++;
        parts = sscanf(lines, "%s %s %s", word1, word2, word3);

        if (parts == 1) {
            strcpy(opcode, word1);
        } else if (parts == 2) {
            strcpy(opcode, word1);
            strcpy(operand, word2);
        } else if (parts == 3) {
            strcpy(label, word1);
            strcpy(opcode, word2);
            strcpy(operand, word3);
        } 

        if (strcmp(opcode, "MACRO") == 0) {
            isMacro = 1;
            strcpy(names[namIndex].label, label);
            names[namIndex].start = defIndex;
        } else if (isMacro && strcmp(opcode, "MEND") == 0) {
            isMacro = 0;
            names[namIndex].end = defIndex;
            namIndex++;
        } else if (isMacro) {
            strcpy(defs[defIndex].opcode, opcode);
            strcpy(defs[defIndex].operand, operand);
            defIndex++;
        }
    
    }

    fclose(fp);

    // Print the NAM table
    printf("\nName Table:\n");
    printf("Label\tStart\tEnd\n");
    for (int i = 0; i < namIndex; i++) {
        printf("%s\t%d\t%d\n", names[i].label, names[i].start, names[i].end);
    }

    // Print the DEF table
    printf("\nDefinition Table:\n");
    printf("Label\tOpcode\tOperand\n");
    for (int i = 0; i < defIndex; i++) {
        printf("%s\t%s\t%s\n", defs[i].label, defs[i].opcode, defs[i].operand);
    }

    return 0;
}
