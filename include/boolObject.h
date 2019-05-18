#ifndef __LL_BOOL_OBJECT_H__
#define __LL_BOOL_OBJECT_H__
#include "Object.h"
#include "stringObject.h"
typedef struct LLBoolObject{
    LLObject_HEAD
    short o_val;
}LLBoolObject;
LLTypeObject* LLBoolTypeObject;
LLObject* LLBool_String(LLObject *);
int LLBool_print(LLObject*);
LLBoolObject* LLBool_Make(short);
#endif