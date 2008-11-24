#ifndef SIMPLE_H
#define SIMPLE_H
#define MAX_SYMBOL_SIZE 100
struct _symbol {
	void *pointer;
};
extern struct _symbol **symbolTable;
extern  int currentSymbol;
#endif