#ifndef __LL_INT_OBJECT_H__
#define __LL_INT_OBJECT_H__
  #include "Object.h"
  #include "stringObject.h"
  typedef struct LLIntObject{
    LLObject_HEAD
    int len;
    int o_val;
  }LLIntObject;
LLTypeObject* LLIntTypeObject;
  LLObject* LLInt_String(LLObject *);
  int LLInt_print(LLObject*);
  LLIntObject* LLInt_Make(int val);
  LLObject* LLInt_ADD(LLObject*,LLObject*);
#endif
