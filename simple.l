%{
#include "y.tab.h"
%}
%%
[0-8]+	return(NUMBER);
[ \t]	;
\n	return(0);
\+	return('+');
\*	return('*');
.	{printf("'%c': illegal cahracter\n", yytext[0]); return(0);}
%%