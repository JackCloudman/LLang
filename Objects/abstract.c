#include "abstract.h"
#include "Lala.h"
extern LLTypeObject* LLIntTypeObject;
extern void execerror(char *s, char *t);
// Implementaciones
LLObject* LL_FUNC_ADD(LLObject* a,LLObject* b) {
    LLObject *result = 0;
    if((a->ob_type == LLListTypeObject) && (b->ob_type == LLListTypeObject)){
      result = (LLObject*) LLList_merge((LLEntryListObject*)b,(LLEntryListObject*)a);
    }else
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
    if(result==LL_NOT_IMPLEMENTED)
        execerror("Operador '+' no esta implementado", NULL);
    return result;
}
LLObject* LL_FUNC_SUB(LLObject* a,LLObject* b){
    LLObject* result = 0;
    if ((a->ob_type == LLIntTypeObject) && (b->ob_type == LLIntTypeObject)) {
        result = LLInt_SUB(a, b);
    }
    if(result==LL_NOT_IMPLEMENTED)
        execerror("Operador '-' no esta implementado", NULL);
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
    if(result==LL_NOT_IMPLEMENTED)
        execerror("Operador '*' no esta implementado", NULL);
    return result;
}
LLObject* LL_FUNC_DIV(LLObject* a,LLObject* b){
    LLObject* result = 0;
    if ((a->ob_type == LLIntTypeObject) && (b->ob_type == LLIntTypeObject)) {
        result = LLInt_DIV(a, b);
    }
    if(result==LL_NOT_IMPLEMENTED)
        execerror("Operador '/' no esta implementado", NULL);
    return result;
}
LLObject* LL_FUNC_NEGATE(LLObject* a){
    LLObject* result = 0;
    if (a->ob_type == LLIntTypeObject) {
        result = (LLObject*)LLInt_Make(-((LLIntObject*)a)->o_val);
    }
    if(result==LL_NOT_IMPLEMENTED)
        execerror("Operador 'unary -' no esta implementado", NULL);
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
