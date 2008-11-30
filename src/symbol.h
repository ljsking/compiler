#ifndef SYMBOL_H
#define SYMBOL_H
#define MAX_SYMBOL_SIZE 100
#include "vector.h"
#include "node.h"
typedef struct _symbol {
	char *id;
	struct _type *type;
	void *data;
}Symbol;
extern struct _symbol **symbolTable;
extern int nextSymbol;
int insertSymbolTable(char *);
void initializeSymbol(int, struct _type *);
void setTypeSymbol(int, struct _type *);
int setValueSymbol(int, struct _vector *, struct _node*);
void setScalarDataSymbol(int, int);
void setVectorDataSymbol(int, int, int);
void setMatrixDataSymbol(int, int, int, int);
int getScalarSymbol(int);
struct _type *getTypeSymbol(int);
void printSymbol(struct _symbol *);
void printSymbolByIndex(int);
#endif
