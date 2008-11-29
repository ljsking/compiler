#include <stdlib.h>
#include <stdio.h>
#include "intList.h"
#include "node.h"

struct _node *mktree(int tag, int lval, struct _node *sibling, struct _node *son){
	struct _node *rz = (struct _node *)malloc(sizeof(struct _node));
	#ifdef DEBUG_NODE
	printf("create node(%d)\n", rz);
	#endif
	rz->tag = tag;
	rz->val = lval;
	rz->son = son;
	son->bro = sibling;
	return rz;
}

struct _node *mkleaf(int tag, int lval){
	struct _node *rz = (struct _node *)malloc(sizeof(struct _node));
	#ifdef DEBUG_NODE
	printf("create node(%d)\n", rz);
	#endif
	rz->son = 0;
	rz->bro = 0;
	rz->tag = tag;
	rz->val = lval;
	return rz;
}

int printnode(struct _node *node, int height, int newlined){
	int i;
	if(!node)
		return 0;
	char buff[256];
	if(newlined)
		for(i=0;i<height-1;i++)
			printf("\t");
	printf("\t%s(%d)", convertTag(node->tag, buff), node->val);
	if(node->son)
		printnode(node->son, height+1, 0);
	if(node->bro){
		printf("\n");
		printnode(node->bro, height, 1);
	}
	return 0;
}

struct _node *mkbro(struct _node *parent, struct _node *bro){
	struct _node *pre;
	struct _node *target = parent->son;
	if(target == NULL)
		parent->son = bro;
	else{
		while(target->bro){
			target=target->bro;
		}
		target->bro = bro;
	}
	return parent;
}

void		 freeNode(struct _node *node){
	if(!node) return;
	freeNode(node->son);
	freeNode(node->bro);
	#ifdef DEBUG_NODE
	printf("delete node(%d)\n", node);
	#endif
	free(node);
}
