#include <stdio.h>
#include <stdlib.h>
#include "simple.tab.h"
#include "simple.h"
#include "type.h"
#include "symbol.h"
#include "interpreter.h"

/*int a,b,c; a=2; b=3; c=a+b;*/
void interpretTypeInfo(struct _node *);
void interpretAssign(struct _node *);
void interpretNode(struct _node *n){
	switch(n->tag){
	case TypeInfo:
		interpretTypeInfo(n);
		break;
	case ASS_OP:
		interpretAssign(n);
	}
}
void interpret(struct _statementList *list){
	int i;
	for(i=0;i<list->numberElement;i++){
		interpretNode(list->elements[i]);
	}
}
void interpretTypeInfo(struct _node *n){
	struct _type *t = (struct _type *)n->val;
	struct _node *work = n->son;
	if(!work||!work->son){
		printf("Type declation error\n");
		exit(-1);
	}
	work=work->son;
	while(work){
		setTypeSymbol(work->val, t);
		work=work->bro;
	}
}
void interpretAssign(struct _node *n){
	char buf[256];
	int symbolIndex = n->val;
	struct _node *work;
	if(n->son->tag==NUMBER){
		work=n->son;
		if(setValueSymbol(symbolIndex, n->son->val))
		{
			printf("Use not declared symbol!\n");
			exit(-1);
		}
	}else{
		printf("Assignment error\n");
		exit(-1);
	}
}