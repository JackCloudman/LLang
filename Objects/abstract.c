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
    return result;
}
LLObject* LL_FUNC_SUB(LLObject* a,LLObject* b){
    LLObject* result = 0;
    if ((a->ob_type == LLIntTypeObject) && (b->ob_type == LLIntTypeObject)) {
        result = LLInt_SUB(a, b);
    }
    return result;
}
LLObject* LL_FUNC_MUL(LLObject* a,LLObject* b){
    LLObject* result = 0;
    if ((a->ob_type == LLIntTypeObject) && (b->ob_type == LLIntTypeObject)) {
        result = LLInt_MUL(a, b);
    }else if ((a->ob_type == LLStringTypeObject)&&(b->ob_type == LLIntTypeObject)){
        result = LLString_MUL(a,b);
    }else if((a->ob_type == LLIntTypeObject)&&(b->ob_type == LLStringTypeObject)){
        result = LLString_MUL(b,a);
    }
    return result;
}
LLObject* LL_FUNC_DIV(LLObject* a,LLObject* b){
    LLObject* result = 0;
    if ((a->ob_type == LLIntTypeObject) && (b->ob_type == LLIntTypeObject)) {
        result = LLInt_DIV(a, b);
    }
    return result;
}


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