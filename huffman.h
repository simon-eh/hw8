#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
	struct tree *left;
	struct tree *right;
	struct tree *next;
	int c;
	int weight;
} tree;

tree* make_tree(int,int);
void clean(tree*);
void print_in(tree*,char[],int);