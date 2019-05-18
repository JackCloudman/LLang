#ifndef __VM_H__
#define __VM_H__

#include "Symbol.h"
#include "abstract.h"
#include "Lala.h"
typedef union Datum {   /* tipo de la pila del intérprete */
    LLObject*  val;
    Symbol  *sym; } Datum;

extern Datum pop();

typedef void (*Inst)();  /* instrucción de máquina */

#define STOP    (Inst) 0
extern  Inst prog[];

void eval(), addo(), subo(), mulo(), divo(),negate();
void  assign(), bltin(), varpush(), constpush(), print(),makeArray(),execute(Inst* p);
void aArray(),ChangeValue(),getSubArray(),emptypush(),ifcode(),whilecode();
void gt(),ge(),lt(),le(),eq(),ne(),and(),or(),not();
#endif