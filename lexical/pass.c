#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char opcode[20], operand[20], label[20], t1[20], t2[20], t3[20];
int locctr, start, len, s = -1, size = 0, opd;
FILE *fp1, *fp2, *fp3, *fp4, *fp5;

struct symtab
{
    char label[20];
    int addr;
} ST[30];

struct optab
{
    char opcode[20], hexcode[20];
} ot[30];

void read_OPTAB()
{
    int o = 0;
    while (fscanf(fp2, "%s%s", ot[o].opcode, ot[o].hexcode) != EOF && o < 30)
    {
        o++;
    }
}

void read_Line()
{
    strcpy(label, "");
    strcpy(opcode, "");
    strcpy(operand, "");
    if (fscanf(fp1, "%s", t1) != EOF)
    {
        if (fgetc(fp1) != '\n')
        {
            if (fscanf(fp1, "%s", t2) != EOF)
            {
                if (fgetc(fp1) != '\n')
                {
                    fscanf(fp1, "%s", t3);
                }
                else
                {
                    strcpy(t3, "");
                }
            }
            else
            {
                strcpy(t2, "");
            }
        }
        else
        {
            strcpy(t2, "");
        }

        if (strcmp(t2, "") == 0)
        {
            strcpy(opcode, t1);
        }
        else if (strcmp(t3, "") == 0)
        {
            strcpy(opcode, t1);
            strcpy(operand, t2);
        }
        else
        {
            strcpy(label, t1);
            strcpy(opcode, t2);
            strcpy(operand, t3);
        }
    }
}

int main()
{
    fp1 = fopen("input.txt", "r");
    fp2 = fopen("optab.txt", "r");
    fp3 = fopen("symtab.txt", "w");
    fp4 = fopen("outputdata.txt", "w");
    fp5 = fopen("length.txt", "w");

    if (!fp1 || !fp2 || !fp3 || !fp4 || !fp5)
    {
        printf("Error opening file(s).\n");
        return 1;
    }

    read_OPTAB();

    if (fscanf(fp1, "%s%s%x", label, opcode, &opd) != EOF && strcmp(opcode, "START") == 0)
    {
        start = opd;
        locctr = start;
        fprintf(fp4, "\t%s\t%s\t%x\n", label, opcode, opd);
        printf("\t%s\t%s\t%x\n", label, opcode, opd);
        read_Line();
    }
    else
    {
        locctr = 0;
    }

    while (strcmp(opcode, "END") != 0)
    {
        fprintf(fp4, "%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);
        printf("%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "") != 0)
        {
            int i;
            for (i = 0; i <= s; i++)
            {
                if (strcmp(ST[i].label, label) == 0)
                {
                    printf("Error: Duplicate label '%s'\n", label);
                    exit(1);
                }
            }
            s++;
            strcpy(ST[s].label, label);
            ST[s].addr = locctr;
        }

        int flag = 0;
        int i;
        for (i = 0; i < 30; i++)
        {
            if (strcmp(opcode, ot[i].opcode) == 0)
            {
                locctr += 3;
                size += 3;
                flag = 1;
                break;
            }
        }

        if (flag == 0)
        {
            if (strcmp(opcode, "WORD") == 0)
            {
                locctr += 3;
                size += 3;
            }
            else if (strcmp(opcode, "RESW") == 0)
            {
                locctr += 3 * atoi(operand);
            }
            else if (strcmp(opcode, "RESB") == 0)
            {
                locctr += atoi(operand);
            }
            else if (strcmp(opcode, "BYTE") == 0)
            {
                len = strlen(operand);
                if (operand[0] == 'C' || operand[0] == 'c')
                {
                    len = len - 3; // Exclude C' and '
                }
                else if (operand[0] == 'X' || operand[0] == 'x')
                {
                    len = (len - 3) / 2; // Exclude X' and '
                }
                locctr += len;
                size += len;
            }
        }

        read_Line();
    }

    fprintf(fp4, "%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    printf("%x\t%s\t%s\t%s\n", locctr, label, opcode, operand);

    printf("The length of the program: %x\n", locctr - start);
    int i;
    for (i = 0; i <= s; i++)
    {
        fprintf(fp3, "%s\t%x", ST[i].label, ST[i].addr);
        printf("%s\t%x", ST[i].label, ST[i].addr);
        if (i != s)
        {
            fprintf(fp3, "\n");
        }
        printf("\n");
    }

    fprintf(fp5, "%x\n%x", locctr - start, size);

    fclose(fp1);
    fclose(fp2);
    fclose(fp3);
    fclose(fp4);
    fclose(fp5);

    return 0;
}