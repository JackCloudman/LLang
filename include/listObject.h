#ifndef __LL_LIST_OBJECT_H__
#define __LL_LIST_OBJECT_H__
  #include "Object.h"
  #include "intObject.h"
  typedef struct LLListObject{
    struct LLListObject* next;
    struct LLListObject* prev;
    LLObject* o;
  }LLListObject;

  typedef struct LLEntryListObject{
    LLObject_HEAD
    int len;
    LLListObject* l_val;
  }LLEntryListObject;
  LLTypeObject* LLListTypeObject;
  int LLList_print(LLObject*);
  LLEntryListObject* LLEntryList_Make();
  LLEntryListObject* LLList_append(LLEntryListObject*,LLObject*);
  LLEntryListObject* LLList_insert(LLEntryListObject*,LLObject*);
  LLEntryListObject* LLList_merge(LLEntryListObject*,LLEntryListObject*);
  LLListObject* LLEntryList_getElement(LLEntryListObject*,int);
  LLObject* LLList_getElement(LLEntryListObject*,int);
  LLEntryListObject* LLList_getrange(LLEntryListObject*,int*,int*);
  LLIntObject* LLList_getsize(LLEntryListObject*);
  LLObject* LLList_String(LLObject*);
  LLObject* LL_FUNC_AREPLACE(LLObject*,LLObject*,LLObject*);
#endif
