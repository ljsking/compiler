#ifndef SYMBOL_H
#define SYMBOL_H
#define MAX_SYMBOL_SIZE 100
#include "node.h"
#include "type.h"
typedef struct _symbol {
	char *id;
	struct _type *type;
	void *data;
}Symbol;
extern struct _symbol **symbolTable;
extern int nextSymbol;
Symbol *mkSymbol(Type *, void *);
int insertSymbolTable(char *);
void initializeSymbol(int, struct _type *);
void setTypeSymbol(int, struct _type *);
void setScalarDataSymbol(int, int);
void setVectorDataSymbol(int, int, int);
void setMatrixDataSymbol(int, int, int, int);
Symbol *getSymbol(int);
struct _type *getTypeSymbol(int);
void printSymbol(struct _symbol *);
void printSymbolByIndex(int);
#endif
