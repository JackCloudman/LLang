%{
#include <stdio.h>
#include "Lala.h"
#include "abstract.h"
void yyerror (char *s);
int yylex ();
void warning(char *s, char *t);
extern void init();
%}
%token object
%left '+' '-'
%left '*' '/'
%%
list:
  | list'\n'
        | list exp '\n'  {LL_FUNC_PRINT($2,"\n");printf(">>> ");}
  ;
exp:      object         { $$ = $1;}
        | exp '+' exp     { $$ = LL_FUNC_ADD($1,$3); }
        | exp '-' exp     { $$ = LL_FUNC_SUB($1,$3);  }
        | exp '*' exp     { $$ = LL_FUNC_MUL($1,$3);}
        | exp '/' exp     { $$ = LL_FUNC_DIV($1,$3);  }
        | '(' exp ')'     { $$ = $2;}
  ;
%%
#include <stdio.h>
#include <ctype.h>
char *progname;
int main (int argc, char *argv[]){
  init();
  printf(">>> ");
  progname=argv[0];
    yyparse ();
  return 0;
}
void yyerror (char *s) {
  warning(s, (char *) 0);
}
void warning(char *s, char *t){
  fprintf (stderr, "%s: %s", progname, s);
  if(t)
    fprintf (stderr, " %s", t);
}