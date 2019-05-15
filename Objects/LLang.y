%{
#include <stdio.h>
#include "Lala.h"
#include "abstract.h"
#include "Symbol.h"
extern void *code(Inst);
#define code2(c1,c2) code(c1); code(c2);
#define code3(c1,c2,c3) code(c1); code(c2); code(c3);

void execerror(char *s, char *t);
void yyerror (char *s);
int yylex ();
void warning(char *s, char *t);
extern void init();
extern void execute();
extern void initcode();
extern Inst *progp;
extern FILE *yyin;
int readfile = 0;
%}
%union {
  Symbol *sym;
  Inst *inst;
}
%token <sym> object VAR BLTIN INDEF EXIT
%type<inst> arraylist initarray

%right '='
%left '+' '-'
%left '*' '/'
%left UNARYMINUS
%%
list:
  | list'\n'
  | list asgn '\n' {code2((Inst)pop,STOP);return 1;}
  | list exp '\n'  { code2(print,STOP);return 1;}
  | list error '\n' {initcode();printf(">>> ");yyerrok;}
  ;
initarray: {code(makeArray);}
;
arraylist: arraylist','arraylist {}
      | exp {}
      | {$$=progp;}
;
asgn: VAR '=' exp {code3(varpush,(Inst)$1,assign);}
  ;
exp:  object  { code2(constpush,(Inst)$1);}
      | VAR       {code3(varpush,(Inst)$1,eval);}
      | asgn
      | exp '+' exp     { code(addo); }
      | exp '-' exp     { code(subo);  }
      | exp '*' exp     { code(mulo);}
      | exp '/' exp     { code(divo);}
      | '(' exp ')'     { }
      |BLTIN  '(' exp ')' {code2(bltin,(Inst)$1->u.ptr);}
      |'-' exp %prec UNARYMINUS {code(negate);}
      | EXIT {exit(0);}
      | initarray '['arraylist']' {code(STOP);}
      | exp '[' exp ']' {code(aArray);}
  ;
%%
#include <stdio.h>
#include <ctype.h>
#include <signal.h>
#include <setjmp.h>

char *progname;
jmp_buf begin;
int main (int argc, char *argv[]){
  progname=argv[0];
  init();
  if(argc==1){
    printf("Lala Lang v1.2 \n[GCC 8.2.1 20181127]\n");
    setjmp(begin);
    printf(">>> ");
    for(initcode(); yyparse (); initcode()){
      execute(prog);
      printf(">>> ");
    }
  }
  if(argc==2){
    readfile = 1;
    yyin = fopen(argv[1],"r");
    for(initcode();yyparse();initcode()){
      execute(prog);
    }
  }
  return 0;
}
void yyerror (char *s) {
  warning(s, (char *) 0);
}
void warning(char *s, char *t){
  fprintf (stderr, "%s",s);
  if(t)
    fprintf (stderr, "%s", t);
  fprintf(stderr,"\n");
}
void execerror(char *s, char *t)
{
	warning(s, t);
  if(readfile)
    exit(1);
  longjmp(begin, 0);
}
