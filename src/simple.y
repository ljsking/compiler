%{
	#include <stdio.h>
	typedef struct _node {
		char	kind;
		int		val;
		struct _node *bro, *son;
	} node;
%}

%union {
	struct _node *nodeVal;
	int	 intVal;
}

%type <intVal> Exp
%token <intVal> NUMBER
%left '+' '-' '*' '/'

%%
Exp	: Exp '+' Exp 		{ $$ = $1 + $3; printf("+ %d\n", $$); }
	| NUMBER		{ $$=$1; printf("num %d\n", $$); }
	;
%%

int yyerror() { puts("syntax error!"); }
int main() { yyparse(); return 0; }