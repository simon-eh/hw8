#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


typedef struct tree {
	struct tree *left;
	struct tree *right;
	struct tree *next;
	int c;
	int weight;
} tree;

tree* make_tree(int,int);
int insert(tree*,tree*);
void print_tree(tree*);
tree* huffman_step(tree*);
tree* huf_encode(tree*);
void print_in(tree*,char[],int);
void clean(tree*);
char* search(tree*,int);
int r_search(tree*,int,char**,int);