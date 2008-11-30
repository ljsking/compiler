%{
	#include "symbol.h"
	#include "simple.tab.h"
	int insertSymbolTable(char *);
%}
%%
[0-9]+	{yylval.intVal = atoi(yytext); return (POSITIVE_NUMBER);}
\-[0-9]+	{yylval.intVal = atoi(yytext); return (NEGATIVE_NUMBER);}
"int"	{yylval.intVal = INT; return(INT); }
"bool"  {yylval.intVal = BOOL; return(BOOL); }
"print" {return (PRINT);}
"while"	{return (WHILE);}
[a-zA-Z]+ {yylval.intVal = insertSymbolTable(yytext); return (ID); }
[ \t]	;
,		{return(COMMA);}
;		{return(SEMICOLONE);};
\n		return (0);

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
"&&"	{yylval.intVal = NE_OP; return(AND_OP); };
"||"	{yylval.intVal = NE_OP; return(OR_OP); };
\=		{yylval.intVal = ASS_OP; return(ASS_OP); };
\+		{yylval.intVal = ADD_OP; return(ADD_OP); };
\-		{yylval.intVal = SUB_OP; return(SUB_OP); };
\*		{yylval.intVal = MUL_OP; return(MUL_OP); };
\/		{yylval.intVal = DIV_OP; return(DIV_OP); };
\^		{yylval.intVal = POW_OP; return(POW_OP); };
\%		{yylval.intVal = MOD_OP; return(MOD_OP); };
\<		{yylval.intVal = LES_OP; return(LES_OP); };
\>		{yylval.intVal = GRT_OP; return(GRT_OP); };
\!		{yylval.intVal = NOT_OP; return(NOT_OP); };
".*"	{yylval.intVal = ELE_MUL_OP; return(ELE_MUL_OP); };
"./"	{yylval.intVal = ELE_DIV_OP; return(ELE_DIV_OP); };
".^"	{yylval.intVal = ELE_POW_OP; return(ELE_POW_OP); };
\(		{yylval.intVal = OPEN_ROUND_BRACKET; return(OPEN_ROUND_BRACKET); };
\)		{yylval.intVal = CLOSE_ROUND_BRACKET; return(CLOSE_ROUND_BRACKET); };
\[		{yylval.intVal = OPEN_SQUARE_BRACKET; return(OPEN_SQUARE_BRACKET); };
\]		{yylval.intVal = CLOSE_SQUARE_BRACKET; return(CLOSE_SQUARE_BRACKET); };
\{		{yylval.intVal = OPEN_BRACKET; return(OPEN_BRACKET); };
\}		{yylval.intVal = CLOSE_BRACKET; return(CLOSE_BRACKET); };
%%
