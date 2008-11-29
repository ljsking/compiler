#include <stdio.h>
#include <stdlib.h>
#include "simple.tab.h"
#include "simple.h"
#include "type.h"
#include "symbol.h"
#include "interpreter.h"
//#define DEBUG_INTERPRETER

struct _vector *traversalNode(struct _node *);

/*
int a; a=[1,2,3]; print(a);
int a,b,c; a=2; b=3; c=a+b; print(c);
*/
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
struct _vector *traversalNode(struct _node *n){
	struct _vector *a, *b, *rz;
	int tmp;
	struct _vector *v;
	#ifdef DEBUG_INTERPRETER
	char buf[256];
	printf("traversalNode %s(%d) v:%d, s:%d, b:%d\n", convertTag(n->tag,buf), n, n->val, n->son, n->bro);
	#endif
	switch(n->tag){
	case TypeInfo:
		interpretTypeInfo(n);
		break;
	case ASS_OP:
		tmp=n->val;//symbol index
		b=traversalNode(n->son);//saved value
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode Assign value %d to %d\n", b, tmp);
		#endif
		setValueSymbol(tmp, b);
		break;
	case ADD_OP:
		a=traversalNode(n->son);
		b=traversalNode(n->son->bro);
		rz=mkVector(a->type);
		addVector(rz, a, b);
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode ADD_OP(%d=%d+%d)\n", rz, a, b);
		#endif
		break;
	case SUB_OP:
		a=traversalNode(n->son);
		b=traversalNode(n->son->bro);
		rz=mkVector(a->type);
		subVector(rz, a, b);
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode SUB_OP(%d=%d+%d)\n", rz, a, b);
		#endif
		break;
	case MUL_OP:
		a=traversalNode(n->son);
		b=traversalNode(n->son->bro);
		multiplyVector(rz, a, b);
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode MUL_OP(%d=%d*%d)\n", rz, a, b);
		#endif
		break;
	case DIV_OP:
		a=traversalNode(n->son);
		b=traversalNode(n->son->bro);
		divideVector(rz, a, b);
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode DIV_OP(%d=%d*%d)\n", rz, a, b);
		#endif
		break;
	case ID:
		rz=getValueSymbol(n->val);
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode getValFromSymbol(%d:%d)\n",n->val, rz);
		#endif
		break;
	case NUMBER:
		v=mkVector(integer);
		insertElementVector(v, n->val);
		rz=v;
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode NUMBER(%d)\n",n->val);
		#endif
		break;
	case Vector:
		v=mkVector(integer);
		setElementsVector(v, (struct _intList *)n->val);
		rz=v;
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode Vector(%d)\n",n->val);
		#endif
		break;
	case PRINT:
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode PRINT(%d)\n",n->val);
		#endif
		printSymbolByIndex(n->val);
		break;
	}
	return rz;
}
