all: sources

.PHONY: all test clean

test:

clean:
	rm -rf bin/*

sources:
	mkdir -p bin/sources
	$(CC) sources/i1.c -o bin/sources/i1
	$(CC) sources/i2.c -o bin/sources/i2
	$(CC) sources/i3.c -o bin/sources/i3
	$(CC) sources/i4.c -o bin/sources/i4

huffman:
	mkdir -p bin
	$(CC) huffkoder.c -o bin/huffkoder
	$(CC) huffdekoder.c -o bin/huffdekoder

lzw:
	mkdir -p bin
	$(CC) lzwkoder.c -o bin/lzwkoder
	$(CC) lzwdekoder.c -o bin/lzwdekoder

linearbinarycoder:
	mkdir -p bin
	$(CC) linbinkoder.c -o bin/linbinkoder
	$(CC) linbindekoder.c -o bin/linbindekoder

channel:
	mkdir -p bin
	$(CC) binsimkanal.c -o bin/binsimkanal
