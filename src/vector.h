#ifndef VALUE_H
#define VALUE_H
#include "intList.h"
struct _vector{
	struct _type 	*type;
	struct _intList	*elements;
};
struct _vector *mkVector(struct _type *);
int getElementVector(struct _vector *, int, ...);
void setElementVector(struct _vector *, int, int, int *);
int setElementsVector(struct _vector *, struct _intList *);
int addVector(struct _vector *, struct _vector *, struct _vector *);
int multiplyVector(struct _vector *, struct _vector *, struct _vector *);
void printVector(struct _vector *);
#endif
