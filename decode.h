#include "huffman.h"
#include <string.h>
#include <assert.h>

void read_tree(FILE*,tree*);
int get_bit(FILE*);
tree* get_char(FILE*,tree*);
void fix_eof(FILE*,tree*);
void print_pre(tree*,char*);