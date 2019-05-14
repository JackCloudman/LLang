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
        | list exp '\n'  {LL_FUNC_PRINT($2,"\n");}
  ;
exp:      object         { $$ = $1;}
        | exp '+' exp     { $$ = LL_FUNC_ADD($1,$3); }
        | exp '-' exp     { /*$$ = Complejo_sub($1,$3);*/  }
        | exp '*' exp     { /*$$ = Complejo_mul($1,$3); */ }
        | exp '/' exp     { /*$$ = Complejo_div($1,$3);*/  }
        | '(' exp ')'     { $$ = $2;}
  ;
%%
#include <stdio.h>
#include <ctype.h>
char *progname;
void main (int argc, char *argv[]){
  init();
  progname=argv[0];
    yyparse ();
}
void yyerror (char *s) {
  warning(s, (char *) 0);
}
void warning(char *s, char *t){
  fprintf (stderr, "%s: %s", progname, s);
  if(t)
    fprintf (stderr, " %s", t);
}