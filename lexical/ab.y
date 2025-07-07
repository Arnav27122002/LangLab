%{
#include <stdio.h>
#include <stdlib.h>

extern int yylex(void);
void yyerror(const char *s);
%}

%token A B

%%
S: A A A A A T B  /* Ensure at least 5 a's followed by exactly 1 b */
 ;

T: /* empty */
 | A T  /* Match additional 'a's */
 ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter a string (a^n b where n >= 5): ");
    if (yyparse() == 0)
        printf("String accepted!\n");
    else
        printf("String rejected.\n");
    return 0;
}