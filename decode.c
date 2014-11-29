#include "decode.h"
/**
 * Simon Ever-Hale
 * 11/29/2014
 * CSCI 241/Kuperman
 * DECODE.C - Decodes a file that has been encoded using a Huffman tree.
 */

int input_index = -1;
int input_char = 0;

int at_eof = 0;
/* The main function which reads first the Huffman tree, then the encoded file, decoding and printing each character it reads. */
int main(int argc, char *argv[]) {
	tree *head = make_tree(0,0);
	FILE *file = NULL;
	if(argc > 1) {
		file = fopen(argv[1], "r");
		if(file == NULL) {
			fprintf(stderr, "Error opening file.\n");
			clean(head);
			exit(1);
	        }
	}
	else {
		fprintf(stderr, "Error opening file.\n");
		clean(head);
		exit(1);
	}

	read_tree(file, head);

	fix_eof(file, head);

	char *code = malloc(sizeof(char) * 100);
	*code = '\0';
	print_pre(head, code);
	free(code);

	tree *tmp;
	while((tmp=get_char(file, head))->c != EOF && !at_eof) {
		putchar(tmp->c);
	}
	// printf("At eof: %d\n", at_eof);
	// printf("Last char: %d\n", tmp->c);
	fclose(file);
	clean(head);
}

/* Find the location where EOF should go in the tree and replace it with the actual EOF symbol. */
void fix_eof(FILE *file, tree *head) {
	tree *character = get_char(file, head);
	// printf("Found EOF, character %d\n", character->c);
	character->c = EOF;
}

/* Print all the Huffman codes for each character in the tree using a preorder traversal. */
void print_pre(tree *head, char* code) {
	if(head->left || head->right) {
	}
	else if(head == NULL) {
		printf("Unexpected leaf.\n");
		exit(1);
	}
	else {
		// printf("Found leaf %c: %s\n", head->c, code);
		// putchar(' ');
		return;
	}
	int i = strlen(code);
	// printf("%s\n", code);
	*(code + i) = '0';
	*(code + i + 1) = '\0';
	print_pre(head->left, code);
	*(code + i) = '1';
	*(code + i + 1) = '\0';
	print_pre(head->right, code);
}

/* Read in the next character from file and return the node associated with it. */
tree* get_char(FILE *file, tree *head) {
	int bit;
	while(head->left && head->right) {
		bit = get_bit(file);
		if(bit == -1) {
			at_eof = 1;
			return head;
		}
		head = bit?head->right:head->left;
	}
	return head;
}

/* Reads in the Huffman tree recursively from the encoded file. */
void read_tree(FILE *file, tree *head) {
	int bit = get_bit(file);
	// putchar(' ');
	if(bit == 0) {

		head->left = make_tree(0,0);
		head->right = make_tree(0,0);
		read_tree(file, head->left);
		read_tree(file, head->right);
	}
	else if(bit == 1) {
		int character = 0;
		for(int i=CHAR_BIT-1; i>=0; i--) {
			character = character | (get_bit(file) << i);
		}
		// putchar(' ');
		// printf("Found character %d\n", character);
		head->c = character;
	}
}

/* Return the next bit in the file. */
int get_bit(FILE *file) {
	if(input_index == -1) {
		input_char = fgetc(file);
		input_index = CHAR_BIT-1;
	}
	if(input_char == EOF) {
		printf("Hit eof.\n");
		return -1;
	}
	int result = !!((1 << input_index--) & input_char);
	// if(input_index == -1) {
	// 	input_index = CHAR_BIT - 1;
	// 	input_char = '\0';
	// }
	// printf("%d", result);
	assert((result==0) || (result == 1));
	return result;
}
