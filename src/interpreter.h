#ifndef INTERPRETER_H
#define INTERPRETER
#include "statementList.h"
#include "symbol.h"
void interpretForMain(struct _statementList *);
Symbol *interpretForFunction(struct _statementList *);
#endif
