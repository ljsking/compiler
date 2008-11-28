#include <stdlib.h>
#include <stdio.h>
#include "intList.h"
//#define DEBUG_LIST

struct _intList *mkIntList(){
	struct _intList *list = malloc(sizeof(struct _intList));
	list->maxElement = 10;
	list->numberElement = 0;
	list->elements = malloc(sizeof(int)*10);
	#ifdef DEBUG_LIST
	printf("malloc IntList %d (%d/%d)\n", list, list->numberElement, list->maxElement);
	#endif
	return list;
}
void			freeIntList(struct _intList *list){
	#ifdef DEBUG_LIST
	printf("free IntList %d\n", list);
	#endif
	free(list->elements);
	free(list);
}
void 			insertIntList(struct _intList *list, int val){
	#ifdef DEBUG_LIST
	printf("insert in IntList(%d)\n", list);
	printf("insertIntList %d now:%d max:%d\n", list, list->numberElement, list->maxElement);
	#endif
	if(list->numberElement == list->maxElement){
		printf("exceed number of elements in IntList\n");
		exit(-1);
	}
	list->elements[list->numberElement] = val;
	list->numberElement++;
}
int				getIntList(struct _intList *list, int index){
	#ifdef DEBUG_LIST
	printf("get IntList");
	printf("getIntList %d now:%d max:%d\n", list, list->numberElement, list->maxElement);
	#endif
	if(list->numberElement < index){
		printf("index is out of bound\n");
		exit(-1);
	}
	return list->elements[index];
}
void			printIntList(struct _intList *list){
	int i;
	printf("list:%d, now:%d, max:%d\n", list, list->numberElement, list->maxElement);
	for(i=0;i<list->numberElement;i++)
		printf("%d, ", list->elements[i]);
}
