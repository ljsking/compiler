#ifndef STATEMENTLIST_H
#define STATEMENTLIST_H
#include "node.h"
typedef struct _statementList{
	int				numberElement;
	int				maxElement;
	struct _node	**elements;
}StatementList;
struct _statementList *mkStatementList();
struct _statementList *mkStatementListWithVal(struct _node *);
void				  freeStatementList(struct _statementList *);
void 				  insertStatementList(struct _statementList *, struct _node *);
void				  mergeStatementList(struct _statementList *,struct _statementList *);				  
void				  printStatementList(struct _statementList *);
#endif
