%{
#include "simple.tab.h"
%}
%%
[0-9]+	{yylval.intVal = atoi(yytext); return (NUMBER);}
[ \t]	;
\n	return (0);
"+="	return(ADD_ASSIGN);
"-="	return(SUB_ASSIGN);
"*="	return(MUL_ASSIGN);
"/="	return(DIV_ASSIGN);
"++"	return(INC_OP);
"--"	return(DEC_OP);
"<="	return(LE_OP);
">="	return(GE_OP);
"=="	return(EQ_OP);
"!="	return(NE_OP);
\=		return(ASS_OP);
\+		return(ADD_OP);
\-		return(SUB_OP);
\*		return(MUL_OP);
\/		return(DIV_OP);
\<		return(LES_OP);
\>		return(GRT_OP);
\!		return(NOT_OP);
%%