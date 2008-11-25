%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "intList.h"
	#include "simple.h"
	#define TypeInfo 	1
	#define IDList		2
	
	struct _node {
		int 	tag;
		int		val;
		struct 	_node *bro, *son;
	};
	
	struct _type{
		int		type;
		int		numberDimension;
		int		maxDimension;
		int		*dimensions;
	};
	
	
	
	struct _node *mktree(int, int, struct _node *, struct _node *);
	struct _node *mkleaf(int, int);
	struct _node *mkbro(struct _node *, struct _node *);
	
	struct _type *mkType(int type);
	
	int			 printnode(struct _node *, int , int );
	struct _node *root;
	struct _symbol **symbolTable;
	int nextSymbol = 0;
%}

%union {
	struct _node *nodeVal;
	int	 intVal;
	char *strVal;
	struct _symbol *symbVal;
	struct _type *typeVal;
	struct _intList *intList;
}
%type  <nodeVal> Program DeclareStatements DeclareStatement IDList Statements Statement Exp Term
%type  <typeVal> Type ScalarType VectorType
%type  <intList> Dimensions Dimension

%token <intVal> ID INT BOOL NUMBER
%token <intVal> ASS_OP
%token <intVal> ADD_OP SUB_OP MUL_OP DIV_OP MOD_OP POW_OP
%token <intVal> LES_OP GRT_OP NOT_OP
%token <intVal> ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN
%token <intVal> LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token <intVal> INC_OP DEC_OP
%token <intVal> ELE_MUL_OP ELE_DIV_OP ELE_POW_OP
%token SEMICOLONE COMMA OPEN_ROUND_BRACKET CLOSE_ROUND_BRACKET OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET
%left  MUL_OP DIV_OP MOD_OP POW_OP ELE_MUL_OP ELE_DIV_OP ELE_POW_OP
%right INC_OP DEC_OP NOT_OP
%left  ADD_OP SUB_OP LES_OP GRT_OP GE_OP LE_OP EQ_OP NE_OP AND_OP OR_OP
%%

Program		: DeclareStatements Statements
			| Statements
			| DeclareStatements

DeclareStatements : DeclareStatements DeclareStatement {$$=mkbro($1,$2);root=$$;}
				  | DeclareStatement{
						struct _node *rz = (struct _node *)malloc(sizeof(struct _node));
						rz->tag = 0;
						rz->val = 0;
						rz->son = $1;
						rz->bro = 0;
						$$=rz; 
						root=$$;
					}
	

DeclareStatement : Type IDList SEMICOLONE { $$=mktree(TypeInfo, (int)$1, 0, $2);}

Type : ScalarType
	 | VectorType
	
ScalarType : INT {$$=mkType($1);}
		   | BOOL {$$=mkType($1);}
		
VectorType : ScalarType OPEN_SQUARE_BRACKET Dimensions CLOSE_SQUARE_BRACKET {
	printf("\nDimension!!\n");printIntList($3);
}
Dimensions : Dimension
		   | Dimensions COMMA Dimension { insertIntList($1, $3->elements[0]); freeIntList($3); $$=$1; }
Dimension  : NUMBER{ $$=mkIntList(); insertIntList($$, $1) }
	
IDList : ID {$$=mktree(IDList, 0, 0, mkleaf(ID, $1))}
	   | IDList COMMA ID {$$=mkbro($1,mkleaf(ID, $3));}

Statements	: Statements Statement {$$=mkbro($1,$2);root=$$;}
			| Statement {
				struct _node *rz = (struct _node *)malloc(sizeof(struct _node));
				rz->tag = 0;
				rz->val = 0;
				rz->son = $1;
				rz->bro = 0;
				$$=rz; 
				root=$$;
			}

Statement 	: Exp SEMICOLONE { root=$1;}
			| ID ASS_OP Exp SEMICOLONE { $$=mktree($2, $1, 0, $3);}

Exp	: Exp ADD_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp SUB_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp LES_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp GRT_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp GE_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp LE_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp EQ_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp NE_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp AND_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp OR_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term				{ $$=$1;}
	;
	
Term: Term MUL_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term DIV_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term MOD_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term POW_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term ELE_MUL_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term ELE_DIV_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term ELE_POW_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| INC_OP Term		{ $$=mktree($1, 0, 0, $2);}
	| DEC_OP Term		{ $$=mktree($1, 0, 0, $2);}
	| NOT_OP Term		{ $$=mktree($1, 0, 0, $2);}
	| NUMBER			{ $$=mkleaf(NUMBER, $1);}
	| OPEN_ROUND_BRACKET Exp CLOSE_ROUND_BRACKET	{ $$=$2;}
	;
%%

int yyerror() { puts("syntax error!"); }

int main() { 
	symbolTable = (struct _symbol **)malloc(sizeof(struct _symbol *)*MAX_SYMBOL_SIZE);
	yyparse();
	printnode(root, 1, 0);
	printf("\n");
	return 0;
}

struct _node *mktree(int tag, int lval, struct _node *sibling, struct _node *son)
{
	struct _node *rz = (struct _node *)malloc(sizeof(struct _node));
	rz->tag = tag;
	rz->val = lval;
	rz->son = son;
	son->bro = sibling;
	return rz;
}

struct _node *mkleaf(int tag, int lval)
{
	struct _node *rz = (struct _node *)malloc(sizeof(struct _node));
	rz->son = 0;
	rz->bro = 0;
	rz->tag = tag;
	rz->val = lval;
	return rz;
}

char *convertTag(int token, char *buff)
{
	switch(token)
	{
	case ADD_OP:
		strcpy(buff, "+");break;
	case SUB_OP:
		strcpy(buff, "-");break;
	case MUL_OP:
		strcpy(buff, "*");break;
	case DIV_OP:
		strcpy(buff, "/");break;
	case MOD_OP:
		strcpy(buff, "\%");break;
	case NUMBER:
		strcpy(buff, "NUM");break;
	case INC_OP:
		strcpy(buff, "++");break;
	case DEC_OP:
		strcpy(buff, "--");break;
	case NOT_OP:
		strcpy(buff, "!");break;
	case LE_OP:
		strcpy(buff, "<");break;	
	case GE_OP:
		strcpy(buff, "\%");break;
	case EQ_OP:
		strcpy(buff, "==");break;
	case NE_OP:
		strcpy(buff, "!=");break;
	case LES_OP:
		strcpy(buff, ">=");break;
	case GRT_OP:
		strcpy(buff, "<=");break;
	case OR_OP:
		strcpy(buff, "||");break;
	case AND_OP:
		strcpy(buff, "&&");break;
	case POW_OP:
		strcpy(buff, "pow");break;
	case ELE_MUL_OP:
		strcpy(buff, ".*");break;
	case ELE_DIV_OP:
		strcpy(buff, "./");break;
	case ELE_POW_OP:
		strcpy(buff, ".^");break;
	case ASS_OP:
		strcpy(buff, "=");break;
	case INT:
		strcpy(buff, "int");break;
	case BOOL:
		strcpy(buff, "bool");break;
	case ID:
		strcpy(buff, "symbol");break;
	case TypeInfo:
		strcpy(buff, "type");break;
	case IDList:
		strcpy(buff, "ids");break;
	default:
		strcpy(buff, "");break;
	}
	return buff;
}

int printnode(struct _node *node, int height, int newlined)
{
	int i;
	if(!node)
		return 0;
	char buff[256];
	if(newlined)
		for(i=0;i<height-1;i++)
			printf("\t");
	printf("\t%s(%d)", convertTag(node->tag, buff), node->val);
	if(node->son)
		printnode(node->son, height+1, 0);
	if(node->bro){
		printf("\n");
		printnode(node->bro, height, 1);
	}
	return 0;
}

struct _node *mkbro(struct _node *parent, struct _node *bro)
{
	struct _node *pre;
	struct _node *target = parent->son;
	if(target == NULL)
		parent->son = bro;
	else{
		while(target->bro){
			target=target->bro;
		}
		target->bro = bro;
	}
	return parent;
}

struct _type *mkType(int type)
{
	struct _type *t = (struct _type *)malloc(sizeof(struct _type));
	t->type = type;
	t->numberDimension = 0;
	return t;
}

void addDimension(struct _type *t, int dimension)
{
	if(t->numberDimension == 0){
		t->maxDimension = 10;
		t->dimensions = (int *)malloc(sizeof(int)*t->maxDimension);
	}
	if(t->numberDimension==t->maxDimension){
		printf("Exceed number of dimension\n");
		exit(-1);
	}
	t->numberDimension++;
	*(t->dimensions+t->numberDimension)=dimension;
}