#ifndef INTLIST_H
#define INTLIST_H
/*
It is vector(One-dimension array).
Multi-dimensions array(Vector) has a IntList.
If a user wants to get a element in vector, vector calculates a index and requests a element to its IntList.
*/
struct _intList{
	int		numberElement;
	int		maxElement;
	int		*elements;
};
struct _intList *mkIntList();
void			freeIntList(struct _intList *);
void 			insertIntList(struct _intList *, int);
void			printIntList(struct _intList *);
int				getIntList(struct _intList *, int);
#endif
