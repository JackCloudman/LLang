#include "abstract.h"
#include "Symbol.h"
#include "Lala.h"
#include "y.tab.h"

extern void execerror(char *s, char *t);
#define NSTACK  256
static  Datum  stack[NSTACK];  /* la pila */
static  Datum   *stackp;       /* siguiente lugar libre en la pila */
#define NPROG   2000
Inst    prog[NPROG];    /* la máquina */
Inst    *progp;         /* siguiente lugar libre para la generación de código */
Inst    *pc;	/* contador de programa durante la ejecución */

void initcode(){ /* inicialización para la generación de código */
    stackp = stack;
    progp = prog;
}

void push(d)	/*  meter d en la pila  */
        Datum d;
{
    if (stackp >= &stack[NSTACK])
        execerror("stack overflow", (char *) 0);
    *stackp++ = d;
}

Datum pop( ){ /* sacar y retornar de la pila el elemento del tope */
    if (stackp <= stack)
        execerror("stack underflow", (char *) 0);
    return  *--stackp;
}


void constpush( ){ /* meter una objeto a la pila  */
    Datum d;
    d.val  =  ((Symbol  *)*pc++)->u.val;
    push(d);
}

void varpush(){/* meter una variable a la pila   */
    Datum d;
    d.sym  =  (Symbol   *)(*pc++);
    push(d);
}

void eval( ){ /*  evaluar una variable en la pila   */
    Datum  d;
    d   =  pop();
    if(d.sym->type   ==   INDEF){
        execerror("Error, variable no definida: ",d.sym->name);
    }
    d.val   =  d.sym->u.val; push(d);
}

void addo( ){
    Datum d1,   d2;
    d2 = pop();
    d1 = pop();
    d1.val = LL_FUNC_ADD(d1.val,d2.val);
    push(d1);
}

void subo(){
    Datum d1,  d2;
    d2 = pop();
    d1 = pop();
    d1.val = LL_FUNC_SUB(d1.val,d2.val);
    push(d1);
}

void mulo(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = LL_FUNC_MUL(d1.val,d2.val);
    push(d1);
}


void divo( ){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = LL_FUNC_DIV(d1.val,d2.val);
    push(d1);
}

void negate()
{
    Datum d;
    d = pop();
    d.val =  LL_FUNC_NEGATE(d.val);
    push(d);
}

void assign( ){
    Datum d1, d2;
    d1 = pop();
    d2 = pop();
    if (d1.sym->type != VAR && d1.sym->type != INDEF){
        execerror("assignment to non-variable", d1.sym->name);
    }
    d1.sym->u.val = d2.val;
    d1.sym->type = VAR;
    push(d2);
}

void print( ){
    Datum d;
    d = pop();
    LL_FUNC_PRINT(d.val,"\n");
}

void bltin( )/*  evaluar un predefinido en el tope de la pila  */
{
    Datum d;
    d  =  pop();
    d.val  =   (*(LLObject*   (*)())(*pc++))(d.val);
    push(d);
}
void makeArray(){
  Datum d;
  LLEntryListObject* l = 0;
  Datum* savestackp = stackp;
  execute(pc);
  while(stackp > savestackp){
    d = pop();
    l = LLList_insert(l,d.val);
  }
  if(l == 0){
    l = LLEntryList_Make();
  }
  d.val = (LLObject*)l;
  push(d);
  *pc++;
}

void aArray(){
  Datum d1,d2;
  d2 = pop();
  d1 = pop();
  d1.val = LL_FUNC_AACCESS(d1.val,d2.val);
  push(d1);
}
void ChangeValue(){
  Datum nd,index,a;//New dato,index, array
  nd = pop();
  index = pop();
  a = pop(); //Save array
  LL_FUNC_AREPLACE(a.val,index.val,nd.val);
  push(nd);
}
void getSubArray(){
  Datum start,end,lista;

  end = pop();
  start = pop();
  lista = pop();

  lista.val = LL_FUNC_GETSUBARRAY(lista.val,start.val,end.val);
  push(lista);
}
void emptypush(){
  Datum d;
  d.val = 0;
  push(d);
}
Inst   *code(Inst f) /*   instalar una instrucción u operando   */
{
    Inst *oprogp = progp;
    if (progp >= &prog [ NPROG ])
        execerror("program too big", (char *) 0);
    *progp++ = f;
    return oprogp;
}

void execute(Inst* p)	/*   ejecución con la máquina   */
{
    for (pc  =  p;   *pc != STOP; )
        (*(*pc++))();
}
