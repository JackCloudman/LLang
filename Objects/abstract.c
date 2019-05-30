#include "abstract.h"
#include "Lala.h"
#include "y.tab.h"
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
double LL_CONDITION_EVAL(LLObject* o){
    double result = 0;
    if(o==NULL)
        return result;
    if(o->ob_type==LLBoolTypeObject){
        result = (double)((LLBoolObject*)o)->o_val;
    }
    if(o->ob_type==LLListTypeObject){
        result =(double) ((LLEntryListObject*)o)->len;
    }
    if(o->ob_type==LLIntTypeObject){
        result =(double) ((LLIntObject*)o)->o_val;
    }
    if(o->ob_type==LLFloatTypeObject){
        result = (((LLFloatObject*)o)->o_val);
    }
    if(o->ob_type==LLStringTypeObject){
        result = (double)((LLStringObject*)o)->len;
    }
    return result;
}
LLObject* LL_FUNC_GT(LLObject* a,LLObject* b){
    int r1,r2;
    if((a->ob_type!=b->ob_type)&&((a->ob_type == LLIntTypeObject || a->ob_type == LLFloatTypeObject ) && (b->ob_type == LLIntTypeObject || b->ob_type == LLFloatTypeObject)))
        execerror("No se puede comparar!", NULL);
    r1 = LL_CONDITION_EVAL(a);
    r2 = LL_CONDITION_EVAL(b);
    return (LLObject*)LLBool_Make(r1>r2);
}
LLObject* LL_FUNC_LT(LLObject*a,LLObject*b){
    int r1,r2;
    if((a->ob_type!=b->ob_type)&&((a->ob_type == LLIntTypeObject || a->ob_type == LLFloatTypeObject ) && (b->ob_type == LLIntTypeObject || b->ob_type == LLFloatTypeObject)))
        execerror("No se puede comparar!", NULL);
    r1 = LL_CONDITION_EVAL(a);
    r2 = LL_CONDITION_EVAL(b);
    return (LLObject*)LLBool_Make(r1<r2);
}
LLObject* LL_FUNC_GE(LLObject*a,LLObject*b){
    int r1,r2;
    if((a->ob_type!=b->ob_type)&&((a->ob_type == LLIntTypeObject || a->ob_type == LLFloatTypeObject ) && (b->ob_type == LLIntTypeObject || b->ob_type == LLFloatTypeObject)))
        execerror("No se puede comparar!", NULL);
    r1 = LL_CONDITION_EVAL(a);
    r2 = LL_CONDITION_EVAL(b);
    return (LLObject*)LLBool_Make(r1>=r2);
}
LLObject* LL_FUNC_LE(LLObject*a,LLObject*b){
    int r1,r2;
    if((a->ob_type!=b->ob_type)&&((a->ob_type == LLIntTypeObject || a->ob_type == LLFloatTypeObject ) && (b->ob_type == LLIntTypeObject || b->ob_type == LLFloatTypeObject)))
        execerror("No se puede comparar!", NULL);
    r1 = LL_CONDITION_EVAL(a);
    r2 = LL_CONDITION_EVAL(b);
    return (LLObject*)LLBool_Make(r1<=r2);
}
LLObject* LL_FUNC_EQ(LLObject*a,LLObject*b){
    int r1,r2;
    if((a->ob_type!=b->ob_type)&&((a->ob_type == LLIntTypeObject || a->ob_type == LLFloatTypeObject ) && (b->ob_type == LLIntTypeObject || b->ob_type == LLFloatTypeObject)))
        execerror("No se puede comparar!", NULL);
    if(a->ob_type==LLStringTypeObject && b->ob_type==LLStringTypeObject){
        return (LLObject*)LLBool_Make(LLString_EQ(a,b));
    }
    r1 = LL_CONDITION_EVAL(a);
    r2 = LL_CONDITION_EVAL(b);
    return (LLObject*)LLBool_Make(r1==r2);
}
LLObject* LL_FUNC_NE(LLObject*a,LLObject*b){
    if(a->ob_type!=b->ob_type){
        return (LLObject*)LLBool_Make(1);
    }
    LLBoolObject* r = (LLBoolObject*)LL_FUNC_EQ(a,b);
    r->o_val = !(r->o_val);
    return (LLObject*)r;
}
LLObject* LL_FUNC_AND(LLObject*a,LLObject*b){
    return (LLObject*)LLBool_Make(LL_CONDITION_EVAL(a)&&LL_CONDITION_EVAL(b));
}
LLObject* LL_FUNC_OR(LLObject*a,LLObject*b){
    return (LLObject*)LLBool_Make(LL_CONDITION_EVAL(a)||LL_CONDITION_EVAL(b));
}
LLObject* LL_FUNC_NOT(LLObject*a){
    return (LLObject*)LLBool_Make(!LL_CONDITION_EVAL(a));
}
LLObject* LL_FUNC_LEN(LLObject* a){
    if(a->ob_type==LLListTypeObject)
        return (LLObject*) LLInt_Make(((LLEntryListObject*)a)->len);
    if(a->ob_type==LLStringTypeObject)
        return (LLObject*) LLInt_Make(((LLStringObject*)a)->len);
    execerror("BLINT 'len' no implementado", NULL);
}
LLObject* LL_FUNC_GET_ATTRIB(LLObject* a,char*name){
    if(a->ob_type==LLNoneTypeObject){
        execerror("None object has no attribute", NULL);
    }
    Symbol* s = Attributelookup(name,a->attribute);
    if(s==NULL){
        char* error = malloc(sizeof(char)*30);
        sprintf(error,"AttributeError: Object has no attribute %s ",name);
        execerror(error, NULL);
    }
    return s->u.val;
}
LLObject* LL_FUNC_ATTRIB_ASSIGN(LLObject* a,LLObject*b,char* name){
    Symbol *s = Attributelookup(name,a->attribute);
    if(s==NULL) {
        Attributeinstall(&(a->attribute), name, VAR, b);
    }
    else {
        s->u.val = b;
        s->type = VAR;
    }
    return b;
}
void LL_FUNC_METHOD_ASSIGN(LLObject* a,Inst programa,int nargs,char* name){
    Symbol *s = Attributelookup(name,a->attribute);
    if(s==NULL) {
        s = Attributeinstall(&(a->attribute), name, FUNCTION, (LLObject*)LLNone_Make());
    }
    s->type = FUNCTION;
    s->u.defn = programa;
    s->nargs = nargs;

}
LLObject* LL_FUNC_INFO(LLObject* a){
    printf("Type: %s\n",a->ob_type->name);
    printf("VALUE: ");
    LL_FUNC_PRINT(a,"\n");
    if(a->attribute!=0){
        printf("Attributes: \n");
        for (Symbol* sp = a->attribute; sp != (Symbol *)0; sp = sp->next){
            printf("%s: ",sp->name);
            if(sp->type==VAR)
              LL_FUNC_PRINT(sp->u.val,"\n");
            else if(sp->type==FUNCTION)
              printf("function\n");
        }
    }
    return (LLObject*)  LLNone_Make();
}
Symbol* LL_FUNC_GET_METHOD(LLObject* a,char*name){
    if(a->ob_type==LLNoneTypeObject){
        execerror("None object has no attribute", NULL);
    }
    Symbol* s = Attributelookup(name,a->attribute);
    if(s==NULL){
        char* error = malloc(sizeof(char)*30);
        sprintf(error,"AttributeError: Object has no attribute %s ",name);
        execerror(error, NULL);
    }
    return s;
}