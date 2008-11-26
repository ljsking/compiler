#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "symbol.h"
#define DEBUG_SYMBOL
struct _symbol **symbolTable;
int nextSymbol = 0;
int isDuplicated(char *id)
{
	int i;
	for(i=0;i<nextSymbol;i++){
		#ifdef DEBUG_SYMBOL
		printf("SYM: compare %s and %s\n", id, symbolTable[i]->id);
		#endif
		if(0==strcmp(id, symbolTable[i]->id)){
			return i;
		}
	}
	return -1;
}
int insertSymbolTable(char *id)
{
	int i;
	if(nextSymbol>MAX_SYMBOL_SIZE){
		printf("The number of symbol is exceeded\n");
		exit(-1);
	}
	i = isDuplicated(id);
	if(i>=0)
	{
		return i;
	}
	char *buf = (char *)malloc(strlen(id));
	strcpy(buf, id);
	symbolTable[nextSymbol]=(struct _symbol *)malloc(sizeof(struct _symbol));
	symbolTable[nextSymbol]->id = buf;
	symbolTable[nextSymbol]->type = 0;
	symbolTable[nextSymbol]->vector = 0;
	#ifdef DEBUG_SYMBOL
	printf("SYM: %d symbol is malloc in %d\n", nextSymbol, symbolTable[nextSymbol]);
	#endif
	nextSymbol++;
	return nextSymbol-1;
}
void setTypeSymbol(int index, struct _type *type){
	symbolTable[index]->type = type;
	#ifdef DEBUG_SYMBOL
	printf("SYM: %d symbol set type %d\n", index, symbolTable[index]->type);
	printSymbol(symbolTable[index]);
	printf("\n");
	#endif
}
int setValueSymbol(int index, struct _vector *val){
	if(symbolTable[index]->type==0) return -1;
	symbolTable[index]->vector = val;
	#ifdef DEBUG_SYMBOL
	printf("SYM: %d symbol set value %d\n", index, symbolTable[index]->vector);
	printSymbol(symbolTable[index]);
	printf("\n");
	#endif
	return 0;
}
struct _vector *getValueSymbol(int index){
	#ifdef DEBUG_SYMBOL
	printf("SYM: %d symbol get value %d\n", index, symbolTable[index]->vector);
	printSymbol(symbolTable[index]);
	printf("\n");
	#endif
	return symbolTable[index]->vector;
}
struct _type *getTypeSymbol(int index){
	#ifdef DEBUG_SYMBOL
	printf("SYM: %d symbol get type %d\n", index, symbolTable[index]->type);
	printSymbol(symbolTable[index]);
	printf("\n");
	#endif
	return symbolTable[index]->type;
}
void printSymbol(struct _symbol *s){
	printf("symbol %s ", s->id);
	if(s->type)
		printType(s->type);
	if(s->vector)
		printVector(s->vector);
}