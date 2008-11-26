#include <stdio.h>
#include <stdlib.h>
#include "simple.tab.h"
#include "simple.h"
#include "type.h"
#include "symbol.h"
#include "interpreter.h"
#define DEBUG_INTERPRETER
/*int a,b,c; a=2; b=3; c=a+b*2;*/
void interpretTypeInfo(struct _node *);
void interpretAssign(struct _node *);
void interpret(struct _statementList *list){
	int i;
	for(i=0;i<list->numberElement;i++){
		traversalNode(list->elements[i]);
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
int traversalNode(struct _node *n){
	int a,b;
	int rz=0;
	#ifdef DEBUG_INTERPRETER
	char buf[256];
	printf("traversalNode %s(%d) s:%d, b:%d\n", convertTag(n->tag,buf),n,n->son,n->bro);
	#endif
	switch(n->tag){
	case TypeInfo:
		interpretTypeInfo(n);
		break;
	case ASS_OP:
		a=n->val;//symbol index
		b=traversalNode(n->son);//saved value
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode Assign value %d to %d\n", b, a);
		#endif
		setValueSymbol(a, b);
		break;
	case ADD_OP:
		a=traversalNode(n->son);
		b=traversalNode(n->son->bro);
		rz=a+b;
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode ADD_OP(%d=%d+%d)\n", rz, a, b);
		#endif
		break;
	case MUL_OP:
		a=traversalNode(n->son);
		b=traversalNode(n->son->bro);
		rz=a*b;
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode ADD_OP(%d=%d*%d)\n", rz, a, b);
		#endif
		break;
	case ID:
		rz=getValueSymbol(n->val);
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode getValFromSymbol(%d:%d)\n",n->val, rz);
		#endif
		break;
	case NUMBER:
		rz = n->val;
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode NUMBER(%d)\n",n->val);
		#endif
		break;
	}
	return rz;
}