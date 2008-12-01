#include <stdio.h>

#include "symbol.h"
#include  "function.h"
void initializeFunction(int sIndex, Type *t, StatementList *list){
	printf("initialize function %d, %d, %d\n", sIndex, (int)t, (int)list);
}
void callFunction(int index){
	Symbol *s = getSymbol(index);
	if(!s->function){
		printf("id(%s) of function is not initialized\n", s->id);
	}
}