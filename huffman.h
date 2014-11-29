/**
 * Simon Ever-Hale
 * 11/29/2014
 * CSCI 241/Kuperman
 * Contains all necessary prototypes and structs for huffman.h
 */

#ifndef HUFFMAN_H

#define HUFFMAN_H

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

#endif
