#include <stdlib.h>
#include <stdio.h>
#include "simple.tab.h"
#include "type.h"
struct _type *integer;
struct _type *boolean;
//#define DEBUG_TYPE
int initScalarType()
{
	integer=(struct _type *)malloc(sizeof(struct _type));
	integer->type = INT;
	integer->dimensions=mkIntList();
	insertIntList(integer->dimensions, 1);
	#ifdef DEBUG_TYPE
	printf("integer is %d, dimensions is %d\n", integer, integer->dimensions);
	#endif
	
	boolean=(struct _type *)malloc(sizeof(struct _type));
	boolean->type = BOOL;
	boolean->dimensions=mkIntList();
	insertIntList(boolean->dimensions, 1);
	#ifdef DEBUG_TYPE
	printf("boolean is %d, dimensions is %d\n", integer, integer->dimensions);
	#endif
}
struct _type *mkType(int type)
{
	struct _type *t = (struct _type *)malloc(sizeof(struct _type));
	#ifdef DEBUG_TYPE
	printf("mkType is %d\n", t);
	#endif
	t->type = type;
	t->dimensions = 0;
	return t;
}
void setDimensionType(struct _type *t, struct _intList *dimensions){
	t->dimensions = dimensions;
}
void printType(struct _type *t){
	char buf[256];
	printf("\nType:%s",convertTag(t->type, buf));
	printIntList(t->dimensions);
}
