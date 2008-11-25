%{
	#include "simple.h"
	#include "simple.tab.h"
%}
%%
[0-9]+	{yylval.intVal = atoi(yytext); return (NUMBER);}
"int"	{yylval.intVal = INT; return(INT); }
[a-zA-Z]+ {yylval.intVal = insertSymbolTable(yytext); return (ID); }
[ \t]	;
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
\(		{yylval.intVal = OPEN_PARENTHESIS; return(OPEN_PARENTHESIS); };
\)		{yylval.intVal = CLOSE_PARENTHESIS; return(CLOSE_PARENTHESIS); };
%%
int isDuplicated(char *id)
{
	int i;
	for(i=0;i<nextSymbol;i++){
		if(0==strcmp(id, symbolTable[i]->id)){
			return 1;
		}
	}
	return 0;
}
int insertSymbolTable(char *id)
{
	if(nextSymbol>MAX_SYMBOL_SIZE){
		printf("The number of symbol is exceeded\n");
		exit(-1);
	}
	if(isDuplicated(id))
	{
		printf("Symbol(%s) is duplicated\n", id);
		exit(-1);
	}
	char *buf = malloc(strlen(id));
	strcpy(buf, id);
	symbolTable[nextSymbol]=malloc(sizeof(struct _symbol));
	symbolTable[nextSymbol]->id = buf;
	nextSymbol++;
	return nextSymbol-1;
}