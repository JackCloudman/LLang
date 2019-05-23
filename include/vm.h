#ifndef __VM_H__
#define __VM_H__

#include "Symbol.h"
#include "abstract.h"
#include "Lala.h"
typedef union Datum {   /* tipo de la pila del intérprete */
    LLObject*  val;
    Symbol  *sym; } Datum;

typedef struct Frame {     /* nivel da pila par» Huida a proc/func */
    Symbol  *sp;         /* entrada en la tabla da simbolos */
    Inst    *retpc;   /* dónde reanudar después del retorno */
    Datum  *argn;     /* n-esimo argumento en la pila */
    int    nargs;     /* número da argumentos */
    Symbol* vars;
} Frame;
extern Datum pop();

typedef void (*Inst)();  /* instrucción de máquina */

#define STOP    (Inst) 0
extern  Inst prog[];
#define NFRAME  1000
Frame  frame[NFRAME] ;
Frame   *fp;  /* apuntador a nivel */

void eval(), addo(), subo(), mulo(), divo(),negate();
void  assign(), bltin(), varpush(), constpush(), print(),makeArray(),execute(Inst* p),varfuncpush();
void aArray(),ChangeValue(),getSubArray(),emptypush(),ifcode(),whilecode();
void gt(),ge(),lt(),le(),eq(),ne(),and(),or(),not();
void call(), arg(), argassign();
void funcret(), procret(),define();
#endif