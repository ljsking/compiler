#ifndef TYPE_H
#define TYPE_H
#include "intList.h"
struct _type{
	int		type;
	struct _intList *dimensions;
};
struct _type *mkType(int type);
void setDimensionType(struct _type *, struct _intList * );
void printType(struct _type *);
int initScalarType();
extern struct _type *integer;
extern struct _type *boolean;
#endif
