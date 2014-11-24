#include "encode.h"

#define CHSET_SIZE (1 << CHAR_BIT) //usually 256

int output_index = 0;
int output_value = 0;

char **char_codes;

int main(int argc, char *argv[]) {
	char_codes = malloc(sizeof(char*) * (CHSET_SIZE + 1));
	if(char_codes == NULL) {
		fprintf(stderr, "Error: inadequate heap space.\n");
		exit(1);
	}

	char *NULL_CHAR = malloc(sizeof(char));
	*NULL_CHAR = '\0';
	for(int i=0; i<CHSET_SIZE + 1; i++) {
		*(char_codes + i) = NULL_CHAR;
	}

	char_codes++;

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
	int c;
	while((c=fgetc(file)) != EOF) {
		weights[c]++;
	}
	for(int i=0; i<CHSET_SIZE; i++) {
		if(weights[i]) {
			head = insert(make_tree(weights[i], i), head);
		}
	}
	head=huf_encode(head);

	char *tmp_code = malloc(CHSET_SIZE*sizeof(char));
	*tmp_code = '\0';
	print_pre(head, tmp_code);
	free(tmp_code);

	char* eof_char = get_code(EOF);
	while(*eof_char) {
		print_bits(*(eof_char++) - '0');
		// putchar(*eof_char);
		// eof_char++;
	}

	rewind(file);

	print_encoded(file);

	for(int i=0; i<CHAR_BIT-1; i++) {
		print_bits(0);
	}

	// printf("\n%s\n", get_code(-1));

	// printf("\n");

	for(int i=-1; i<CHSET_SIZE; i++) {
		if(*get_code(i)) {
			// printf("Freeing %d: %s\n", i, get_code(i));
			free(get_code(i));
		}
	}
	free(char_codes - 1);

	fclose(file);
	clean(head);
	// for(int i=0; i<math.pow(2, CHAR_BIT)-1; i++) {

	// }
}

char* get_code(int c) {
	return *(char_codes + c);
}

void print_pre(tree *head, char* code) {
	if(head->left || head->right) {
		print_bits(0);
		// putchar('0');
		// putchar(' ');
	}
	else if(head == NULL) {
		printf("Unexpected leaf.\n");
		exit(1);
	}
	else {
		// putchar('1');
		print_bits(1);

		// putchar(' ');
		print_binary(head->c);
		// printf("Found leaf %c: %s\n", head->c, code);
		*(char_codes + head->c) = malloc(strlen(code) + 1);
		strcpy(*(char_codes + head->c), code);
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

void print_binary(int c) {
	for(int i=CHAR_BIT-1; i>=0; i--) {
		print_bits((c & (1<<i))?1:0);
		// printf("%d", c & (1 << i)?1:0);
	}
}

/* Print the contents of the file given a huffman encoding tree pointed to by head. Returns the index upon completion. */
void print_encoded(FILE *file) {
	char *character;
	int c;
	int past_eof = 0;
	while(!past_eof) {
		c = fgetc(file);
		past_eof = (c == EOF);
		// character = search(head, c);
		character = get_code(c);
		// char *origin = character;
		while(*character) {
			print_bits(*(character++) - '0');
			// putchar(*(character++));
		}
		// free(origin);
	}

}

void print_bits(int bit) {
	output_value = output_value | bit<<(CHAR_BIT - output_index - 1);
	if(output_index++ == 7) {
		printf("%c", output_value);
		output_value = 0;
		output_index = 0;
	}
}

/* Search the huffman tree for the symbol, returning its bitstring if found or an empty string if not found. Be sure to free after use. */
char* search(tree *head, int symbol) {
	char *code = malloc(100);
	if(code == NULL) {
		fprintf(stderr, "Inadequate heap space.\n");
		exit(1);
	}
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
	// print_list(head);
	// printf("\n");
	// printf("New head: %d, %d\n", head->c, head->weight);
	return head;
}

void print_list(tree* head) {
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

/* Insert the new_node into the tree and return the new head. */
tree* insert(tree *new_node, tree *head) {
	// printf("Before inserting element (%d, %d) ", new_node->c, new_node->weight);
	// print_list(head);
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
