%{
	#include <stdio.h>
	struct _node {
		char	kind;
		int		val;
		struct _node *bro, *son;
	};
	struct _node *mktree(char, int, struct _node *, struct _node *);
	struct _node *mkleaf(char, int);
%}

%union {
	struct _node *nodeVal;
	int	 intVal;
}

%type <nodeVal> Exp
%token <intVal> NUMBER
%left '+' '-' '*' '/'

%%
Exp	: Exp '+' Exp 		{ mktree('+', 0, $3, $1); printf("+ %d\n", $$); }
	| NUMBER		{ mkleaf('L', $1); printf("num %d\n", $$); }
	;
%%

int yyerror() { puts("syntax error!"); }

int main() { yyparse(); return 0; }

struct _node *mktree(char tag, int lval, struct _node *sibling, struct _node *son)
{
	struct _node *rz = malloc(sizeof(struct _node));
	rz->kind = tag;
	rz->val = lval;
	rz->son = son;
	son->bro = sibling;
	return rz;
}

struct _node *mkleaf(char tag, int lval)
{
	struct _node *rz = malloc(sizeof(struct _node));
	rz->kind = tag;
	rz->val = lval;
	return rz;
}