#include <stdio.h>
#include <stdlib.h>
#include "symbol.h"
#include "interpreter.h"
#include "type.h"
#include "function.h"
void initializeFunction(int index, Type *t, StatementList *list, Node *params){
	Node *n = (Node *)params;
	Node *param;
	Function *f=malloc(sizeof(Function));
	Symbol *s;
	Type *paraType;
	f->symbol = getSymbol(index);
	f->symbol->function = 1;
	f->symbol->data = f;
	f->returnType = t;
	f->list = list;
	f->params = n;
	if(n){
		n=n->son;
		while(n){
			param=(Node *)n->val;
			s=getSymbol((int)param->val);
			s->type=(Type *)param->tag;
			s->scope=index;
			n=n->bro;
		}
	}
}
Symbol *callFunction(int index, Node *args){
	Function *f;
	Symbol *s = getSymbol(index);
	Symbol *rz;
	Node *params, *param, *exp;
	Symbol *sParam;
	if(!s->function){
		printf("id(%s) of function is not initialized\n", s->id);
		exit(-1);
	}
	f=s->data;
	params = f->params;
	if(params){
		params=params->son;
		args=args->son;
		while(params){
			if(!args){printf("argument missing\n");exit(-1);}
			param=(Node *)params->val;
			exp = (Node *)args->val;
			sParam=getSymbol((int)param->val);
			sParam->data = traversalNode(exp)->data;
			params=params->bro;
			args=args->bro;
		}
		if(args){printf("argument exceed\n");exit(-1);}
	}
	rz=interpretForFunction(f->list);
	return rz;
}
