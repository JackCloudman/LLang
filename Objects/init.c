#include "Lala.h"
extern LLTypeObject* LLIntTypeObject;
extern LLTypeObject* LLStringTypeObject;
extern LLTypeObject* LLListTypeObject;
void init(){
  LLIntTypeObject = calloc(1,sizeof(LLTypeObject));
  LLStringTypeObject = calloc(1,sizeof(LLTypeObject));
  LLListTypeObject = calloc(1,sizeof(LLTypeObject));
  LLFloatTypeObject = calloc(1,sizeof(LLTypeObject));
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
  return;
}