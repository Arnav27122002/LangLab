#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
void extractTokens();
int checkKeyword(char word[]);
char sourceCode[1000], buffer[100];
size_t len;
int main()
{
    FILE *fp= fopen("lex.l", "r");
    if(fp == NULL)
    {
        printf("error opening file\n");
        return 1;
    }
    else
    {len= fread(sourceCode, 1, 1000, fp);
    extractTokens();
    return 0;}
}

void extractTokens()
{
    int j;
    int i=0;
    do{
        if(sourceCode[i]=='#')
        {
            j=0;
            while(sourceCode[i]!='\n')
            {
            buffer[j]= sourceCode[i];
            j++;
            i++;
        }
        printf("TOKEN_PREPROCESSOR_DIRECTIVE:%s\n", buffer);
        buffer[j]='\0';
        }
        i++;
    } while(i<len);
}
int checkKeyword(char word[])
{
    char keyword[11][11]={"int", "char", "do", "while", "for", "if", "else", "switch", "case", "break", "return"};
    int i;
    for(i=0; i<11; i++)
    {
       if(strcmp(keyword[i], word)==0)
       {
            return 1;
        }
        else
        {
            return 0;
            }
      }
    }


