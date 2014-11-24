CC=gcc
CFLAGS=-std=c99 -g -Wall -Wextra -pedantic

all: encode
encode: encode.c huffman.c
	$(CC) $(CFLAGS) encode.c huffman.c -o encode
decode: decode.c huffman.c
	$(CC) $(CFLAGS) decode.c huffman.c -o decode
# run: encode.exe
# 	./encode.exe encode.test > encode.huf
run: decode.exe encode.exe
	./decode.exe encode.huf
clean:
	# rm -f encode.exe
	# rm -f decode.exe