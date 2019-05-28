#include "Object.h"

Symbol* Attributelookup(char*s,Symbol* sl){
    Symbol  *sp;
    for (sp = sl; sp != (Symbol *)0; sp = sp->next){
        if (strcmp(sp->name, s)== 0)
            return sp;
    }
    return 0;      /* 0 ==> no se encontró */
}

Symbol* Attributeinstall(Symbol** sl,char *s,int t,LLObject* o){
    Symbol *sp;
    char *emalloc();

    sp = (Symbol *) emalloc(sizeof(Symbol));

    sp->name = emalloc(strlen(s)+ 1) ; /* +1 para '\0' */
    strcpy(sp->name, s);

    sp->type = t;
    sp->u.val = o;
    sp->status = 0;
    sp->next  =  *sl;   /*  poner al frente de la lista   */
    *sl = sp;
    return sp;
}