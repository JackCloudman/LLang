#ifndef __LL_FLOAT_OBJECT_H__
#define __LL_FLOAT_OBJECT_H__
#include "Object.h"
#include "stringObject.h"
typedef struct LLFloatObject{
    LLObject_HEAD
    double o_val;
}LLFloatObject;
LLTypeObject* LLFloatTypeObject;
LLObject* LLFloat_String(LLObject *);
int LLFloat_print(LLObject*);
LLFloatObject* LLFloat_Make(double val);
LLObject* LLFloat_ADD(LLObject*,LLObject*);
LLObject* LLFloat_SUB(LLObject*,LLObject*);
LLObject* LLFloat_MUL(LLObject*,LLObject*);
LLObject* LLFloat_DIV(LLObject*,LLObject*);
#endif
