#include <stdio.h>
#include  "function.h"
void initializeFunction(int sIndex, Type *t, StatementList *list){
	printf("initialize function %d, %d, %d\n", sIndex, (int)t, (int)list);
}