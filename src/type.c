#include <stdlib.h>
#include <stdio.h>
#include "simple.tab.h"
#include "intList.h"
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
int numberOfElementsType(struct _type *t){
	int i, rz=1;
	for(i=0;i<t->dimensions->numberElement;i++){
		rz*=getIntList(t->dimensions, i);
	}
	return rz;
}
int getOffsetType(struct _type *t, int count, int *array){
	int rz, i, tmp=1;
	if(count!=t->dimensions->numberElement){
		printf("size of dimensions is not same as count\n");
		exit(-1);
	}
	for(i=count-1;i>=0;i--){
		rz+=tmp*array[i];
		tmp*=t->dimensions->elements[i];
	}
	return rz;
}
void printType(struct _type *t){
	char buf[256];
	printf("\nType:%s ",convertTag(t->type, buf));
	printIntList(t->dimensions);
}
