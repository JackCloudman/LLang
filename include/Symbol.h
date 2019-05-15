#ifndef __SYMBOL_H__
#define __SYMBOL_H__
#include "Lala.h"
#include <string.h>
/*entrada a tabla de simbolos,
es una lista simplemente ligada*/
typedef struct Symbol {
    char   *name;
    short   type;   /* VAR, BLTIN, UNDEF */

    union {
        LLObject* val;	       /* si es VAR */
        LLObject* (*ptr)();      /* sí es BLTIN */
    } u;

    struct Symbol   *next;  /* para ligarse a otro */
} Symbol;

Symbol *install(char *s,int t, LLObject*), *lookup(char *s);

typedef union Datum {   /* tipo de la pila del intérprete */
    LLObject*  val;
    Symbol  *sym; } Datum;

extern Datum pop();

typedef void (*Inst)();  /* instrucción de máquina */

#define STOP    (Inst) 0
extern  Inst prog[];

extern  void eval(), addo(), subo(), mulo(), divo(),negate();
extern void  assign(), bltin(), varpush(), constpush(), print();

#endif
