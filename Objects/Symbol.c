#include "Symbol.h"
static Symbol *symlist=0;    /* tabla de simbolos: lista ligada */

Symbol *lookup(char *s)    /* encontrar s en la tabla de símbolos */
{
    Symbol  *sp;
    for (sp = symlist; sp != (Symbol *)0; sp = sp->next){
        if (strcmp(sp->name, s)== 0)
            return sp;
    }
    return 0;      /* 0 ==> no se encontró */
}
Symbol* funclookup(char*s,Symbol* sl){
    Symbol  *sp;
    for (sp = sl; sp != (Symbol *)0; sp = sp->next){
        if (strcmp(sp->name, s)== 0)
            return sp;
    }
    return 0;      /* 0 ==> no se encontró */
}
/*La funcion install crea la variable en la tabla
de simbolos si esta que esta no existe*/
Symbol* funcinstall(Symbol** sl,char *s,int t,LLObject* o){
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
Symbol *install(char *s,int t,LLObject* o)
{
    Symbol *sp;
    char *emalloc();

    sp = (Symbol *) emalloc(sizeof(Symbol));

    sp->name = emalloc(strlen(s)+ 1) ; /* +1 para '\0' */
    strcpy(sp->name, s);

    sp->type = t;
    sp->u.val = o;
    sp->status = 0;
    sp->next  =  symlist;   /*  poner al frente de la lista   */
    symlist =  sp;
    return sp;
}

/*   revisar el regreso desde malloc  */
char  *emalloc(unsigned n){
    char *p;
    p =(char*) malloc(n);
    if(p == 0)
        perror("out of memory");
    return p;
}