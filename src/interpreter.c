#include <stdio.h>
#include <stdlib.h>
#include "simple.tab.h"
#include "simple.h"
#include "type.h"
#include "symbol.h"
#include "mesch/matrix.h"
#include "interpreter.h"
//#define DEBUG_INTERPRETER

Symbol *traversalNode(struct _node *);

/*
int a;a=2+2;print(a);-ok
int a;int[2]b;int[2,2]c;print(a);print(b);print(c);-ok
int a,b,c; a=2; b=3; c=a+b; print(c);-ok
int [3] v;v[0]=1;print(v); -ok
int [3,2] a;a[1,1]=2;print(a); -ok
int a, b; a=2; b=4; a = a-b; print(a);	-ok
int a, b; a=2; b=4; a = a*b; print(a);	-ok
int a, b; a=2; b=4; a = a/b; print(a);	-ok
int a, b; a=2; b=4; a = a%b; print(a);	-ok
int [3] v;v[0]=1;v[1]=2;print(v); -ok
int [3] a,b,c;a[0]=1;b[0]=2;b[1]=3;c=a+b;print(c); -ok

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
Symbol *traversalNode(struct _node *n){
	int  a, b, i;
	Symbol *pa, *pb;
	void *dataA, *dataB, *dataRz;
	Symbol *rz;
	int tmp, tmp_data;
	char buf[256];
	#ifdef DEBUG_INTERPRETER
	printf("traversalNode %s(%d) v:%d, s:%d, b:%d\n", convertTag(n->tag,buf), n, n->val, n->son, n->bro);
	#endif
	switch(n->tag){
	case TypeInfo:
		interpretTypeInfo(n);
		break;
	case ScalarAssign:
		pa=traversalNode(n->son);
		rz=getSymbol(n->val);
		rz->type=pa->type;
		rz->data=pa->data;
		break;
	case VectorAssign:
		pa=traversalNode(n->son);//val
		b=(int)n->son->bro;//col
		setVectorDataSymbol(n->val, (int)(pa->data), b);
		break;
	case MatrixAssign:
		pa=traversalNode(n->son);//val
		b=(int)n->son->bro->tag;//row
		tmp=(int)n->son->bro->val;//col
		setMatrixDataSymbol(n->val, (int)pa->data, b, tmp);
		break;
	case ADD_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;
		switch(pa->type->type){
			case ScalarType:
				dataRz=(void*)((int)dataA+(int)dataB);
				rz=mkSymbol(pa->type,dataRz);
			break;
			case VectorType:
				dataRz = v_copy(dataA,VNULL);
				v_add((VEC *)dataA,(VEC *)dataB,(VEC *)dataRz);
				rz=mkSymbol(pa->type, dataRz);
			break;
			case MatrixType:
				dataRz = m_copy(dataA, MNULL);
				m_add((MAT *)dataA,(MAT *)dataB,(MAT *)dataRz);
				rz=mkSymbol(pa->type, dataRz);
			break;
		}
		
		#ifdef DEBUG_INTERPRETER
		printf("%d=%d+%d\n",rz,a,b);
		#endif
		break;
	case SUB_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;
		switch(pa->type->type){
			case ScalarType:
				dataRz=(void*)((int)dataA-(int)dataB);
				rz=mkSymbol(pa->type,dataRz);
			break;
			case VectorType:
				dataRz = v_copy(dataA,VNULL);
				v_sub((VEC *)dataA,(VEC *)dataB,(VEC *)dataRz);
				rz=mkSymbol(pa->type, dataRz);
			break;
			case MatrixType:
				dataRz = m_copy(dataA, MNULL);
				m_sub((MAT *)dataA,(MAT *)dataB,(MAT *)dataRz);
				rz=mkSymbol(pa->type, dataRz);
			break;
		}
		
		#ifdef DEBUG_INTERPRETER
		printf("%d=%d-%d\n",rz,a,b);
		#endif
		break;
	case MUL_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;
		switch(pa->type->type){
			case ScalarType:
				dataRz=(void*)((int)dataA*(int)dataB);
				rz=mkSymbol(pa->type,dataRz);
			break;
			case VectorType:				
			break;
			case MatrixType:
				dataRz = m_copy(dataA, MNULL);
				m_mlt((MAT *)dataA,(MAT *)dataB,(MAT *)dataRz);
				rz=mkSymbol(pa->type, dataRz);
			break;

		}
		
		#ifdef DEBUG_INTERPRETER
		printf("%d=%d*%d\n",rz,a,b);
		#endif
		break;
	case DIV_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;
		switch(pa->type->type){
			case ScalarType:
				dataRz=(void*)((int)dataA*(int)dataB);
				rz=mkSymbol(pa->type,dataRz);
			break;
			case VectorType:				
			break;
		}
		
		#ifdef DEBUG_INTERPRETER
		printf("%d=%d/%d\n",rz,a,b);
		#endif
		break;

	case MOD_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;
		switch(pa->type->type){
			case ScalarType:
				dataRz=(void*)((int)dataA%(int)dataB);
				rz=mkSymbol(pa->type,dataRz);
			break;
			case VectorType:				
			break;
		}
		
		#ifdef DEBUG_INTERPRETER
		printf("%d=%d%%d\n",rz,a,b);
		#endif
		break;
	case POW_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;
		tmp = (int)dataA;
		tmp_data = (int)dataA;
		switch(pa->type->type){
			case ScalarType:
				for (i = 1; i < (int)dataB; i++)
					tmp_data *= tmp;
				dataA = (void*)(tmp_data);
				dataRz=(void*)((int)dataA);
				rz=mkSymbol(pa->type,dataRz);
			break;
			case VectorType:				
			break;
		}
		
		#ifdef DEBUG_INTERPRETER
		printf("%d=%d^%d\n",rz,a,b);
		#endif
		break;
	case ScalarID:
		rz=getSymbol(n->val);
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode getValFromSymbol(%d:%d)\n",n->val, rz);
		#endif
		break;
	case ScalarData:
		rz=(Symbol*)mkSymbol((Type *)IntegerScalarType,(void *)n->val);
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
