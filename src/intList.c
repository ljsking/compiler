#include <stdlib.h>
#include <stdio.h>
#include "simple.h"

struct _intList *mkIntList(){
	struct _intList *list = malloc(sizeof(struct _intList));
	#ifdef DEBUG_LIST
	printf("malloc list %d\n", list);
	#endif
	list->maxElement = 10;
	list->numberElement = 0;
	list->elements = malloc(sizeof(int)*10);
}
void			freeIntList(struct _intList *list){
	#ifdef DEBUG_LIST
	printf("free list %d\n", list);
	#endif
	free(list->elements);
	free(list);
}
void 			insertIntList(struct _intList *list, int val){
	if(list->numberElement == list->maxElement){
		printf("exceed number of elements\n");
		exit(-1);
	}
	list->elements[list->numberElement] = val;
	list->numberElement++;
}
void			printIntList(struct _intList *list){
	int i;
	printf("list:%d, now:%d, max:%d\n", list, list->numberElement, list->maxElement);
	for(i=0;i<list->numberElement;i++)
		printf("%d, ", list->elements[i]);
	printf("\n");
}