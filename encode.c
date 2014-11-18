#include "encode.h"

#define CHSET_SIZE 255

int main(int argc, char *argv[]) {
	tree *head = make_tree(1, EOF);

	FILE *file = fopen(*(argv + 1), "r");
	if(file == NULL) {
		printf("Error: %s\n", strerror(errno));
		return 1;
	}
	int weights[CHSET_SIZE];
	for(int i=0; i<CHSET_SIZE; i++) {
		weights[i] = 0;
	}
	int c; //the problem is that i'm using eof as a head
	while((c=fgetc(file)) != EOF) {
		weights[c]++;
	}
	for(int i=0; i<CHSET_SIZE; i++) {
		if(weights[i]) {
			head = insert(make_tree(weights[i], i), head);
		}
	}
	head=huf_encode(head);
	// char code[100];
	// print_in(head, code, 0);
	print_pre(head);

	rewind(file);

	print_encoded(file, head);

	// int total = 0;
	// char* string;
	// while((c=fgetc(file)) != EOF) {
	// 	string = search(head, c);
	// 	total += strlen(string);
	// 	free(string);
	// }
	// string = search(head, c);
	// total += strlen(string);
	// free(string);

	// printf("Total size without encoding: %d bytes\n", head->weight*sizeof(char));
	// printf("Total size with encoding: %d bytes\n", total/8);



	fclose(file);
	clean(head);
}

void print_pre(tree *head) {
	if(head->left || head->right) {
		putchar('0');
		putchar(' ');
	}
	else if(head == NULL) {
		printf("Unexpected leaf.\n");
		return;
	}
	else {
		putchar('1');
		putchar(' ');
		print_binary(head->c);
		putchar(' ');
		return;
	}
	print_pre(head->left);
	print_pre(head->right);
}

void print_binary(int c) {
	for(int i=CHAR_BIT-1; i>=0; i--) {
		putchar((c & (1<<i))?'1':'0');
	}
}

void print_encoded(FILE *file, tree *head) {
	char *character;
	int c;
	int index = 0;
	int value = 0;
	while((c=fgetc(file)) != EOF) {
		character = search(head, c);
		for( ; *character; character++) {
			value = print_bits(index, *character - '0', value);
			if(index == CHAR_BIT-1) {
				index = 0;
			}
			else {
				index++;
			}
		}
	}
	while(index > 0 && index < CHAR_BIT) {
	    print_bits(index++, 0, value);
	}
}

int print_bits(int index, int bit, int value) {
	value = value | bit<<(CHAR_BIT - index - 1);
	if(index == 7) {
		printf("%c", value);
		return 0;
	}
	else {
		return value;
	}
}

/* Search the huffman tree for the symbol, returning its bitstring if found or an empty string if not found. Be sure to free after use. */
char* search(tree *head, int symbol) {
	char *code = malloc(100);
	*code = '\0';
	int index = 0;
	index = r_search(head, symbol, &code, 0);
	*(code + index) = '\0';
	return code;
}

int r_search(tree *head, int symbol, char** code, int index) {
	if(head->c == symbol) {
		return index;
	}
	else if(!head->left && !head->right) {
		return 0;
	}
	else if(head->left) {
		int i = r_search(head->left, symbol, code, index+1);
		if(i) {
			*(*code + index) = '0';
			return i;
		}
	}
	if(head->right) {
		int i = r_search(head->right, symbol, code, index+1);
		if(i) {
			*(*code + index) = '1';
			return i;
		}
	}
	return 0;
}

/* Encodes the list of singletons into a huffman tree and returns the head. */
tree* huf_encode(tree *head) {
	while((head=huffman_step(head))->next){}
	return head;
}

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

/* Performs one step of the huffman tree creation on the sorted list whose first node is pointed to by head. */
tree* huffman_step(tree *head) {
	tree *new_node = head;
	tree *old_head = head;
	if(head->next->next) {
		new_node=make_tree(head->weight + head->next->weight, 0);
		new_node->left = head;
		new_node->right = head->next;
		head = insert(new_node, head->next->next);
	}
	else if(head->next) { //only 2 elements
		new_node = make_tree(head->weight + head->next->weight, 0);
		new_node->left = head;
		new_node->right = head->next;
		head = new_node;
	}
	// if(head != old_head || !old_head->next || !old_head->next->next) {
	// 	result = new_node;
	// }
	// else {
	// 	result = head->next->next;
	// }
	if(old_head->next) {
		old_head->next->next = NULL; //gotta avoid infinite loops
	}
	old_head->next = NULL;
	// printf("New Ordering: ");
	// print_tree(head);
	// printf("\n");
	// printf("New head: %d, %d\n", head->c, head->weight);
	return head;
}

void print_tree(tree* head) {
	while(head != NULL) {
		// if(head->c >= 0) {
		// 	printf("%c: %d,", head->c, head->weight);
		// }
		// else {
		printf("(%d, %d),", head->c, head->weight);
		// }
		head = head->next;
	}
	printf("\n");
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

/* Insert the new_node into the tree and return the new head. */
tree* insert(tree *new_node, tree *head) {
	// printf("Before inserting element (%d, %d) ", new_node->c, new_node->weight);
	print_tree(head);
	// int i=0;
	tree *result = head;
	if(new_node->weight <= head->weight) {
		result = new_node;
		new_node->next = head;
	}
	else {
		while(head->next && head->next->weight < new_node->weight) {
			head = head->next;
			// i++;
		}
		tree *tmp = head->next;
		head->next = new_node;
		new_node->next = tmp;
	}

	return result;
}
