#include "abstract.h"
#include "Lala.h"
extern LLTypeObject* LLIntTypeObject;
extern void execerror(char *s, char *t);
// Implementaciones
LLObject* bop1(LLObject* a,LLObject* b){
    LLObject *c,*d;
    c = a;
    d = b;
    if(a->ob_type==LLIntTypeObject){
        c = (LLObject*)LLFloat_Make((double)((LLIntObject*)a)->o_val);
    }
    if(b->ob_type==LLIntTypeObject){
        d = (LLObject*)LLFloat_Make((double)((LLIntObject*)b)->o_val);
    }
    LLObject* result = LLFloat_ADD(c,d);
    return result;
}

LLObject* bop2(LLObject* a,LLObject* b){
    LLObject *c,*d;
    c = a;
    d = b;
    if(a->ob_type==LLIntTypeObject){
        c = (LLObject*)LLFloat_Make((double)((LLIntObject*)a)->o_val);
    }
    if(b->ob_type==LLIntTypeObject){
        d = (LLObject*)LLFloat_Make((double)((LLIntObject*)b)->o_val);
    }
    LLObject* result = LLFloat_SUB(c,d);
    return result;
}


LLObject* bop3(LLObject* a,LLObject* b){
    LLObject *c,*d;
    c = a;
    d = b;
    if(a->ob_type==LLIntTypeObject){
        c = (LLObject*)LLFloat_Make((double)((LLIntObject*)a)->o_val);
    }
    if(b->ob_type==LLIntTypeObject){
        d = (LLObject*)LLFloat_Make((double)((LLIntObject*)b)->o_val);
    }
    LLObject* result = LLFloat_MUL(c,d);
    return result;
}


LLObject* bop4(LLObject* a,LLObject* b){
    LLObject *c,*d;
    c = a;
    d = b;
    if(a->ob_type==LLIntTypeObject){
        c = (LLObject*)LLFloat_Make((double)((LLIntObject*)a)->o_val);
    }
    if(b->ob_type==LLIntTypeObject){
        d = (LLObject*)LLFloat_Make((double)((LLIntObject*)b)->o_val);
    }
    LLObject* result = LLFloat_DIV(c,d);
    return result;
}

LLObject* LL_FUNC_ADD(LLObject* a,LLObject* b) {
    LLObject *result = 0;
    if((a->ob_type == LLListTypeObject) && (b->ob_type == LLListTypeObject)){
      result = (LLObject*) LLList_merge((LLEntryListObject*)a,(LLEntryListObject*)b);
    }else
        if((a->ob_type == LLIntTypeObject) && (b->ob_type == LLIntTypeObject)){
            result = LLInt_ADD(a,b);
        }
        else if ((a->ob_type == LLIntTypeObject || a->ob_type == LLFloatTypeObject ) && (b->ob_type == LLIntTypeObject || b->ob_type == LLFloatTypeObject)){
          result = bop1(a,b);
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
    }else if ((a->ob_type == LLIntTypeObject || a->ob_type == LLFloatTypeObject ) && (b->ob_type == LLIntTypeObject || b->ob_type == LLFloatTypeObject)){
        result = bop2(a,b);
    }
    if(result==LL_NOT_IMPLEMENTED)
        execerror("Operador '-' no esta implementado", NULL);
    return result;
}
LLObject* LL_FUNC_MUL(LLObject* a,LLObject* b){
    LLObject* result = 0;
    if ((a->ob_type == LLIntTypeObject) && (b->ob_type == LLIntTypeObject)) {
        result = LLInt_MUL(a, b);
    }else if ((a->ob_type == LLIntTypeObject || a->ob_type == LLFloatTypeObject ) && (b->ob_type == LLIntTypeObject || b->ob_type == LLFloatTypeObject)){
        result = bop3(a,b);
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
    }else if ((a->ob_type == LLIntTypeObject || a->ob_type == LLFloatTypeObject ) && (b->ob_type == LLIntTypeObject || b->ob_type == LLFloatTypeObject)){
        result = bop4(a,b);
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
LLObject* LL_FUNC_AACCESS(LLObject* l,LLObject* i){
  LLObject* result = 0;
  if((l->ob_type == LLListTypeObject)&&(i->ob_type==LLIntTypeObject)){
    result = LLList_getElement((LLEntryListObject*)l,((LLIntObject*)i)->o_val);
    if(!result)
      execerror("IndexError: list index out of range", NULL);
  }
  if(result==LL_NOT_IMPLEMENTED)
      execerror("Operador 'Access array [ ]' no esta implementado", NULL);
  return result;
}
LLObject* LL_FUNC_AREPLACE(LLObject* l,LLObject* i,LLObject*o){
  LLListObject* result = 0;
  if((l->ob_type == LLListTypeObject)&&(i->ob_type==LLIntTypeObject)){
    result = LLEntryList_getElement((LLEntryListObject*)l,((LLIntObject*)i)->o_val);
    if(!result)
      execerror("IndexError: list index out of range", NULL);
    result->o = o;
  }
  if(result==LL_NOT_IMPLEMENTED)
      execerror("Operador 'Access array [ ]' no esta implementado", NULL);
  return o;
}

LLObject* LL_FUNC_GETSUBARRAY(LLObject* l,LLObject* start,LLObject* end){
  LLObject* result = 0;
  int* s = 0;
  int* e = 0;
  if(l->ob_type == LLListTypeObject){
    if(start){
      if(start->ob_type==LLIntTypeObject){
        s = &(((LLIntObject*)start)->o_val);
      }else{
        execerror("Error Index Access ' [ ] start'", NULL);
      }
    }
    if(end){
      if(end->ob_type==LLIntTypeObject){
        e = &(((LLIntObject*)end)->o_val);
      }else{
        execerror("Error Index Access ' [ ] end'", NULL);
      }
    }
    result = (LLObject*)LLList_getrange((LLEntryListObject*)l,s,e);
    if(!result)
      return (LLObject*)LLEntryList_Make();
  }
  if(result==LL_NOT_IMPLEMENTED)
      execerror("Operador 'Access array [ ]' no esta implementado", NULL);
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
