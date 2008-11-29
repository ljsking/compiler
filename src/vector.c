#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "type.h"
#include "vector.h"
//#define DEBUG_VECTOR
static int insertElementVector(struct _vector *, int);
struct _vector *mkVector(struct _type *t){
	int numberOfElements, i;
	struct _vector *v = malloc(sizeof(struct _vector));
	v->type = t;
	v->elements=mkIntList();
	numberOfElements = numberOfElementsType(t);
	for(i=0;i<numberOfElements;i++)
		insertElementVector(v, 0);
	#ifdef DEBUG_VECTOR
	printf("malloc vector %d\n", v);
	#endif
	return v;
}

int addVector(struct _vector *dst, struct _vector *a, struct _vector *b){
	int tmp1,tmp2;
	tmp1=getElementVector(a, 1, 0);
	tmp2=getElementVector(b, 1, 0);
	setIntList(dst->elements, tmp1+tmp2, 0);
}

int subVector(struct _vector *dst, struct _vector *a, struct _vector *b){
	int tmp1,tmp2;
	tmp1=getElementVector(a, 1, 0);
	tmp2=getElementVector(b, 1, 0);
	setIntList(dst->elements, tmp1-tmp2, 0);
}

int multiplyVector(struct _vector *dst, struct _vector *a, struct _vector *b){
	int tmp1,tmp2;
	tmp1=getElementVector(a, 1, 0);
	tmp2=getElementVector(b, 1, 0);
	setIntList(dst->elements, tmp1-tmp2, 0);
}

int divideVector(struct _vector *dst, struct _vector *a, struct _vector *b){
	int tmp1,tmp2;
	tmp1=getElementVector(a, 1, 0);
	tmp2=getElementVector(b, 1, 0);
	setIntList(dst->elements, tmp1/tmp2, 0);
}

static int insertElementVector(struct _vector *v, int val){
	#ifdef DEBUG_VECTOR
	printf("VECTOR: insertElementVector %d in %d.%d\n", val, v, v->elements);
	#endif
	insertIntList(v->elements, val);
	#ifdef DEBUG_VECTOR
	printVector(v);
	#endif
}

int setElementsVector(struct _vector *v, struct _intList *val){
	#ifdef DEBUG_VECTOR
	printf("VECTOR: setElementsVector %d in %d.%d\n", val, v, v->elements);
	#endif
	freeIntList(v->elements);
	v->elements = val;
	#ifdef DEBUG_VECTOR
	printVector(v);
	#endif
}

int getElementVector(struct _vector *v, int argc, ...){
	register int i;
	int args;
	va_list ap;
	
	#ifdef DEBUG_VECTOR
	printf("VECTOR: getElement argument count: %d in %d\n", index, v);
	#endif
	
	if(v->type->dimensions->numberElement!=argc)
	{
		printf("vector assignment's number is not same as dimension's count\n");
		exit(-1);
	}

	printf("getElementVector \n");
	va_start(ap, argc);
	for(i=0;i<argc;i++){
		
	}
	args = va_arg(ap, int);
	va_end(ap);

	return getIntList(v->elements, args);
}

void setElementVector(struct _vector *v, int value, int argc, int *array){
	int offset;
	
	#ifdef DEBUG_VECTOR
	printf("VECTOR: getElement argument count: %d in %d\n", index, v);
	#endif
	
	if(v->type->dimensions->numberElement!=argc)
	{
		printf("vector assignment's number is not same as dimension's count\n");
		exit(-1);
	}
	printf("setElementVector \n");
	offset = getOffsetType(v->type, argc, array);
	setIntList(v->elements, value, offset);
}

void printVector(struct _vector *v)
{
	printf("vector type:");
	printType(v->type);
	printf(" ");
	printIntList(v->elements);
	printf("\n");
}
