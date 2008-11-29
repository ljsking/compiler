#include <stdlib.h>
#include <stdio.h>
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
	tmp1=getElement(a, 0);
	tmp2=getElement(b, 0);
	insertElementVector(dst, tmp1+tmp2);
}

int multiplyVector(struct _vector *dst, struct _vector *a, struct _vector *b){
	
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

int getElement(struct _vector *v, int index){
	#ifdef DEBUG_VECTOR
	printf("VECTOR: getElement %d in %d\n", index, v);
	#endif
	return getIntList(v->elements, index);
}

void printVector(struct _vector *v)
{
	printf("vector type:");
	printType(v->type);
	printf(" ");
	printIntList(v->elements);
	printf("\n");
}
