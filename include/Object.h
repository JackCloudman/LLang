#ifndef __OBJECT_H__
#define __OBJECT_H__
  #include <stdlib.h>
  #include <stdio.h>
  #include<string.h>
//  #define LLMEM(LLObject) (LLObject*)calloc(1,sizeof(LLObject))

  typedef struct _typeobject{
    char *name;
  }LLTypeObject;

  typedef struct _object LLObject;
  #define LLObject_HEAD LLTypeObject *ob_type; \
                        int (*print)(LLObject*); \
                        LLObject* (*to_String)(LLObject*);
  typedef struct _object{
      LLObject_HEAD
    }LLObject;
  typedef LLObject *APLLObject;
  #define YYSTYPE APLLObject
#endif
