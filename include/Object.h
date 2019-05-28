#ifndef __OBJECT_H__
#define __OBJECT_H__
  #include <stdlib.h>
  #include <stdio.h>
  #include<string.h>

//  #define LLMEM(LLObject) (LLObject*)calloc(1,sizeof(LLObject))
  typedef struct _typeobject{
    char *name;
  }LLTypeObject;
  typedef struct _object LLObject;
typedef void (*Inst)();  /* instrucción de máquina */
typedef struct Symbol {
    char   *name;
    short   type;   /* VAR, BLTIN, UNDEF */
    short status;
    union {
        LLObject* val;	       /* si es VAR */
        LLObject* (*ptr)();      /* sí es BLTIN */
        Inst defn;
    } u;
    int nargs;
    struct Symbol   *next;  /* para ligarse a otro */
} Symbol;
  #define LLObject_HEAD LLTypeObject *ob_type; \
                        int (*print)(LLObject*); \
                        LLObject* (*to_String)(LLObject*); \
                        Symbol* attribute;
  typedef struct _object{
      LLObject_HEAD
    }LLObject;
  typedef LLObject *APLLObject;
Symbol* Attributelookup(char*s,Symbol* sl),*Attributeinstall(Symbol** sl,char *s,int t,LLObject* o);
Symbol *install(char *s,int t, LLObject*), *lookup(char *s),*funclookup(char*s,Symbol*),*funcinstall(Symbol**,char *,int,LLObject*);
typedef void (*Inst)();
#endif
