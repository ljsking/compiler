#ifndef SYMBOL_H
#define SYMBOL_H
#define MAX_SYMBOL_SIZE 100
struct _symbol {
	char *id;
	struct _type *type;
	int	 val;
};
extern struct _symbol **symbolTable;
extern int nextSymbol;
int insertSymbolTable(char *);
void setTypeSymbol(int index, struct _type *type);
int setValueSymbol(int index, int value);
#endif