#ifndef __LL_ABSTRACT_H__
#define __LL_ABSTRACT_H__

#include "Lala.h"

LLObject* LL_FUNC_ADD(LLObject*,LLObject*);
LLObject* LL_FUNC_SUB(LLObject*,LLObject*);
LLObject* LL_FUNC_MUL(LLObject*,LLObject*);
LLObject* LL_FUNC_DIV(LLObject*,LLObject*);
LLObject* LL_FUNC_NEGATE(LLObject*);
LLObject* LL_FUNC_AACCESS(LLObject*,LLObject*);
int LL_FUNC_PRINT(LLObject*,char*);
LLObject* LL_FUNC_AREPLACE(LLObject*,LLObject*,LLObject*);
LLObject* LL_FUNC_GETSUBARRAY(LLObject*,LLObject*,LLObject*);
double LL_CONDITION_EVAL(LLObject*);
LLObject* LL_FUNC_GT(LLObject*,LLObject*);
LLObject* LL_FUNC_LT(LLObject*,LLObject*);
LLObject* LL_FUNC_GE(LLObject*,LLObject*);
LLObject* LL_FUNC_LE(LLObject*,LLObject*);
LLObject* LL_FUNC_EQ(LLObject*,LLObject*);
LLObject* LL_FUNC_NE(LLObject*,LLObject*);
LLObject* LL_FUNC_AND(LLObject*,LLObject*);
LLObject* LL_FUNC_OR(LLObject*,LLObject*);
LLObject* LL_FUNC_NOT(LLObject*);
LLObject* LL_FUNC_LEN(LLObject*);
LLObject* LL_FUNC_GET_ATTRIB(LLObject* a,char*name);
LLObject* LL_FUNC_ATTRIB_ASSIGN(LLObject* a,LLObject*b,char* name);
LLObject* LL_FUNC_INFO(LLObject*);
#define LL_NOT_IMPLEMENTED 0
#endif
