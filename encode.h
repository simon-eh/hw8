/**
 * Simon Ever-Hale
 * 11/29/2014
 * CSCI 241/Kuperman
 * Contains all necessary inclusions and prototypes for encode.c.
 */

#ifndef ENCODE_H

#define ENCODE_H

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

#endif
