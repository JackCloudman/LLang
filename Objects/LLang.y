%{
#include <stdio.h>
#include "Lala.h"
#include "abstract.h"
#include "Symbol.h"
void yyerror (char *s);
int yylex ();
void warning(char *s, char *t);
extern void init();
%}
%union {
  LLObject* val;
  Symbol *sym;
}
%token <val> object
%token <sym> VAR BLTIN INDEF
%type <val> exp asgn

%right '='
%left '+' '-'
%left '*' '/'
%%
list:
  | list'\n'
  | list exp '\n'  {LL_FUNC_PRINT($2,"\n");printf(">>> ");}
  | list asgn '\n' {printf(">>> ");}
  | list error '\n' {yyerrok;}
  ;
asgn: VAR '=' exp {$$=$1->u.val=$3; $1->type=VAR;}
  ;
exp:      object         { $$ = $1;}
        | VAR     {if($1->type == INDEF)
                    printf("Error: '%s' no esta definido\n",$1->name);
                  $$ = $1->u.val;}
        | asgn
        | exp '+' exp     { $$ = LL_FUNC_ADD($1,$3); }
        | exp '-' exp     { $$ = LL_FUNC_SUB($1,$3);  }
        | exp '*' exp     { $$ = LL_FUNC_MUL($1,$3);}
        | exp '/' exp     { $$ = LL_FUNC_DIV($1,$3);  }
        | '(' exp ')'     { $$ = $2;}
        |BLTIN  '(' exp ')' { $$=(*($1->u.ptr))($3);}
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
