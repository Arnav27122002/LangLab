#include<stdio.h>
#include<string.h>
#include<stdlib.h>
void addZero(char field[10], int target)
{
    int left= target-strlen(field);
    char formatted[10];
    if(left>0)
    {
    for(int i=0; i<left; i++)
    {
            formatted[i]='0';
    }
    strcpy(formatted + left, field);
    }
    else
    {
        strcpy(field, formatted);
    }
}
void main(){
    FILE *fp=  fopen("outputdata.txt", "r");
    FILE *fp1= fopen("length.txt", "r");
    FILE *fp2= fopen("obj.txt", "w");
    char length[10], name[10], dummy[10], start[10], firstline[200];
    fgets(firstline, 200, fp);
    fread(length,1, 10, fp1);
    sscanf(firstline, "%s %s %s", name, dummy, start);
    addZero(name, 6);
    addZero(start, 6);
    addZero(length, 6);
    fprintf(fp2,"H^%s %s^ %s", name, start, length);
    printf("H^%s %s^ %s", name, start, length);
    printf("E^%s", start);
}