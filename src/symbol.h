#ifndef SYMBOL_H
#define SYMBOL_H
#define MAX_SYMBOL_SIZE 100
#include "vector.h"
struct _symbol {
	char *id;
	struct _type *type;
	struct _vector *vector;
};
extern struct _symbol **symbolTable;
extern int nextSymbol;
int insertSymbolTable(char *);
void setTypeSymbol(int, struct _type *);
int setValueSymbol(int, struct _vector *);
struct _vector *getValueSymbol(int);
struct _type *getTypeSymbol(int);
void printSymbol(struct _symbol *);
void printSymbolByIndex(int);
#endif