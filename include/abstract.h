#ifndef __LL_ABSTRACT_H__
#define __LL_ABSTRACT_H__

#include "Lala.h"

LLObject* LL_FUNC_ADD(LLObject*,LLObject*);
/*LLObject* LL_FUNC_SUB(LLObject*,LLObject*);
LLObject* LL_FUNC_MUL(LLObject*,LLObject*);
LLObject* LL_FUNC_DIV(LLObject*,LLObject*);
LLObject* LL_FUNC_NEGATE(LLObject*);*/
int LL_FUNC_PRINT(LLObject*,char*);
#define LL_NOT_IMPLEMENTED 0
#endif