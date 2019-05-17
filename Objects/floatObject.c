#include "floatObject.h"

LLObject* LLFloat_String(LLObject *o){
    char* buffer = (char*)calloc(32,sizeof(char));
    int j;
    j = sprintf(buffer,"\"");
    if(o!=NULL)
        j += sprintf(buffer+j,"%f",((LLFloatObject*)o)->o_val);
    j+= sprintf(buffer+j,"\"");
    buffer[j] = '\0';
    return (LLObject*)LLString_Make(buffer);
}
int LLFloat_print(LLObject *o){
    printf("%f",((LLFloatObject*)o)->o_val);
    return 1;
}
LLFloatObject* LLFloat_Make(double val){
    LLFloatObject * result = 0;
    result = calloc(1,sizeof(LLFloatObject));
    result->o_val = val;
    result->print = LLFloat_print;
    result->to_String = LLFloat_String;
    result->ob_type = LLFloatTypeObject;
    return result;
}
LLObject* LLFloat_ADD(LLObject* a,LLObject* b){
    return (LLObject*)LLFloat_Make((((LLFloatObject*)a)->o_val)+((LLFloatObject*)b)->o_val);
}

LLObject* LLFloat_SUB(LLObject* a,LLObject* b){
    return (LLObject*)LLFloat_Make((((LLFloatObject*)a)->o_val)-(((LLFloatObject*)b)->o_val));
}
LLObject* LLFloat_MUL(LLObject* a,LLObject* b){
    return (LLObject*)LLFloat_Make(((LLFloatObject*)a)->o_val*((LLFloatObject*)b)->o_val);
}
LLObject* LLFloat_DIV(LLObject* a,LLObject* b){
    return (LLObject*)LLFloat_Make(((LLFloatObject*)a)->o_val/((LLFloatObject*)b)->o_val);
}
