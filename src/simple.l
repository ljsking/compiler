%{
#include "simple.tab.h"
%}
%%
[0-9]+	{yylval.intVal = atoi(yytext); return (NUMBER);}
[ \t]	;
\n	return (0);
"+="	{yylval.intVal = ADD_ASSIGN; return(ADD_ASSIGN); };
"-="	{yylval.intVal = SUB_ASSIGN; return(SUB_ASSIGN); };
"*="	{yylval.intVal = MUL_ASSIGN; return(MUL_ASSIGN); };
"/="	{yylval.intVal = DIV_ASSIGN; return(DIV_ASSIGN); };
"++"	{yylval.intVal = INC_OP; return(INC_OP); };
"--"	{yylval.intVal = DEC_OP; return(DEC_OP); };
"<="	{yylval.intVal = LE_OP; return(LE_OP); };
">="	{yylval.intVal = GE_OP; return(GE_OP); };
"=="	{yylval.intVal = EQ_OP; return(EQ_OP); };
"!="	{yylval.intVal = NE_OP; return(NE_OP); };
\=		{yylval.intVal = ASS_OP; return(ASS_OP); };
\+		{yylval.intVal = ADD_OP; return(ADD_OP); };
\-		{yylval.intVal = SUB_OP; return(SUB_OP); };
\*		{yylval.intVal = MUL_OP; return(MUL_OP); };
\/		{yylval.intVal = DIV_OP; return(DIV_OP); };
\<		{yylval.intVal = LES_OP; return(LES_OP); };
\>		{yylval.intVal = GRT_OP; return(GRT_OP); };
\!		{yylval.intVal = NOT_OP; return(NOT_OP); };
\(		{yylval.intVal = OPEN_PARENTHESIS; return(OPEN_PARENTHESIS); };
\)		{yylval.intVal = CLOSE_PARENTHESIS; return(CLOSE_PARENTHESIS); };
%%