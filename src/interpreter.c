#include <stdio.h>
#include <stdlib.h>
#include "mesch/matrix.h"
#include "simple.tab.h"
#include "simple.h"
#include "type.h"
#include "symbol.h"
#include "function.h"
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
int test(){int a;a=2;return a;}int main(){int b;b=test();print(b);}
int main(){int a;if(1){print(a);}}
int main(){int a;if(0){print(a);}}
int main(){int a;a=1;if(a){print(a);}}
int main(){int a,b;a=1;if(a){print(a);}else{print(b);}}
int main(){int a,b;a=0;b=1;if(a){print(a);}else{print(b);}}
int main(){int [2] a, b; int c; a[0]=1; a[1]=2; b[0]=3; b[1]=4; c=a.*b; print(c);}
int main(){int [2] a, b; int c; a[0]=1; a[1]=2; b[0]=3; b[1]=4; c=a./b; print(c);}
int main(){int [2] a, b; int c; a[0]=1; a[1]=2; b[0]=3; b[1]=4; c=a.^b; print(c);}
int test(){int a;a=2;print(a);}int main(){int a;a=3;test();print(a);} //print 2, 3 because scope
int test(int a, int b){return a+b;}int main(){int c;c=test(2,3);print(c);}
int test(int a, int b){print(2);return 3;}int main(){int a,b,c;c=test(a,b);print(c);}
int test(){return 2;}int main(){int a;a=test();print(a);}

Working List

Need to work List
int a; a=[2,2]; print(a);
*/
void interpretForMain(struct _statementList *list){
	int i;
	for(i=0;i<list->numberElement;i++){
		traversalNode(list->elements[i]);
	}
}
Symbol *interpretForFunction(struct _statementList *list){
	int i;
	Symbol *rz;
	Node *lastNode;
	for(i=0;i<list->numberElement;i++){
		rz=traversalNode(list->elements[i]);
	}
	lastNode = list->elements[list->numberElement-1];
	if(lastNode->tag!=RETURN)
		rz=NULL;
	return rz;
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
	int  a, b, i, j, k, l;
	Symbol *pa, *pb;
	void *dataA, *dataB, *dataRz;
	Symbol *rz;
	VEC *vec1, *vec2;
	MAT *mat1, *mat2;
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
	case ELE_MUL_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;
		idata_a = (int)dataA;
		idata_b = (int)dataB;

		vec1 = (VEC*)dataA;
		vec2 = (VEC*)dataB;

		mat1 = (MAT*)dataA;
		mat2 = (MAT*)dataB;

		switch(pa->type->type){
			case ScalarType:
				dataRz=(void*)((int)dataA*(int)dataB);
				rz=mkSymbol(pa->type,dataRz);
			break;
			case VectorType:
				tmp = 0;
				for (i = 0; i < vec1->dim; i++)
				{
					tmp += vec1->ve[i]*vec2->ve[i];
				}
				dataRz=(void*)((int)tmp);
				
				rz=mkSymbol(mkScalarType(0),dataRz);
			break;
			case MatrixType:
				tmp = 0;
				for (i = 0; i < mat1->m; i++)
				{
					for (j = 0; j < mat1->n; j++)
					{
						tmp += mat1->me[i][j]*mat2->me[i][j];
					}						
				}
				dataRz=(void*)((int)tmp);
				
				rz=mkSymbol(mkScalarType(0),dataRz);
			break;
			default:
				printf("Not allowed type in vector .* vector = scalar\n");
				exit(-1);
			break;
		}
		break;
	case ELE_DIV_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;
		idata_a = (int)dataA;
		idata_b = (int)dataB;

		vec1 = (VEC*)dataA;
		vec2 = (VEC*)dataB;

		mat1 = (MAT*)dataA;
		mat2 = (MAT*)dataB;

		switch(pa->type->type){
			case ScalarType:
				dataRz=(void*)((int)dataA/(int)dataB);
				rz=mkSymbol(pa->type,dataRz);
			break;
			case VectorType:
				tmp = 0;
				for (i = 0; i < vec1->dim; i++)
				{
					tmp += vec1->ve[i]/vec2->ve[i];
				}
				dataRz=(void*)((int)tmp);
				
				rz=mkSymbol(mkScalarType(0),dataRz);
			break;
			case MatrixType:
				tmp = 0;
				for (i = 0; i < mat1->m; i++)
				{
					for (j = 0; j < mat1->n; j++)
					{
						tmp += mat1->me[i][j]/mat2->me[i][j];
					}						
				}
				dataRz=(void*)((int)tmp);
				
				rz=mkSymbol(mkScalarType(0),dataRz);
			break;
			default:
				printf("Not allowed type in vector ./ vector = scalar\n");
				exit(-1);
			break;
		}
		break;
	case ELE_POW_OP:
		pa=traversalNode(n->son);
		pb=traversalNode(n->son->bro);
		
		dataA = pa->data;
		dataB = pb->data;
		idata_a = (int)dataA;
		idata_b = (int)dataB;

		vec1 = (VEC*)dataA;
		vec2 = (VEC*)dataB;

		mat1 = (MAT*)dataA;
		mat2 = (MAT*)dataB;

		switch(pa->type->type){
			case ScalarType:
				dataRz=(void*)((int)dataA/(int)dataB);
				rz=mkSymbol(pa->type,dataRz);
			break;
			case VectorType:
				tmp = 0;
				tmp_data = 0;
				for (i = 0; i < vec1->dim; i++)
				{
					tmp = 1;
					for (j = 0; j < vec2->ve[i]; j++)
					{
						tmp *= vec1->ve[i];
					}
					tmp_data += tmp;
				}
				dataRz=(void*)((int)tmp_data);
				
				rz=mkSymbol(mkScalarType(0),dataRz);
			break;
			case MatrixType:
				tmp_data = 0;
				for (i = 0; i < mat1->m; i++)
				{
					for (j = 0; j < mat1->n; j++)
					{
						tmp = 1;
						for (k = 0; k < mat2->me[i][j]; k++)
						{
							tmp *= mat1->me[i][j];
						}
						tmp_data += tmp;
					}						
				}
				dataRz=(void*)((int)tmp_data);
				
				rz=mkSymbol(mkScalarType(0),dataRz);
			break;
			default:
				printf("Not allowed type in vector ./ vector = scalar\n");
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
	case NOT_OP:
		pa=traversalNode(n->son);
				
		dataA = pa->data;
		
		idata_a = (int)dataA;
		
		switch(pa->type->type){
			case ScalarType:
				if (idata_a == 0)
					dataRz = (void*)1;
				else
					dataRz = (void*)0;
				rz=mkSymbol(pa->type,dataRz);
			break;
			default:
				printf("Not allowed type in not\n");
				exit(-1);
			break;
		}
		break;
	case INC_OP:
		pa=traversalNode(n->son);
				
		dataA = pa->data;
		
		idata_a = (int)dataA;
		
		switch(pa->type->type){
			case ScalarType:
				idata_a = idata_a + 1;
				dataRz = (void*)(idata_a);
				pa->data = (void*)idata_a;
				rz=mkSymbol(pa->type,dataRz);
			break;
			default:
				printf("Not allowed type in inc\n");
				exit(-1);
			break;
		}
		break;
	case DEC_OP:
		pa=traversalNode(n->son);
				
		dataA = pa->data;
		
		idata_a = (int)dataA;
		
		switch(pa->type->type){
			case ScalarType:
				idata_a = idata_a - 1;
				dataRz = (void*)(idata_a);
				pa->data = (void*)idata_a;
				rz=mkSymbol(pa->type,dataRz);
			break;
			default:
				printf("Not allowed type in dec\n");
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
		rz=mkSymbol((Type *)IntegerScalarType,(void *)n->val);
		break;
	case WHILE:
		n=n->son;//exp
		list = (StatementList *)n->bro;//statements
		pa = traversalNode(n);
		if(pa->type->type!=ScalarType){
			printf("while's exp is not scalar\n");
			exit(-1);
		}
		idata_a = (int)(pa->data);
		while(idata_a){
			interpretForMain(list);
			pa = traversalNode(n);
			idata_a = (int)(pa->data);
		}
		break;
	case IF:
		list =(StatementList *)n->val;
		n=n->son;
		pa = traversalNode(n);//exp
		if(pa->type->type!=ScalarType){
			printf("if's exp is not scalar\n");
			exit(-1);
		}
		idata_a = (int)(pa->data);
		if(idata_a){
			interpretForMain(list);//list
		}
		list=(StatementList *)n->bro;//else
		if(list&&!idata_a){
			interpretForMain(list);//list
		}
		break;
	case PRINT:
		#ifdef DEBUG_INTERPRETER
		printf("traversalNode PRINT(%d)\n",n->val);
		#endif
		n=(Node *)n->val;//exp
		pa = traversalNode(n);
		printSymbol(pa);
		break;
	case FunctionCall:
		idata_a = getScope(); //previous id
		idata_b = (int)(n->val); //function id;
		setScope(idata_b);
		rz=callFunction(idata_b, n->son);//id_index
		setScope(idata_a);
		break;
	case RETURN:
		n=(Node *)n->val;
		rz=traversalNode(n);
		break;
	}
	return rz;
}
