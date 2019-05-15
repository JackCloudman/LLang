%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include "Lala.h"
#include "Symbol.h"
#include "y.tab.h"
extern LLIntObject* LLInt_Make(int);
extern LLStringObject* LLString_Make(char*);
void RmWs(char* str);
extern YYSTYPE yylval;
%}
/* Add your Flex definitions here              */
/* Some definitions are already provided to you*/
op [-+*\/()=]
ws [ \t]+
digits [0-9]
number (0|[1-9]+{digits}*)\.?{digits}*
STRING \"(\\.|[^"\\])*\"
VAR [_]*[a-zA-Z][a-zA-Z0-9_]*
EXIT exit[\(][\)]
%%
{VAR} {
  Symbol *s;
  if((s=lookup(yytext))==0)
    s = install(yytext,INDEF,0);
  yylval.sym = s;
  return s->type==INDEF?VAR:s->type;
}
{number} {
 int dato;
 RmWs(yytext);
 sscanf(yytext,"%d",&dato);
 yylval.sym =  install("",object,(LLObject*) LLInt_Make(dato));
 return object;}
{op} |
\n {return *yytext;}
{ws} { /* Do nothing */ }
[\[|\]|,] {return *yytext;}
. { /* Do nothing */ }
{STRING} {
    yylval.sym =  install("",object,(LLObject*)LLString_Make(yytext));
    return object;
  }
{EXIT} {return EXIT;}
%%
void RmWs(char* str) {
  int i = 0, j = 0;
  char temp[strlen(str) + 1];
  strcpy(temp, str);
  while (temp[i] != '\0') {
    while (temp[i] == ' ')
      i++;
    str[j] = temp[i];
    i++;
    j++;
  }
 str[j] = '\0';
}
