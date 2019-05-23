#ifndef __SYMBOL_H__
#define __SYMBOL_H__
#include "Lala.h"
#include <string.h>
typedef void (*Inst)();  /* instrucción de máquina */
/*entrada a tabla de simbolos,
es una lista simplemente ligada*/
typedef struct Symbol {
    char   *name;
    short   type;   /* VAR, BLTIN, UNDEF */
    short status;
    union {
        LLObject* val;	       /* si es VAR */
        LLObject* (*ptr)();      /* sí es BLTIN */
        Inst defn;
    } u;

    struct Symbol   *next;  /* para ligarse a otro */
} Symbol;

Symbol *install(char *s,int t, LLObject*), *lookup(char *s),*funclookup(char*s,Symbol*),*funcinstall(Symbol**,char *,int,LLObject*);
typedef void (*Inst)();
#endif
