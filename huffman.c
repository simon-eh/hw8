#include "encode.h"

/* Recursively frees the tree-list whos first node is pointed to by head. */
void clean(tree *head) {
	if(head->left != NULL) {
		clean(head->left);
	}
	if(head->right != NULL) {
		clean(head->right);
	}
	if(head->next != NULL) {
		clean(head->next);
	}
	free(head);
}

/* Intialize a singleton node for specified character and weight (frequency). */
tree* make_tree(int weight, int c) {
	tree *result = malloc(sizeof(tree));
	if(result == NULL) {
		fprintf(stderr, "Error: inadequate heap space.\n");
		exit(1);
	}
	result->c = c;
	result->weight = weight;
	result->next = NULL;
	result->left = NULL;
	result->right = NULL;
	return result;
}

void print_in(tree *head, char code[], int index) {
	if(head->left) {
		code[index] = '0';
		print_in(head->left, code, index+1);
	}
	if(head->right) {
		code[index] = '1';
		print_in(head->right, code, index+1);
	}
	if(!head->right && !head->left) {
		code[index]='\0';
		if(head->c >= 0 && head->c < 128) {
			printf("%c: %s\n", head->c, code);
		}
		else {
			printf("%d: %s\n", head->c, code);
		}
	}
}