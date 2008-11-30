#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "type.h"
Type *IntegerScalarType;
Type *BooleanScalarType;
void initType(){
	IntegerScalarType=mkScalarType(0);
	BooleanScalarType=mkScalarType(1);
}
struct _type *mkScalarType(int boolean){
	struct _type * type = malloc(sizeof(struct _type));
	type->boolean = boolean;
	type->type = ScalarType;
	type->row = 0;
	type->col = 0;
	return type;
}
struct _type *mkVectorType(int boolean, int col){
	struct _type * type = malloc(sizeof(struct _type));
	type->boolean = boolean;
	type->type = VectorType;
	type->row = 0;
	type->col = col;
	return type;
}
struct _type *mkMatrixType(int boolean, int row, int col){
	struct _type * type = malloc(sizeof(struct _type));
	type->boolean = boolean;
	type->type = MatrixType;
	type->row = row;
	type->col = col;
	return type;
}
void printType(Type *t){
	char type[256];
	char buff[256];
	if(t->boolean)
		strcpy(type, "boolean");
	else
		strcpy(type, "integer");
	switch(t->type){
		case ScalarType:
			sprintf(buff, "ScalarType(%s)\n",type);
		break;
		case VectorType:
			sprintf(buff, "VectorType(%s[%d])\n",type,t->col);
		break;
		case MatrixType:
			sprintf(buff, "MatrixType(%s[%d,%d])\n",type,t->row,t->col);
		break;
		default:
			printf("Unknow type\n");
		break;
	}
}