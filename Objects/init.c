#include "Lala.h"
#include "abstract.h"
#include "Symbol.h"
#include "y.tab.h"
static struct {	/*	Predefinidos */
    char *name;
    LLObject* (*func)();
} builtins[] =	{
        "len",	LL_FUNC_LEN,
        0,	0
};
void init(){
  Symbol *s;
  LLIntTypeObject = calloc(1,sizeof(LLTypeObject));
  LLStringTypeObject = calloc(1,sizeof(LLTypeObject));
  LLListTypeObject = calloc(1,sizeof(LLTypeObject));
  LLFloatTypeObject = calloc(1,sizeof(LLTypeObject));
  LLBoolTypeObject = calloc(1,sizeof(LLTypeObject));
  LLNoneTypeObject = calloc(1,sizeof(LLTypeObject));
  char* c = 0;
  c = malloc(sizeof(char)*13);
  strcpy(c,"<type 'int'>\0");
  LLIntTypeObject->name = c;
  c = malloc(sizeof(char)*13);
  strcpy(c,"<type 'str'>\0");
  LLStringTypeObject->name = c;
  c = malloc(sizeof(char)*14);
  strcpy(c,"<type 'list'>\0");
  LLListTypeObject->name = c;
  c = malloc(sizeof(char)*15);
  strcpy(c,"<type 'float'>\0");
  LLFloatTypeObject->name = c;
  c = malloc(sizeof(char)*15);
  strcpy(c,"<type 'Bool'>\0");
  LLBoolTypeObject->name = c;
  c = malloc(sizeof(char)*14);
  strcpy(c,"<type 'None'>\0");
  LLNoneTypeObject->name = c;

  for (int i = 0; builtins[i].name; i++) {
        s = install(builtins[i].name, BLTIN, (LLObject*)LLNone_Make());
        s->u.ptr = builtins[i].func;
    }
  return;
}