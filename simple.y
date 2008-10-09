%{
#include <stdio.h>
%}
%token NUMBER
%%
Exp		: Exp '+' Term		{ printf("E->E+T\n"); }
		| Term				{ printf("E->T\n"); }
		;
Term	: Term '*' NUMBER	{ printf("T->T*T\n"); }
		| NUMBER			{ printf("T->num\n"); }
		;
%%
main()
{
	yyparse();
}
yyerror(char *s)
{
	printf("%s\n", s);
	exit(1);
}