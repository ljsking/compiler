#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

#include "vector.h"
//#define DEBUG_VECTOR
struct _vector *mkVector(struct _type *t){
	struct _vector *v = malloc(sizeof(struct _vector));
	v->type = t;
	v->elements=mkIntList();
	#ifdef DEBUG_VECTOR
	printf("malloc vector %d\n", v);
	#endif
	return v;
}

int addVector(struct _vector *dst, struct _vector *a, struct _vector *b){
	int tmp1,tmp2;
	tmp1=getElementVector(a, 1, 0);
	tmp2=getElementVector(b, 1, 0);
	insertElementVector(dst, tmp1+tmp2);
}

int subVector(struct _vector *dst, struct _vector *a, struct _vector *b){
	int tmp1,tmp2;
	tmp1=getElementVector(a, 1, 0);
	tmp2=getElementVector(b, 1, 0);
	insertElementVector(dst, tmp1-tmp2);
}

int multiplyVector(struct _vector *dst, struct _vector *a, struct _vector *b){
	int tmp1,tmp2;
	tmp1=getElementVector(a, 1, 0);
	tmp2=getElementVector(b, 1, 0);
	insertElementVector(dst, tmp1*tmp2);
}

int divideVector(struct _vector *dst, struct _vector *a, struct _vector *b){
	int tmp1,tmp2;
	tmp1=getElementVector(a, 1, 0);
	tmp2=getElementVector(b, 1, 0);
	insertElementVector(dst, tmp1/tmp2);
}

int insertElementVector(struct _vector *v, int val){
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
	#ifdef DEBUG_VECTOR
	printf("VECTOR: getElement %d in %d\n", index, v);
	#endif
	register int i;
	int args;
	va_list ap;

	printf("getElementVector \n");
	va_start(ap, argc);
	args = va_arg(ap, int);
	va_end(ap);

	return getIntList(v->elements, args);
}

void printVector(struct _vector *v)
{
	printf("vector type:");
	printType(v->type);
	printf(" ");
	printIntList(v->elements);
	printf("\n");
}
