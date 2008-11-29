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
	struct _statementList *mkAssignmentStatementWithoutVal(int, struct _node *);
	struct _statementList *mkAssignmentStatement(int, struct _node *, struct _intList *);
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
%type  <nodeVal> IDList Exp Term Vector
%type  <typeVal> Type ScalarType VectorType
%type  <intList> NumberList

%token <intVal> ID INT BOOL NUMBER
%token <intVal> ASS_OP
%token <intVal> ADD_OP SUB_OP MUL_OP DIV_OP MOD_OP POW_OP
%token <intVal> LES_OP GRT_OP NOT_OP
%token <intVal> ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN
%token <intVal> LE_OP GE_OP EQ_OP NE_OP AND_OP OR_OP
%token <intVal> INC_OP DEC_OP
%token <intVal> ELE_MUL_OP ELE_DIV_OP ELE_POW_OP
%token SEMICOLONE COMMA OPEN_ROUND_BRACKET CLOSE_ROUND_BRACKET OPEN_SQUARE_BRACKET CLOSE_SQUARE_BRACKET PRINT
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

Type : ScalarType
	 | VectorType
	
ScalarType : INT {$$=integer;}
		   | BOOL {$$=boolean;}
		
VectorType : ScalarType OPEN_SQUARE_BRACKET NumberList CLOSE_SQUARE_BRACKET {
					setDimensionType($1, $3);
				}
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
			| ID ASS_OP Exp SEMICOLONE { $$=mkAssignmentStatementWithoutVal($1, $3) }
			| ID OPEN_SQUARE_BRACKET NumberList CLOSE_SQUARE_BRACKET ASS_OP Exp SEMICOLONE{
				$$=mkAssignmentStatement($1, $6, $3);
			}
			| PRINT OPEN_ROUND_BRACKET ID CLOSE_ROUND_BRACKET SEMICOLONE { $$ = mkStatementListWithVal(mkleaf(PRINT,$3)); }

Exp	: Exp ADD_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp SUB_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp LES_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp GRT_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp GE_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp LE_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp EQ_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp NE_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp AND_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Exp OR_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term				{ $$=$1;}
	;
	
Term: Term MUL_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term DIV_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term MOD_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term POW_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term ELE_MUL_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term ELE_DIV_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| Term ELE_POW_OP Term	{ $$=mktree($2, 0, $3, $1);}
	| INC_OP Term		{ $$=mktree($1, 0, 0, $2);}
	| DEC_OP Term		{ $$=mktree($1, 0, 0, $2);}
	| NOT_OP Term		{ $$=mktree($1, 0, 0, $2);}
	| Vector			
	| ID				{ $$=mkleaf(ID, $1);}
	| OPEN_ROUND_BRACKET Exp CLOSE_ROUND_BRACKET	{ $$=$2;}
	;
	
Vector	:	NUMBER  { $$=mkleaf(Vector, (int)mkIntList()); insertIntList((struct _intList*)($$->val), $1); }
		|	OPEN_SQUARE_BRACKET NumberList CLOSE_SQUARE_BRACKET { $$=mkleaf(Vector, (int)$2);}
		;
%%

int yyerror() { puts("syntax error!"); }

int main() { 
	symbolTable = (struct _symbol **)malloc(sizeof(struct _symbol *)*MAX_SYMBOL_SIZE);
	initScalarType();
	yyparse();
	interpret(root);
	return 0;
}

struct _statementList *mkAssignmentStatementWithoutVal(int id, struct _node *exp){
	struct _intList *list=mkIntList(); 
	insertIntList(list, 0);
	return mkAssignmentStatement(id, exp, list);
}

struct _statementList *mkAssignmentStatement(int id, struct _node *exp, struct _intList *val){
	return mkStatementListWithVal(mktree(ASS_OP, id, exp, mkleaf(NumberList, (int)val)));
}


char *convertTag(int token, char *buff)
{
	printf("convertTag token %d buff %d\n", token, buff);
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
	default:
		strcpy(buff, "");break;
	}
	return buff;
}
