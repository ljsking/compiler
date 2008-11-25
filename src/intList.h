#ifndef INTLIST_H
#define INTLIST_H
struct _intList{
	int		numberElement;
	int		maxElement;
	int		*elements;
};
struct _intList *mkIntList();
void			freeIntList(struct _intList *);
void 			insertIntList(struct _intList *, int);
void			printIntList(struct _intList *);
#endif