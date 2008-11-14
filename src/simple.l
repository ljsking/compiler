%{
#include "simple.tab.h"
%}
%%
[0-9]+	{yylval.intVal = atoi(yytext); return (NUMBER);}
[ \t]	;
\n	return (0);
\+	return ('+');
\*	return ('*');
%%