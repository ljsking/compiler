%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include "intList.h"
	#include "node.h"
	#include "type.h"
	#include "statementList.h"
	#include "interpreter.h"
	#include "symbol.h"
	#include "simple.h"
	struct _statementList *root;
	struct _statementList *mkScalarAssignmentStatement(int, struct _node *);
%}

%union {
	struct _node *nodeVal;
	int	 intVal;
	char *strVal;
	struct _symbol *symbVal;
	struct _type *typeVal;
	struct _intList *intList;
	struct _statementList *stmtList;
}
%type  <stmtList> Program DeclareStatements Statements DeclareStatement Statement
%type  <nodeVal> IDList Exp ScalarTerm ScalarExp
%type  <typeVal> Type
%type  <intList> NumberList
%type  <intVal>  ScalarID

%token <intVal> ID INT BOOL NUMBER
%token <intVal> ASS_OP
%token <intVal> ADD_OP SUB_OP MUL_OP DIV_OP MOD_OP POW_OP
%token <intVal> LES_OP GRT_OP NOT_OP
%token <intVal> ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN
%token <intVal> LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token <intVal> INC_OP DEC_OP
%token <intVal> ELE_MUL_OP ELE_DIV_OP ELE_POW_OP
%token SEMICOLONE COMMA OPEN_ROUND_BRACKET CLOSE_ROUND_BRACKET OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET OPEN_BRACKET CLOSE_BRACKET PRINT WHILE
%left  MUL_OP DIV_OP MOD_OP POW_OP ELE_MUL_OP ELE_DIV_OP ELE_POW_OP
%right INC_OP DEC_OP NOT_OP
%left  ADD_OP SUB_OP LES_OP GRT_OP GE_OP LE_OP EQ_OP NE_OP AND_OP OR_OP
%%

Program		: DeclareStatements Statements{ 
						mergeStatementList($1,$2); 
						freeStatementList($2);
						root=$1;
					}
			| Statements{root=$$;}
			| DeclareStatements{root=$$;}

DeclareStatements : DeclareStatements DeclareStatement { 
						mergeStatementList($1,$2); 
						freeStatementList($2);
						$$=$1;
					}
				  | DeclareStatement
	

DeclareStatement : Type IDList SEMICOLONE { 
						$$=mkStatementListWithVal(mktree(TypeInfo, (int)$1, 0, $2));
					}
ScalarID 	: ID
			;

Type : INT {$$=mkScalarType(0);}
	 | BOOL{$$=mkScalarType(1);}
	 | INT OPEN_SQUARE_BRACKET NUMBER CLOSE_SQUARE_BRACKET{$$=mkVectorType(0, $3);}
	 | BOOL OPEN_SQUARE_BRACKET NUMBER CLOSE_SQUARE_BRACKET{$$=mkVectorType(1, $3);}
	 | INT OPEN_SQUARE_BRACKET NUMBER COMMA NUMBER CLOSE_SQUARE_BRACKET{$$=mkMatrixType(0, $3, $5);}
	 | BOOL OPEN_SQUARE_BRACKET NUMBER COMMA NUMBER CLOSE_SQUARE_BRACKET{$$=mkMatrixType(1, $3, $5);}
	 ;
	
NumberList   : NUMBER{ $$=mkIntList(); insertIntList($$, $1); }
		   	 | NumberList COMMA NUMBER { insertIntList($1, $3); $$=$1; }
	
IDList : ID {$$=mktree(IDList, 0, 0, mkleaf(ID, $1)); }
	   | IDList COMMA ID {$$=mkbro($1,mkleaf(ID, $3));}
	   ;

Statements	: Statements Statement 	{ 
							mergeStatementList($1,$2); 
							freeStatementList($2);
							$$=$1;
						}
			| Statement
			;

Statement 	: Exp SEMICOLONE { $$=mkStatementListWithVal($1);}
			| ScalarID ASS_OP Exp SEMICOLONE { $$=mkScalarAssignmentStatement($1, $3) }
			| PRINT OPEN_ROUND_BRACKET ID CLOSE_ROUND_BRACKET SEMICOLONE { $$ = mkStatementListWithVal(mkleaf(PRINT,$3)); }
			| WHILE OPEN_ROUND_BRACKET Exp CLOSE_ROUND_BRACKET OPEN_BRACKET Statements CLOSE_BRACKET {$$ = mkStatementListWithVal(mkleaf(WHILE,0));}
			;
			
Exp			: ScalarExp
			
ScalarExp	: ScalarExp ADD_OP ScalarTerm	{ $$=mktree(ScalarAdd, 0, $3, $1);}
			| ScalarExp SUB_OP ScalarTerm	{ $$=mktree(ScalarSub, 0, $3, $1);}
			| ScalarExp LES_OP ScalarTerm	{ $$=mktree(ScalarLes, 0, $3, $1);}
			| ScalarExp GRT_OP ScalarTerm	{ $$=mktree(ScalarGrt, 0, $3, $1);}
			| ScalarExp GE_OP ScalarTerm	{ $$=mktree(ScalarGE, 0, $3, $1);}
			| ScalarExp LE_OP ScalarTerm	{ $$=mktree(ScalarLE, 0, $3, $1);}
			| ScalarExp EQ_OP ScalarTerm	{ $$=mktree(ScalarEq, 0, $3, $1);}
			| ScalarExp NE_OP ScalarTerm	{ $$=mktree(ScalarNE, 0, $3, $1);}
			| ScalarExp AND_OP ScalarTerm	{ $$=mktree(ScalarAnd, 0, $3, $1);}
			| ScalarExp OR_OP ScalarTerm	{ $$=mktree(ScalarOr, 0, $3, $1);}
			| ScalarTerm					{ $$=$1;}
			;
	
ScalarTerm	: ScalarTerm MUL_OP ScalarTerm	{ $$=mktree($2, 0, $3, $1);}
			| ScalarTerm DIV_OP ScalarTerm	{ $$=mktree($2, 0, $3, $1);}
			| ScalarTerm MOD_OP ScalarTerm	{ $$=mktree($2, 0, $3, $1);}
			| ScalarTerm POW_OP ScalarTerm	{ $$=mktree($2, 0, $3, $1);}
			| ScalarTerm ELE_MUL_OP ScalarTerm	{ $$=mktree($2, 0, $3, $1);}
			| ScalarTerm ELE_DIV_OP ScalarTerm	{ $$=mktree($2, 0, $3, $1);}
			| ScalarTerm ELE_POW_OP ScalarTerm	{ $$=mktree($2, 0, $3, $1);}
			| INC_OP ScalarTerm		{ $$=mktree($1, 0, 0, $2);}
			| DEC_OP ScalarTerm		{ $$=mktree($1, 0, 0, $2);}
			| NOT_OP ScalarTerm		{ $$=mktree($1, 0, 0, $2);}
			| ScalarID			{ $$=mkleaf(ScalarID, $1);}
			| NUMBER			{ $$=mkleaf(ScalarData,$1);}
			;
%%

int yyerror() { puts("syntax error!"); }

int main() { 
	symbolTable = (struct _symbol **)malloc(sizeof(struct _symbol *)*MAX_SYMBOL_SIZE);
	yyparse();
	interpret(root);
	return 0;
}

struct _statementList *mkScalarAssignmentStatement(int id, struct _node *exp){
	return mkStatementListWithVal(mktree(ScalarAssign, id, 0, exp));
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
	case MOD_OP:
		strcpy(buff, "\%");break;
	case NUMBER:
		strcpy(buff, "NUM");break;
	case INC_OP:
		strcpy(buff, "++");break;
	case DEC_OP:
		strcpy(buff, "--");break;
	case NOT_OP:
		strcpy(buff, "!");break;
	case LE_OP:
		strcpy(buff, "<");break;	
	case GE_OP:
		strcpy(buff, "\%");break;
	case EQ_OP:
		strcpy(buff, "==");break;
	case NE_OP:
		strcpy(buff, "!=");break;
	case LES_OP:
		strcpy(buff, ">=");break;
	case GRT_OP:
		strcpy(buff, "<=");break;
	case OR_OP:
		strcpy(buff, "||");break;
	case AND_OP:
		strcpy(buff, "&&");break;
	case POW_OP:
		strcpy(buff, "pow");break;
	case ELE_MUL_OP:
		strcpy(buff, ".*");break;
	case ELE_DIV_OP:
		strcpy(buff, "./");break;
	case ELE_POW_OP:
		strcpy(buff, ".^");break;
	case ASS_OP:
		strcpy(buff, "=");break;
	case INT:
		strcpy(buff, "int");break;
	case BOOL:
		strcpy(buff, "bool");break;
	case ID:
		strcpy(buff, "symbol");break;
	case TypeInfo:
		strcpy(buff, "type");break;
	case IDList:
		strcpy(buff, "ids");break;
	case PRINT:
		strcpy(buff, "prnt");break;
	case WHILE:
		strcpy(buff, "while");break;
	case ScalarID:
		strcpy(buff, "scalarID");break;
	case ScalarData:
		strcpy(buff, "scalarData");break;
	case ScalarAdd:
		strcpy(buff, "scalarAdd");break;
	case ScalarAssign:
		strcpy(buff, "scalarAssign");break;
		
	default:
		strcpy(buff, "");break;
	}
	return buff;
}
