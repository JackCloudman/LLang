#include "boolObject.h"
LLObject* LLBool_String(LLObject *o){
    char* buffer = (char*)calloc(8,sizeof(char));
    int j;
    j = sprintf(buffer,"\"");
    if(o!=NULL){
        if(((LLBoolObject*)o)->o_val){
            j += sprintf(buffer+j,"True");
        }else{
            j += sprintf(buffer+j,"False");
        }
    }
    j+= sprintf(buffer+j,"\"");
    buffer[j] = '\0';
    return (LLObject*)LLString_Make(buffer);
}
int LLBool_print(LLObject *o){
    if(((LLBoolObject*)o)->o_val){
        printf("True");
    }else{
        printf("False");
    }
    return 1;
}
LLBoolObject* LLBool_Make(short val){
    LLBoolObject * result = 0;
    result = calloc(1,sizeof(LLBoolObject));
    result->o_val = val;
    result->print = LLBool_print;
    result->to_String = LLBool_String;
    result->ob_type = LLBoolTypeObject;
    result->attribute = 0;
    return result;
}