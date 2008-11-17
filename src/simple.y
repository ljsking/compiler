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
}

%type  <nodeVal> Exp
%type  <nodeVal> Term

%token <intVal> NUMBER
%token <intVal> ASS_OP
%token <intVal> ADD_OP SUB_OP MUL_OP DIV_OP
%token <intVal> LES_OP GRT_OP NOT_OP
%token <intVal> ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN
%token <intVal> LE_OP GE_OP EQ_OP NE_OP
%token <intVal> INC_OP DEC_OP
%left  INC_OP DEC_OP MUL_OP DIV_OP ADD_OP SUB_OP

%%
Exp	: Exp ADD_OP Term	{ $$=mktree($2, 0, $3, $1); root=$$;}
	| Exp SUB_OP Term	{ $$=mktree($2, 0, $3, $1); root=$$;}
	| Term				{ $$=$1;}
	;
	
Term: Term MUL_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term DIV_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| INC_OP Term		{ $$=mktree($1, 0, 0, $2);}
	| DEC_OP Term		{ $$=mktree($1, 0, 0, $2);}
	| NUMBER			{ $$=mkleaf(NUMBER, $1);}
	;
%%

int yyerror() { puts("syntax error!"); }

int main() { yyparse(); printnode(root, 1, 0); return 0; }

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
	case NUMBER:
		strcpy(buff, "NUM");break;
	case INC_OP:
		strcpy(buff, "++");break;
	case DEC_OP:
		strcpy(buff, "--");break;
	}
	return buff;
}

int printnode(struct _node *node, int height, int newlined)
{
	int i;
	char buff[256];
	if(!node) return 0;
	if(newlined)
		for(i=0;i<height-1;i++)
			printf("\t");
	printf("\t%s(%d)", convertTag(node->tag, buff), node->val);
	printnode(node->son, height+1, 0);
	printf("\n");
	printnode(node->bro, height, 1);
	return 0;
}