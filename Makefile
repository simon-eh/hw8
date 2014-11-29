CC=gcc
CFLAGS=-std=c99 -g -Wall -Wextra -pedantic

all: encode decode
encode: encode.c huffman.c
	$(CC) $(CFLAGS) encode.c huffman.c -o encode
decode: decode.c huffman.c
	$(CC) $(CFLAGS) decode.c huffman.c -o decode
clean:
	rm -f encode
	rm -f decode
