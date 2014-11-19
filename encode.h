#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <limits.h>


typedef struct tree {
	struct tree *left;
	struct tree *right;
	struct tree *next;
	int c;
	int weight;
} tree;

tree* make_tree(int,int);
tree* insert(tree*,tree*);
void print_list(tree*);
tree* huffman_step(tree*);
tree* huf_encode(tree*);
void print_in(tree*,char[],int);
void clean(tree*);
char* search(tree*,int);
int r_search(tree*,int,char**,int);
void print_encoded(FILE*);
void print_bits(int);
void print_pre(tree*,char*);
void print_binary(int);
char* get_code(int);