#ifndef VALUE_H
#define VALUE_H
#include "intList.h"
struct _vector{
	struct _type 	*type;
	struct _intList	*elements;
};
struct _vector *mkVector(struct _type *);
int insertElementVector(struct _vector *, int);
int getElementVector(struct _vector *, int, ...);
int setElementsVector(struct _vector *, struct _intList *);
int addVector(struct _vector *, struct _vector *, struct _vector *);
int multiplyVector(struct _vector *, struct _vector *, struct _vector *);
void printVector(struct _vector *);
#endif
