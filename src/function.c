#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include  "function.h"
void initializeFunction(int index, Type *t, StatementList *list){
	Function *f=malloc(sizeof(Function));
	f->symbol = getSymbol(index);
	f->symbol->function = 1;
	f->symbol->data = f;
	f->returnType = t;
	f->list = list;
}
Symbol *callFunction(int index){
	Function *f;
	Symbol *s = getSymbol(index);
	if(!s->function){
		printf("id(%s) of function is not initialized\n", s->id);
		exit(-1);
	}
	f=s->data;
	interpret(f->list);
}