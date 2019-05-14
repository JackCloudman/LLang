#include "stringObject.h"

int LLString_print(LLObject *o){
  printf("\"%s\"",((LLStringObject*)o)->o_sval);
  return 1;
}
LLObject* LLString_String(LLObject* o){
    LLStringObject* s = (LLStringObject*)o;
    if(s==NULL)
        return (LLObject*)LLString_Make("\"\'\'\"");
    char * cad = calloc((s->len)+4,sizeof(char));
    sprintf(cad,"\"\'%s\'\"",s->o_sval);
    return (LLObject*)LLString_Make(cad);
}
LLStringObject* LLString_Make(char* cadena){
    int len = strlen(cadena)-1; // La cadena llega como: "hola"
    LLStringObject* result = 0;
    result = calloc(1,sizeof(LLStringObject));
    char* c = (char*)malloc(sizeof(char)*len);
    strncpy(c, cadena+1,len);
    c[len-1] = '\0';
    result->o_sval = c;
    result->len = len;
    result->print = LLString_print;
    result->ob_type = LLStringTypeObject;
    result->to_String = LLString_String;
    return result;
}
LLObject* LLString_CAT(LLObject* a,LLObject* b){
    int len = (((LLStringObject*)a)->len)+(((LLStringObject*)b)->len);
    char *buffer = 0;
    buffer = calloc(len+3,sizeof(char));
    sprintf(buffer,"\"%s%s\"\0",((LLStringObject*)a)->o_sval,((LLStringObject*)b)->o_sval);
    return (LLObject*)LLString_Make(buffer);

}
