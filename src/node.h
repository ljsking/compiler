#ifndef NODE_H
#define NODE_H
typedef struct _node {
	int 	tag;
	int		val;
	struct 	_node *bro, *son;
}Node;
struct _node *mktree(int, int, struct _node *, struct _node *);
struct _node *mkleaf(int, int);
struct _node *mkbro(struct _node *, struct _node *);
int			 printnode(struct _node *, int , int );
void		 freeNode(struct _node *);
#endif
