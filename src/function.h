#ifndef FUNCTION_H
#define FUNCTION_H
#include "symbol.h"
#include "type.h"
#include "statementList.h"
typedef struct _function{
	Symbol 	*symbol;
	Type	*returnType;
	StatementList *list;
}Function;
void initializeFunction(int, Type *, StatementList *);
#endif