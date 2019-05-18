#ifndef __STRING_OBJECT_H__
#define __STRING_OBJECT_H__
  #include "Object.h"
  #include <string.h>
  typedef struct LLStringObject{
    LLObject_HEAD
    int len;
    char *o_sval;
  }LLStringObject;

  LLTypeObject* LLStringTypeObject;

  int LLString_print(LLObject *o);
  LLStringObject* LLString_Make(char*);
  LLObject* LLString_CAT(LLObject*,LLObject*);
  LLObject* LLString_String(LLObject*);
  LLObject* LLString_MUL(LLObject*,LLObject*);
  int LLString_EQ(LLObject*,LLObject*);
#endif
