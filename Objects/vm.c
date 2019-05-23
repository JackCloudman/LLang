#include "vm.h"
#include "y.tab.h"
extern void execerror(char *s, char *t);
#define NSTACK  256
static  Datum  stack[NSTACK];  /* la pila */
static  Datum   *stackp;       /* siguiente lugar libre en la pila */
#define NPROG   2000
Inst    prog[NPROG];    /* la máquina */
Inst    *progp;         /* siguiente lugar libre para la generación de código */
Inst    *pc;	/* contador de programa durante la ejecución */
Inst   *progbase = prog; /* Inicie del subprograma actual */
int    returning;      /* 1 si se ve la proposiolón de retorno */

void initcode(){ /* inicialización para la generación de código */
    stackp = stack;
    progp = progbase;
    stackp = stack;
    fp = frame;
    returning = 0;
}

void push(d)	/*  meter d en la pila  */
        Datum d;
{
    if (stackp == &stack[NSTACK])
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
void varfuncpush(){
    Datum d;
    d.sym  =  (Symbol   *)(*pc++);
    Symbol* s = funclookup(d.sym->name,fp->vars);
    if(s==0)
        s = funcinstall(&(fp->vars),d.sym->name,INDEF,LLNone_Make());
    d.sym = s;
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

void ifcode(){
    Datum d;
    Inst  *savepc  = pc;	/* parte then */
    execute(savepc+3);	/*  condición   */
    d  =  pop();
    if(LL_CONDITION_EVAL(d.val))
        execute(*((Inst   **)(savepc)));
    else if(*((Inst  **)(savepc+1)))   /*  ¿parte else?   */
        execute(*(( Inst  **) (savepc+1)));
    if (!returning)
        pc  =  *((Inst  **)(savepc+2));	/*  siguiente proposición   */
}
void whilecode(){
    Datum d;
    Inst *savepc = pc;
    execute(savepc+2);
    d = pop();
    while(LL_CONDITION_EVAL(d.val)){
        execute(*((Inst  **)(savepc)));
        if (returning) break;
        execute(savepc+2);
        d = pop();
    }
    if (!returning)
        pc = *((Inst  **)(savepc+1));
}

void gt() {
    Datum d1,  d2;
    d2 = pop();
    d1 = pop();
    d1.val  = LL_FUNC_GT(d1.val,d2.val);
    push(d1);
}

void lt(){
    Datum d1,  d2;
    d2 = pop();
    d1 = pop();
    d1.val  = LL_FUNC_LT(d1.val,d2.val);
    push(d1);
}

void ge( ) {
    Datum d1,  d2;
    d2  = pop();
    d1  = pop();
    d1.val = LL_FUNC_GE(d1.val,d2.val);
    push(d1) ;
}

void le() {
    Datum d1,  d2;
    d2   =  pop();
    d1   =  pop();
    d1.val = LL_FUNC_LE(d1.val,d2.val);
    push(d1);
}

void eq( ) {
    Datum d1,  d2;
    d2  = pop();
    d1  = pop();
    d1.val =LL_FUNC_EQ(d1.val,d2.val);
    push(d1);
}

void ne(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = LL_FUNC_NE(d1.val,d2.val);
    push(d1);
}

void and(){
    Datum d1,   d2;
    d2   = pop();
    d1   = pop();
    d1.val = LL_FUNC_AND(d1.val,d2.val);
    push(d1);
}

void or(){
    Datum d1, d2;
    d2 = pop();
    d1 = pop();
    d1.val = LL_FUNC_OR(d1.val,d2.val);
    push(d1);
}

void not( ){
    Datum d;
    d = pop();
    d.val = LL_FUNC_NOT(d.val);
    push(d);
}

void define(Symbol *sp){
    sp->u.defn = (Inst)progbase;
    progbase = progp;      /* el siguiente código comienza aquí */
}

void call() {
    Symbol  *sp  =   (Symbol *)pc[0];   /*   entrada en tabla da simbolos  */
    /*   para la función   */
    if   (fp++   >=  &frame[NFRAME-1])
        execerror(sp->name,   "call  nested too deeply");
    fp->sp = sp;
    fp->nargs =   (int)pc[1];
    fp->retpc = pc  + 2;
    fp->vars = 0;
    fp->argn  =  stackp  -   1;     /*   último argumento   */
    execute((Inst*)sp->u.defn);
    returning = 0;
}
void ret( ) {
    int i;
    for (i = 0; i < fp->nargs; i++)
        pop();  /* sacar argunentos de la pila */
    pc = (Inst *)fp->retpc;
    --fp;
    returning = 1;
}
void funcret(){
    Datum d;
    d = pop();      /* conservar el valor de retorno de la func */
    ret();
    push(d);
}
void procret( ){
    Datum d;
    d.val = (LLObject*)LLNone_Make();
    ret();
    push(d);
}
LLObject** getarg( ) {
    int nargs = (int) *pc++;
    if (nargs > fp->nargs)
        execerror(fp-> sp->name, "not enough arguments");
    return &(fp->argn[nargs - fp->nargs].val);
}
void arg( ) {
    Datum d;
    d.val = *getarg();
    push(d);
}
void argassign() {
    Datum d;
    d =pop();
    push(d);       /* dejar valor en la pila */
    *getarg() = d.val;
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
    for (pc  =  p;*pc != STOP && !returning; )
        (*(*pc++))();
}
