#include <errno.h>
#include <string.h>
#include "huffman.h"

tree* insert(tree*,tree*);
void print_list(tree*);
tree* huffman_step(tree*);
tree* huf_encode(tree*);
char* search(tree*,int);
int r_search(tree*,int,char**,int);
void print_encoded(FILE*);
void print_bits(int);
void print_pre(tree*,char*);
void print_binary(int);
char* get_code(int);