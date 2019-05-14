#include "intObject.h"

LLObject* LLInt_String(LLObject *o){
    char* buffer = (char*)calloc(32,sizeof(char));
    int j;
    j = sprintf(buffer,"\"");
    if(o!=NULL)
        j += sprintf(buffer+j,"%d",((LLIntObject*)o)->o_val);
    j+= sprintf(buffer+j,"\"");
    buffer[j] = '\0';
    return (LLObject*)LLString_Make(buffer);
}
int LLInt_print(LLObject *o){
  printf("%d",((LLIntObject*)o)->o_val);
  return 1;
}
LLIntObject* LLInt_Make(int val){
  LLIntObject * result = 0;
  result = calloc(1,sizeof(LLIntObject));
  result->o_val = val;
  result->print = LLInt_print;
  result->to_String = LLInt_String;
  result->ob_type = LLIntTypeObject;
  return result;
}
LLObject* LLInt_ADD(LLObject* a,LLObject* b){
  return (LLObject*)LLInt_Make(((LLIntObject*)a)->o_val+((LLIntObject*)b)->o_val);
}

LLObject* LLInt_SUB(LLObject* a,LLObject* b){
    return (LLObject*)LLInt_Make((((LLIntObject*)a)->o_val)-(((LLIntObject*)b)->o_val));
}
LLObject* LLInt_MUL(LLObject* a,LLObject* b){
    return (LLObject*)LLInt_Make(((LLIntObject*)a)->o_val*((LLIntObject*)b)->o_val);
}
LLObject* LLInt_DIV(LLObject* a,LLObject* b){
    return (LLObject*)LLInt_Make(((LLIntObject*)a)->o_val/((LLIntObject*)b)->o_val);
}


