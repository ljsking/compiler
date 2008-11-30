#ifndef TYPE_H
#define TYPE_H
#include "intList.h"
#define ScalarType 0
#define VectorType 1
#define MatrixType 2
typedef struct _type{
	int		boolean;
	int		type;
	int		row;
	int		col;
}Type;
Type *mkScalarType(int);
Type *mkVectorType(int, int);
Type *mkMatrixType(int, int, int);
void printType(Type *);
#endif
