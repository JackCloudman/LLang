%{
#include <stdio.h>
#include "Object.h"
#include "Lala.h"
#include "vm.h"
#include "abstract.h"
#include "Symbol.h"
extern void *code(Inst);
#define code2(c1,c2) code(c1); code(c2);
#define code3(c1,c2,c3) code(c1); code(c2); code(c3);

int indef;//Para saber si un return esta fuera de una funcion
void defnonly( char *s );
void execerror(char *s, char *t);
void yyerror (char *s);
int yylex ();
void warning(char *s, char *t);
extern void init();
extern void execute();
extern void initcode();
extern Inst *progp;
extern FILE *yyin;
extern Inst   *progbase;
int readfile = 0;
%}
%union {
  Symbol *sym; //Tabla de simbolos
  Inst *inst; //Instruccion de maquina virtual
  int narg; //Numero de argumentos
}
%token <sym> FUNCTION RETURN FUNC PROC
%token <sym> object VAR BLTIN INDEF EXIT IF ELSE PRINT WHILE GLOBAL
%type<inst> arraylist initarray asgn exp stmt stmtlist cond if end while begin
%type <sym> procname
%type <narg> arglist argdef

%right '='
%left OR
%left AND
%left GT GE LT LE EQ NE
%left '+' '-'
%left '*' '/'
%left UNARYMINUS NOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE
%%
list:
  | list'\n'
  | list asgn '\n' {code2((Inst)pop,STOP);return 1;}
  | list exp '\n'  { code2(print,STOP);return 1;}
  | list error '\n' {initcode();printf(">>> ");yyerrok;}
  | list stmt '\n' {code(STOP);return 1;}
  | list defn '\n' {code(STOP);return 1;}
  ;
initarray: {code(makeArray);}
;
arraylist: arraylist','arraylist {}
      | exp {}
      | {$$=progp;}
;
asgn: VAR '=' exp { if($1->status==1){
                        code3(varpush,(Inst)$1,assign);}
                    else{
                        code3(varfuncpush,(Inst)$1,assign);
                        }
                  }
    | exp '[' exp ']' '=' exp {code(ChangeValue);}
    | VAR'.'VAR '=' exp {if($1->status==1){ //Variable global
                       code2(varpush,(Inst)$1);
                       }else{
                       code2(varfuncpush,(Inst)$1);
                       }
                       code2(atribassign,(Inst)$3);
                       }
;
stmt: exp {code((Inst)pop);}
    | PRINT exp { code(print); $$ = $2;}
    | while cond stmt end {
        ($1)[1] = (Inst)$3;
        ($1)[2] = (Inst)$4;
      }
    | if cond stmt end  %prec LOWER_THAN_ELSE{
        ($1)[1] = (Inst)$3;
        ($1)[3] = (Inst)$4;
      }
    | if cond stmt end ELSE stmt end {
        ($1)[1] = (Inst)$3;
        ($1)[2] = (Inst)$6;
        ($1)[3] = (Inst)$7;
      }
    | '{' stmtlist '}' {printf("...");$$=$2;}
    | RETURN { defnonly("return"); code(procret); }
    | RETURN exp {defnonly( "return" ); $$ = $2; code(funcret);}
;
defn:    FUNC procname { $2->type=FUNCTION; indef=1; }
          '('argdef')' stmt'\n' {code(procret); define($2,$5);indef=0;}
        | GLOBAL VAR {$2->status=1;$2->type=VAR;}
;

argdef:  /* nada */   { $$ = 0; }
    | VAR                 {$$ = 1;code2(varfuncpush,(Inst)$1);code2(defassign,(Inst)$$); }
    | argdef ',' VAR     { $$ = $1 + 1;code2(varfuncpush,(Inst)$3);code2(defassign,(Inst)$$);}
;
arglist:  /* nada */   { $$ = 0; }
    | exp                 { $$ = 1; }
    | arglist ',' exp     { $$ = $1 + 1; }
;
procname: VAR
   | FUNCTION
;
cond: exp  {code(STOP);$$=$1;}
;
if: IF {$$=code(ifcode);code3(STOP,STOP,STOP);}
  ;
while: WHILE {$$= code3(whilecode,STOP,STOP);}
  ;
end:  '\n'{code(STOP);$$=progp;}
  ;
begin:  /* nada */          { $$ = progp; }
;
stmtlist: {$$=progp;}
      | stmtlist '\n' {printf("... ");}
      | stmtlist stmt
;
exp:  object  { code2(constpush,(Inst)$1);}
      | VAR       {if($1->status==1){ //Variable global
                     code3(varpush,(Inst)$1,eval);
                   }else{
                     code3(varfuncpush,(Inst)$1,eval);
                  }
                  }
      | asgn
      | exp '+' exp     { code(addo); }
      | exp '-' exp     { code(subo);  }
      | exp '*' exp     { code(mulo);}
      | exp '/' exp     { code(divo);}
      | '(' exp ')'     { }
      |BLTIN  '(' exp ')' {code2(bltin,(Inst)$1->u.ptr);}
      |'-' exp %prec UNARYMINUS {code(negate);}
      | exp GT exp {code(gt);}
      | exp GE exp {code(ge);}
      | exp LT exp {code(lt);}
      | exp LE exp {code(le);}
      | exp EQ exp {code(eq);}
      | exp NE exp {code(ne);}
      | exp AND exp {code(and);}
      | exp OR exp {code(or);}
      | NOT exp {$$=$2;code(not);}
      | EXIT {exit(0);}
      | initarray '['arraylist']' {code(STOP);}
      | exp '[' exp ']' {code(aArray);}
      | exp '[' index ':' index ']' {code(getSubArray);}
      | FUNCTION begin '(' arglist ')'
         { $$ = $2; code3(call,(Inst)$1,(Inst)$4); }
      | VAR'.'VAR {if($1->status==1){ //Variable global
                                     code2(varpush,(Inst)$1);
                                   }else{
                                     code2(varfuncpush,(Inst)$1);
                                  }
                                  code2(attributepush,(Inst)$3);
                 }
  ;
index: exp {}
| {code(emptypush);}
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
    printf("Lala Lang v1.6 \n[GCC 8.2.1 20181127]\n");
    setjmp(begin);
    printf(">>> ");
    for(initcode(); yyparse (); initcode()){
      execute(progbase);
      printf(">>> ");
    }
  }
  if(argc==2){
    readfile = 1;
    yyin = fopen(argv[1],"r");
    for(initcode();yyparse();initcode()){
      execute(progbase);
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
void defnonly( char *s )     /* advertena la si hay definición i legal */
{
if (!indef)
	execerror(s, "used outside definition");
}