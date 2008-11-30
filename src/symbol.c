#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mesch/matrix.h"
#include "type.h"
#include "symbol.h"
//#define DEBUG_SYMBOL
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
	char *buf;
	if(nextSymbol>MAX_SYMBOL_SIZE){
		printf("The number of symbol is exceeded\n");
		exit(-1);
	}
	i = isDuplicated(id);
	if(i>=0)
	{
		return i;
	}
	buf = (char *)malloc(strlen(id));
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
void printSymbol(Symbol *s){
	switch(s->type->type){
		case ScalarType:
			printf("Scalar %d\n",s->data);
		break;
		case VectorType:
			v_output(s->data);
		break;
		case MatrixType:
			m_output(s->data);
		break;
	}
}
void initializeSymbol(int index, struct _type *type){
	struct _symbol *symbol = symbolTable[index];
	setTypeSymbol(index, type);
	symbol->vector = mkVector(symbol->type);
	switch(type->type){
		case ScalarType:
			symbol->data=0;
		break;
		case VectorType:
			symbol->data=v_get(type->col);
		break;
		case MatrixType:
			symbol->data=m_get(type->row,type->col);
		break;
	}
	#ifdef DEBUG_SYMBOL
	printf("before printSymbol\n");
	printSymbol(symbol);
	#endif
}
void setTypeSymbol(int index, struct _type *type){
	Symbol *symbol = symbolTable[index];
	symbol->type = type;
	#ifdef DEBUG_SYMBOL
	printf("SYM: %d symbol set type %d\n", index, symbolTable[index]->type);
	printSymbol(symbolTable[index]);
	printf("\n");
	#endif
}
int setValueSymbol(int index, struct _vector *val, struct _intList* list){
	struct _symbol *dst = symbolTable[index];
	if(dst->type==0) return -1;
	
	#ifdef DEBUG_SYMBOL
	printf("SYM: %d symbol set value %d\n", index, symbolTable[index]->vector);
	printIntList(list);
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
void printSymbolByIndex(int index){
	printSymbol(symbolTable[index]);
}
