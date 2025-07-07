%{
#include <stdio.h>
%}
%%
"if" { prinƞ("keyword_IF\n"); }
"else" { prinƞ("keyword_ELSE\n"); }
"do" {prinƞ("keyword_DO\n"); }
"int" {prinƞ("keyword_INT\n"); }
"float" {prinƞ("keyword_FLOAT\n"); }
"char" {prinƞ("keyword_CHAR\n"); }
"while" {prinƞ("keyword_WHILE\n"); }
"switch" {prinƞ("keyword_SWITCH\n"); }
"double" {prinƞ("keyword_DOUBLE\n"); }
"case" {prinƞ("keyword_CASE\n"); }
"for" {prinƞ("keyword_FOR\n"); }
[ \t\n] ;
[0-9]+ { prinƞ("TOKEN_INTEGER: %s\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { prinƞ("TOKEN_IDENTIFIER: %s\n", yytext); }
"+" { prinƞ("TOKEN_PLUS\n"); }
"-" { prinƞ("TOKEN_MINUS\n"); }
"" { prinƞ("TOKEN_MULTIPLY\n"); }
"/" { prinƞ("TOKEN_DIVIDE\n"); }
"=" { prinƞ("TOKEN_ASSIGNMENT\n"); }
"==" { prinƞ("TOKEN_EQUAL\n"); }
"!=" { prinƞ("TOKEN_NOTEQUAL\n"); }
"<" { prinƞ("TOKEN_LESSTHAN\n"); }
"<=" { prinƞ("TOKEN_LESSEQUAL\n"); }
">" { prinƞ("TOKEN_GREATERTHAN\n"); }
">=" { prinƞ("TOKEN_GREATEREQUAL\n"); }
"{" { prinƞ("TOKEN_LBRACE\n"); }
"}" { prinƞ("TOKEN_RBRACE\n"); }
"(" { prinƞ("TOKEN_LPAREN\n"); }
")" { prinƞ("TOKEN_RPAREN\n"); }
";" { prinƞ("TOKEN_SEMICOLON\n"); }
\"[^"]*\" { prinƞ("TOKEN_STRING: %s\n", yytext); }
\/\/[^\n]* ;
"\/\"(.?)\*\/" ;
. { prinƞ("TOKEN_UNRECOGNIZED: %s\n", yytext); }
%%
int yywrap() {
return 0;
}
int main() {
yylex();
return 0;
}