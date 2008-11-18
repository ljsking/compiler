%{
	#include <stdio.h>
	#include <string.h>
	struct _node {
		int 	tag;
		int		val;
		struct 	_node *bro, *son;
	};
	struct _node *mktree(int, int, struct _node *, struct _node *);
	struct _node *mkleaf(int, int);
	int			 printnode(struct _node *, int , int );
	struct _node *root;
%}

%union {
	struct _node *nodeVal;
	int	 intVal;
	char *strVal;
}

%type  <nodeVal> Statement Exp Term

%token <strVal> ID
%token <intVal> NUMBER INT
%token <intVal> ASS_OP
%token <intVal> ADD_OP SUB_OP MUL_OP DIV_OP MOD_OP POW_OP
%token <intVal> LES_OP GRT_OP NOT_OP
%token <intVal> ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN
%token <intVal> LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token <intVal> INC_OP DEC_OP
%token <intVal> OPEN_PARENTHESIS CLOSE_PARENTHESIS
%token <intVal> ELE_MUL_OP ELE_DIV_OP ELE_POW_OP
%token SEMICOLONE
%left  MUL_OP DIV_OP MOD_OP POW_OP ELE_MUL_OP ELE_DIV_OP ELE_POW_OP
%right INC_OP DEC_OP NOT_OP
%left  ADD_OP SUB_OP LES_OP GRT_OP GE_OP LE_OP EQ_OP NE_OP AND_OP OR_OP

%%
Statement 	: Exp SEMICOLONE { root=$1; root=$$;}
			| ID ASS_OP Exp { $$=mktree($2, (int)$1, 0, $3); root=$$;}

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
	| OPEN_PARENTHESIS Exp CLOSE_PARENTHESIS	{ $$=$2;}
	;
%%

int yyerror() { puts("syntax error!"); }

int main() { yyparse(); printnode(root, 1, 0); printf("\n"); return 0; }

struct _node *mktree(int tag, int lval, struct _node *sibling, struct _node *son)
{
	struct _node *rz = malloc(sizeof(struct _node));
	rz->tag = tag;
	rz->val = lval;
	rz->son = son;
	son->bro = sibling;
	return rz;
}

struct _node *mkleaf(int tag, int lval)
{
	struct _node *rz = malloc(sizeof(struct _node));
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