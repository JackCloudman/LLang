#include "listObject.h"
LLObject* LLList_String(LLObject* o){
    LLEntryListObject* e = (LLEntryListObject*)o;
    if(e==NULL||e->l_val==NULL)
        return (LLObject*)LLString_Make("\"[]\"");
    char* buffer = 0;
    int j = 0;
    LLStringObject *s = 0;

    LLListObject *aux = e->l_val;
    buffer = (char*)calloc(5,sizeof(char));
    j += sprintf(buffer,"%c",'\"');
    j += sprintf(buffer+j,"%c",'[');
    while(aux->next!=(e->l_val)){
        if(aux->o!=NULL){
            s = (LLStringObject*)(aux->o->to_String(aux->o));
            buffer = realloc(buffer,strlen(buffer)+(s->len)+2);
            j+=sprintf(buffer+j,"%s, ",s->o_sval);
        }
        aux = aux->next;
    }
    s = (LLStringObject*)(aux->o->to_String(aux->o));
    buffer = realloc(buffer,strlen(buffer)+(s->len)+2);
    j+=sprintf(buffer+j,"%s]",s->o_sval);
    buffer[j] = '\"';
    buffer[j+1] = '\0';
    return (LLObject*)LLString_Make(buffer);
}
LLEntryListObject* LLEntryList_Make(){
  LLEntryListObject* n = (LLEntryListObject*)calloc(1,sizeof(LLEntryListObject));
  n->len = 0;
  n->l_val = 0;
  n->print = LLList_print;
  n->ob_type = LLListTypeObject;
  n->to_String = LLList_String;
  return n;
}
LLListObject* LLList_Make(LLObject *o){
  LLListObject* n = (LLListObject*)malloc(sizeof(LLListObject));
  n->o = o;
  n->next = n;
  n->prev = n;
  return n;
}
LLEntryListObject* LLList_insert(LLEntryListObject* e,LLObject* o){
  LLEntryListObject* ne = 0;
  LLListObject* n = LLList_Make(o);

  if(e==0){
    ne = LLEntryList_Make();
    ne->l_val = n;
    ne->len = 1;
    return ne;
  }
  n->next = e->l_val;
  e->l_val->prev->next = n;
  n->prev = e->l_val->prev;
  e->l_val->prev = n;
  e->l_val = n;
  (e->len)++;
  return e;
}
LLIntObject* LLList_getsize(LLEntryListObject* e){
  return LLInt_Make(e->len);
}
LLEntryListObject* LLList_getrange(LLEntryListObject* e,int* pos1,int* pos2){
  LLListObject* start = 0;
  LLListObject* end = 0;
  LLEntryListObject* aux = 0;
  if(e==0||e->l_val ==0)
    return NULL;
  if(pos1 == 0){
    start = e->l_val;
  }else{
    start = LLEntryList_getElement(e,*pos1);
    if(start == 0){
      if(*pos1<0)
        start = e->l_val;
      else
        return NULL;
    }
  }
  if(pos2 == 0){
    end = e->l_val;
  }else{
    if(*pos2 == 0)
      return NULL;
    end = LLEntryList_getElement(e,*pos2);
    if(end == 0){
      if(*pos2>0)
        end = e->l_val;
      else
        return NULL;
    }
  }
  if(pos1 !=0 && pos2!=0 && *pos1==*pos2)
    return 0;
  while(start->next!=end){
    aux = LLList_append(aux,start->o);
    start = start->next;
  }
  if(pos2!=0 && *pos2!=0)
    aux = LLList_append(aux,start->o);
  else
    if(pos2==0)
      aux = LLList_append(aux,start->o);
  return aux;
}
LLListObject* LLEntryList_getElement(LLEntryListObject* e,int pos){
  LLListObject* aux = 0;
  int i;
  if(e==0 || e->l_val==0)
    return NULL;
  if(pos>=0){ // Recorrido a la derecha
    aux = e->l_val;
    for(i=0;(aux->next!=(e->l_val))&&(i<pos);i++){
      aux = aux->next;
    }
    if(pos>i)
      return NULL;
  }
  else{ //Recorrido a la izquierda
    aux = e->l_val->prev;
    for(i=-1;(aux->prev!=(e->l_val))&&(i>pos);i--){
      aux = aux->prev;
    }
    if(pos<i-1)
      return 0;
    else if(pos!=i)
      return e->l_val;
  }
  return aux;
}
LLObject* LLList_getElement(LLEntryListObject* e,int pos){
  LLListObject* aux = 0;
  int i;
  if(e==0 || e->l_val==0)
    return NULL;
  if(pos>=0){ // Recorrido a la derecha
    aux = e->l_val;
    for(i=0;(aux->next!=(e->l_val))&&(i<pos);i++){
      aux = aux->next;
    }
    if(pos>i)
      return NULL;
  }
  else{ //Recorrido a la izquierda
    aux = e->l_val->prev;
    for(i=-1;(aux->prev!=(e->l_val))&&(i>pos);i--){
      aux = aux->prev;
    }
    if(pos<i-1)
      return NULL;
    else if(pos!=i)
      return e->l_val->o;
  }
  return aux->o;
}
LLEntryListObject* LLList_append(LLEntryListObject* e,LLObject* o){
  LLListObject* n = LLList_Make(o);
  if(e==0){
    LLEntryListObject* ne = LLEntryList_Make();
    ne->len = 1;
    ne->l_val = n;
    return ne;
  }
  n->next = e->l_val;
  n->prev = e->l_val->prev;
  e->l_val->prev->next = n;
  e->l_val->prev = n;
  (e->len)++;
  return e;
}
LLEntryListObject* LLList_merge(LLEntryListObject* e1,LLEntryListObject* e2){
  LLListObject *aux;
  LLEntryListObject *n;
  n = 0;
  if(e1->l_val!=0){
    aux = e1->l_val;
    while(aux->next!=(e1->l_val)){
      n = LLList_append(n,aux->o);
      aux = aux->next;
    }
    n = LLList_append(n,aux->o);
  }
  if(e2->l_val!=0){
    aux = e2->l_val;
    while(aux->next!=(e2->l_val)){
      n = LLList_append(n,aux->o);
      aux = aux->next;
    }
    n = LLList_append(n,aux->o);
  }
  return n;
}
int LLList_print(LLObject* o){
  LLEntryListObject* e = (LLEntryListObject*)o;
  if(e==0||e->l_val==0){
    printf("[]");
    return 0;
  }
  LLListObject *aux = e->l_val;
  printf("[");
  while(aux->next!=(e->l_val)){
    aux->o->print(aux->o);
    printf(", ");
    aux = aux->next;
  }
  aux->o->print(aux->o);
  printf("]");
  return 0;
}
