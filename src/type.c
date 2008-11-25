#include <stdlib.h>
#include <stdio.h>
#include "type.h"
struct _type *mkType(int type)
{
	struct _type *t = (struct _type *)malloc(sizeof(struct _type));
	t->type = type;
	t->vector = 0;
	t->dimensions = 0;
	return t;
}
void setDimensionType(struct _type *t, struct _intList *dimensions){
	t->vector = 1;
	t->dimensions = dimensions;
}
void printType(struct _type *t){
	char buf[256];
	printf("\nType:%s, vector:%d",convertTag(t->type, buf),t->vector);
	if(t->vector)
		printIntList(t->dimensions);
	printf("\n");
}