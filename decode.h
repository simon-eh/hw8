/**
 * Simon Ever-Hale
 * 11/29/2014
 * CSCI 241/Kuperman
 * Header file for all functions specific to decode.c.
 */

#ifndef DECODE_H

#define DECODE_H

#include "huffman.h"
#include <string.h>
#include <assert.h>

void read_tree(FILE*,tree*);
int get_bit(FILE*);
tree* get_char(FILE*,tree*);
void fix_eof(FILE*,tree*);
void print_pre(tree*,char*);

#endif
