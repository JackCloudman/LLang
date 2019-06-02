%option noyywrap
%{
#include <stdio.h>
#include <stdlib.h>
#include "Object.h"
#include "Lala.h"
#include "y.tab.h"
extern LLIntObject* LLInt_Make(int);
extern LLStringObject* LLString_Make(char*);
void RmWs(char* str);
extern YYSTYPE yylval;
extern int lineno;
%}
/* Add your Flex definitions here              */
/* Some definitions are already provided to you*/
op [-+*\/()=]
ws [ \t]+
digits [0-9]
intnum (0|[1-9]+{digits}*)
floatnum (0|[1-9]+{digits}*)\.?{digits}*
STRING \"(\\.|[^"\\\n])*\"
true True
false False
none None
VAR [_]*[a-zA-Z][a-zA-Z0-9_]*
EXIT exit[\(][\)]
%%
> {return GT;}
>= {return GE;}
\< {return LT;}
\<= {return LE;}
== {return EQ;}
!= {return NE;}
not {return NOT;}
or {return OR;}
and {return AND;}
if {return IF;}
while {return WHILE;}
else {return ELSE;}
print {return PRINT;}
def {return FUNC;}
proc {return PROC;}
return {return RETURN;}
global {return GLOBAL;}
input {return INPUT;}
{true} {
    yylval.sym = install("",object,(LLObject*)LLBool_Make(1));
    return object;}
{false} {
    yylval.sym = install("",object,(LLObject*)LLBool_Make(0));
    return object;}
{none} {
    yylval.sym = install("",object,(LLObject*)LLNone_Make());
    return object;}
{VAR} {
  Symbol *s;
  if((s=lookup(yytext))==0)
    s = install(yytext,INDEF,(LLObject*)LLNone_Make());
  yylval.sym = s;
  return s->type==INDEF?VAR:s->type;
}
{intnum} {
 int dato;
 RmWs(yytext);
 sscanf(yytext,"%d",&dato);
 yylval.sym =  install("",object,(LLObject*) LLInt_Make(dato));
 return object;}
{floatnum} {
 double dato;
 RmWs(yytext);
 sscanf(yytext,"%lf",&dato);
 yylval.sym =  install("",object,(LLObject*) LLFloat_Make(dato));
 return object;}
{op} {return *yytext;}
\n {lineno++;return *yytext;}
{ws} { /* Do nothing */ }
[\[|\]|,:] {return *yytext;}
. { return *yytext; }
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