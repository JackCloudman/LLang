#include "abstract.h"
#include "Lala.h"
extern LLTypeObject* LLIntTypeObject;
// Implementaciones
LLObject* LL_FUNC_ADD(LLObject* a,LLObject* b) {
    LLObject *result = 0;
    if ((a->ob_type == LLIntTypeObject) && (b->ob_type == LLIntTypeObject)){
        result = LLInt_ADD(a, b);
    } else {
        if ((a->ob_type == LLStringTypeObject)&& (b->ob_type == LLStringTypeObject)) {
            result = LLString_CAT(a, b);
        }else{
            if(a->ob_type==LLStringTypeObject){
                result = LLString_CAT(a,b->to_String(b));
            }else if(b->ob_type==LLStringTypeObject){
                result = LLString_CAT(a->to_String(a),b);
            }
        }
    }
    if (result == LL_NOT_IMPLEMENTED)
            return 0;
    return result;
}
/*
LLObject* LL_FUNC_SUB(LLObject*,LLObject*);
LLObject* LL_FUNC_MUL(LLObject*,LLObject*);
LLObject* LL_FUNC_DIV(LLObject*,LLObject*);
LLObject* LL_FUNC_NEGATE(LLObject*);*/


int LL_FUNC_PRINT(LLObject* o,char* end){
    if(o==0){
        return 0;
    }
    o->print(o);
    if(end!=NULL){
        printf("%s",end);
    }
    return 0;
}