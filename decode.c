#include "decode.h"

int input_index = CHAR_BIT-1;
int input_char = 0;

int at_eof = 0;

int main(int argc, char *argv[]) {
	tree *head = make_tree(0,0);
	FILE *file = fopen(argv[1], "r");
	if(file == NULL) {
		fprintf(stderr, "Error opening file.\n");
		exit(1);
	}
	read_tree(file, head);

	fix_eof(file, head);

	tree *tmp;
	while((tmp=get_char(file, head))->c != EOF && !at_eof) {
		putchar(tmp->c);
	}
	printf("Last char: %d\n", tmp->c);
	fclose(file);
	clean(head);
}

void fix_eof(FILE *file, tree *head) {
	tree *character = get_char(file, head);
	character->c = EOF;
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

void read_tree(FILE *file, tree *head) {
	int bit = get_bit(file);
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

int get_bit(FILE *file) {
	if(!input_char) {
		input_char = fgetc(file);
	}
	if(input_char == EOF) {
		return -1;
	}
	int result = !!((1 << input_index--) & input_char);
	if(input_index == -1) {
		input_index = CHAR_BIT - 1;
		input_char = '\0';
	}
	// printf("%d", result);
	return result;
}