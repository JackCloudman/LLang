#ifndef __LL_NONE_OBJECT_H__
#define __LL_NONE_OBJECT_H__
#include "Object.h"
#include "stringObject.h"
typedef struct LLNoneObject{
    LLObject_HEAD
}LLNoneObject;
LLTypeObject* LLNoneTypeObject;
LLObject* LLNone_String(LLObject *);
int LLNone_print(LLObject*);
LLNoneObject* LLNone_Make();
#endif