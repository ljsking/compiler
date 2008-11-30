#include <stdio.h>
#include <stdlib.h>
#include "simple.tab.h"
#include "simple.h"
#include "type.h"
#include "symbol.h"
#include "mesch/matrix.h"
#include "interpreter.h"
//#define DEBUG_INTERPRETER

void *traversalNode(struct _node *);

/*
int a;a=2+2;print(a);-ok
int a;int[2]b;int[2,2]c;print(a);print(b);print(c);-ok
int a;a=2;print(a);-ok
int a,b,c; a=2; b=3; c=a+b; print(c);-ok
int [3] v;v[0]=1;print(v); -ok
int [3,2] a;a[1,1]=2;print(a); -ok

int a; a=[2,2]; print(a); -no
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
		initializeSymbol(work->val, t);
		work=work->bro;
	}
}
void *traversalNode(struct _node *n){
	void *pa, *pb;
	void *rz;
	int a,b;
	int tmp;
	char buf[256];
	#ifdef DEBUG_INTERPRETER
	printf("traversalNode %s(%d) v:%d, s:%d, b:%d\n", convertTag(n->tag,buf), n, n->val, n->son, n->bro);
	#endif
	switch(n->tag){
	case TypeInfo:
		interpretTypeInfo(n);
		break;
	case ScalarAssign:
		a=(int)traversalNode(n->son);
		setScalarDataSymbol(n->val, a);
		break;
	case VectorAssign:
		a=(int)traversalNode(n->son);//val
		b=(int)n->bro;//col
		setVectorDataSymbol(n->val, a, b);
		break;
	case MatrixAssign:
		a=(int)traversalNode(n->son);//val
		b=(int)n->son->bro->tag;//row
		tmp=(int)n->son->bro->val;//col
		setMatrixDataSymbol(n->val, a, b, tmp);
		break;
	case ScalarAdd:
		a=(int)traversalNode(n->son);
		b=(int)traversalNode(n->son->bro);
		rz=(void *)(a+b);
		#ifdef DEBUG_INTERPRETER
		printf("%d=%d+%d\n",rz,a,b);
		#endif
		break;
	case VectorAdd:
		pa=traversalNode(n->son);//VEC *
		pb=traversalNode(n->son->bro);
		v_add((VEC *)rz, (VEC *)a,(VEC *)b);
		#ifdef DEBUG_INTERPRETER
		printf("%d=%d+%d\n",rz,a,b);
		#endif
		break;
	case MatrixAdd:
		pa=traversalNode(n->son);//VEC *
		pb=traversalNode(n->son->bro);
		m_add((MAT *)rz, (MAT *)a,(MAT *)b);
		#ifdef DEBUG_INTERPRETER
		printf("%d=%d+%d\n",rz,a,b);
		#endif
		break;
	case ScalarID:
		rz=(void *)getScalarSymbol(n->val);
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode getValFromSymbol(%d:%d)\n",n->val, rz);
		#endif
		break;
	case ScalarData:
		rz=(void *)n->val;
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
