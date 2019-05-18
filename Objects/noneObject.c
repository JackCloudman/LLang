#include "noneObject.h"
LLObject* LLNone_String(LLObject *o){
    char* buffer = (char*)calloc(7,sizeof(char));
    int j;
    j = sprintf(buffer,"\"");
    if(o!=NULL)
        j += sprintf(buffer+j,"None");
    j+= sprintf(buffer+j,"\"");
    buffer[j] = '\0';
    return (LLObject*)LLString_Make(buffer);
}
int LLNone_print(LLObject *o){
    printf("None");
    return 1;
}
LLNoneObject* LLNone_Make(){
    LLNoneObject * result = 0;
    result = calloc(1,sizeof(LLNoneObject));
    result->print = LLNone_print;
    result->to_String = LLNone_String;
    result->ob_type = LLNoneTypeObject;
    return result;
}