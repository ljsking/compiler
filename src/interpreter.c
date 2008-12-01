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
OK List
int main(){int a;a=2+2;print(a);}
int main(){int a;int[2]b;int[2,2]c;print(a);print(b);print(c);}
int main(){int a,b,c; a=2; b=3; c=a+b; print(c);}
int main(){int [3] v;v[0]=1;print(v);}
int main(){int [3,2] a;a[1,1]=2;print(a);}
int main(){int a, b; a=2; b=4; a = a-b; print(a);}
int main(){int a, b; a=2; b=4; a = a*b; print(a);}
int main(){int a, b; a=2; b=4; a = a/b; print(a);}
int main(){int a, b; a=2; b=4; a = a%b; print(a);}
int main(){int [3] v;v[0]=1;v[1]=2;print(v);}
int main(){int [3] a,b,c;a[0]=1;b[0]=2;b[1]=3;c=a+b;print(c);}
int main(){int a, b, c; a=1; b=2; c=a>b; print(c);}
int main(){int a,i;i=0;a=0;while(a<5){a=a+i;i=i+2;}print(a);}
int main(){test(); return 0;} // need to rise error.
int test(){int a;print(a);}int main(){int b;test();b=2;print(b);}

Working List
int test(){int a;a=2;return 2}int main(){int b;b=test();print(b);}

Need to work List
int a; a=[2,2]; print(a);
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
	int tmp, tmp_data, idata_a, idata_b;
	StatementList *list;
	char buf[256];
	#ifdef DEBUG_INTERPRETER
	printf("traversalNode %s(%d) v:%d, s:%d, b:%d\n", convertTag(n->tag,buf), n, n->val, n->son, n->bro);
	#endif
	switch(n->tag){
	case TypeInfo:
		interpretTypeInfo(n);
		break;
	case ScalarAssign:
		pa=traversalNode(n->son);//result
		rz=getSymbol(n->val);//symbol
		rz->type=pa->type;//type
		rz->data=pa->data;//data
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
			default:
				printf("Not allowed type in add\n");
				exit(-1);
			break;
		}
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
			default:
				printf("Not allowed type in sub\n");
				exit(-1);
			break;
		}
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
			case MatrixType:
				dataRz = m_copy(dataA, MNULL);
				m_mlt((MAT *)dataA,(MAT *)dataB,(MAT *)dataRz);
				rz=mkSymbol(pa->type, dataRz);
			break;
			default:
				printf("Not allowed type in mul\n");
				exit(-1);
			break;

		}
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
			default:
				printf("Not allowed type in div\n");
				exit(-1);
			break;
		}
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
			default:
				printf("Not allowed type in mod\n");
				exit(-1);
			break;
		}
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
			default:
				printf("Not allowed type in pow\n");
				exit(-1);
			break;
		}
		break;
	case GRT_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;

		idata_a = (int)dataA;
		idata_b = (int)dataB;
		switch(pa->type->type){
			case ScalarType:
				if (idata_a > idata_b)
					dataRz = (void*)1;
				else
					dataRz = (void*)0;
				rz=mkSymbol(pa->type,dataRz);
			break;
			default:
				printf("Not allowed type in GRT\n");
				exit(-1);
			break;
		}
		break;
	case LES_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;

		idata_a = (int)dataA;
		idata_b = (int)dataB;
		switch(pa->type->type){
			case ScalarType:
				if (idata_a < idata_b)
					dataRz = (void*)1;
				else
					dataRz = (void*)0;
				rz=mkSymbol(pa->type,dataRz);
			break;
			default:
				printf("Not allowed type in LES\n");
				exit(-1);
			break;
		}
		break;
	case GE_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;

		idata_a = (int)dataA;
		idata_b = (int)dataB;
		switch(pa->type->type){
			case ScalarType:
				if (idata_a >= idata_b)
					dataRz = (void*)1;
				else
					dataRz = (void*)0;
				rz=mkSymbol(pa->type,dataRz);
			break;
			default:
				printf("Not allowed type in GE\n");
				exit(-1);
			break;
		}
		break;
	case LE_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;

		idata_a = (int)dataA;
		idata_b = (int)dataB;
		switch(pa->type->type){
			case ScalarType:
				if (idata_a <= idata_b)
					dataRz = (void*)1;
				else
					dataRz = (void*)0;
				rz=mkSymbol(pa->type,dataRz);
			break;
			default:
				printf("Not allowed type in LE\n");
				exit(-1);
			break;
		}
		break;
	case EQ_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;

		idata_a = (int)dataA;
		idata_b = (int)dataB;
		switch(pa->type->type){
			case ScalarType:
				if (idata_a == idata_b)
					dataRz = (void*)1;
				else
					dataRz = (void*)0;
				rz=mkSymbol(pa->type,dataRz);
			break;
			default:
				printf("Not allowed type in EQ\n");
				exit(-1);
			break;
		}
		break;
	case NE_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;

		idata_a = (int)dataA;
		idata_b = (int)dataB;
		switch(pa->type->type){
			case ScalarType:
				if (idata_a != idata_b)
					dataRz = (void*)1;
				else
					dataRz = (void*)0;
				rz=mkSymbol(pa->type,dataRz);
			break;
			default:
				printf("Not allowed type in EQ\n");
				exit(-1);
			break;
		}
		break;
	case INC_OP:
		pa=traversalNode(n->son->bro);
		
		dataA = pa->data;
		
		idata_a = (int)dataA;
		
		switch(pa->type->type){
			case ScalarType:
				idata_a = idata_a + 1;
				dataRz = (void*)idata_a;
				rz=mkSymbol(pa->type,dataRz);
			break;
			default:
				printf("Not allowed type in inc\n");
				exit(-1);
			break;
		}
		break;
	case ID:
		rz=getSymbol(n->val);
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode getValFromSymbol(%d:%d)\n",n->val, rz);
		#endif
		break;
	case NUMBER:
		rz=(Symbol*)mkSymbol((Type *)IntegerScalarType,(void *)n->val);
		break;
	case WHILE:
		n=n->son;//exp
		list = (StatementList *)n->bro;//statements
		pa = traversalNode(n);
		if(pa->type->type!=ScalarType){
			printf("while's exp is not scalar\n");
			exit(-1);
		}
		while(idata_a){
			interpret(list);
			pa = traversalNode(n);
			idata_a = (int)(pa->data);
		}
		break;
	case PRINT:
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode PRINT(%d)\n",n->val);
		#endif
		printSymbolByIndex(n->val);
		break;
	case FunctionCall:
		idata_a = n->val;//id index
		callFunction(idata_a);
	break;
	}
	return rz;
}
