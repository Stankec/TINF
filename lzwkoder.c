#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <ctype.h>
#include <string.h>
/* trie.c */
typedef struct kidnode {
	int code;
	int myChar;
} kidNode;
typedef struct node {
	int pref;
	int newChar;
	int seen;
	int numKids;
	kidNode *kids;
} Node;
void trieAdd(Node *root, int p, int c, int index);
void arrayAdd(Node *root, int p, int c, int index);
void createTrie(Node **root, int bits);
void initTrie(Node *trie, int eFlag);
void reallocTrie(Node **trie, int bits);
void trieRemove(Node *root, int index);
int searchTrie(Node *root, int p, int c);
void destroyTrie(Node *root, int size);
int binarySearch(kidNode *node, int find, int start, int last);
int topSearch(kidNode *node, int find, int last);
void printTrie(Node *root, int x);
void printArray(kidNode *array, int c);
int putString(Node* root, int *fK, int code, FILE *output);
int pruneTrie(Node *trie, Node *newTrie, int index, int empty);
int seen(Node *trie, int code);
void printChildren(kidNode *node, int count);
/* trie.c */
#define die(msg) exit (fprintf (stderr, "%s", msg))
void createTrie (Node **root, int bits)
{
	*root = (Node *) malloc (sizeof (Node) * (1 << bits));
	return;
}
void reallocTrie(Node **node, int bits){
	*node = (Node *) realloc (*node, sizeof (Node) * (1 << bits));
	return;
}
void initTrie (Node *trie, int eFlag){
	trie[0].newChar = 0;
	trie[0].seen = 0;
	trie[0].pref = 0;
	if (eFlag == 0) {
		trie[0].numKids = 256;
		trie[0].kids = (kidNode*) malloc (sizeof (kidNode) * 256);
		for(int i = 0; i < 256; i++) {
			trie[0].kids[i].myChar = i;
			trie[0].kids[i].code = i + 1;
			int j = i + 1;
			trie[j].pref = 0;
			trie[j].numKids = 0;
			trie[j].seen = 0;
			trie[j].kids = NULL;
			trie[j].newChar = i;
		}
	}
	else{
		trie[0].numKids = 0;
		trie[0].kids = NULL;
	}
}
void arrayAdd(Node *root, int p, int c, int index){
	root[index].kids = NULL;
	root[index].numKids = 0;
	root[index].seen = 1;
	root[index].newChar = c;
	root[index].pref = p;
	return;
}
void trieAdd(Node *root, int p, int c, int index){
	arrayAdd(root, p, c, index);
	if(root[p].kids == NULL) {
		root[p].kids = (kidNode *) malloc (sizeof (kidNode) * 2);
		root[p].numKids = 1;
		root[p].kids[0].code = index;
		root[p].kids[0].myChar = c;
	}
	else{
		int i = 0;
		for(i = 0; i >= 0; i++) {
			if(i == root[p].numKids) {
				break;
			}
			if(c > root[p].kids[i].myChar) {
				continue;
			}
			if(c < root[p].kids[i].myChar)
				break;
		}
		root[p].kids = (kidNode *) realloc (root[p].kids,
		                                    (sizeof (kidNode) * (root[p].numKids + 1)));
		if(root[p].numKids != i) {
			int j = root[p].numKids - 1;
			while(j >= i) {
				root[p].kids[j+1].code = root[p].kids[j].code;
				root[p].kids[j+1].myChar = root[p].kids[j].myChar;
				j--;
			}
			root[p].kids[i].code = index;
			root[p].numKids = root[p].numKids + 1;
			root[p].kids[i].myChar = c;
		}
		else if(root[p].numKids == i) {
			root[p].kids[i].code = index;
			root[p].numKids = root[p].numKids + 1;
			root[p].kids[i].myChar = c;
		}
	}
}
int searchTrie(Node *root, int c, int k){
	if(root[c].kids == NULL) {
		printf("null root");
		return -1;
	}
	int index = binarySearch(root[c].kids, k, 0, root[c].numKids - 1);
	if(index == -1) {
		return -1;
	}
	else{
		if(c != 0)
			root[c].seen = root[c].seen + 1;
		return root[c].kids[index].code;
	}
}
void destroyTrie(Node *root, int index){
	for(int i = 0; i < index; i++) {
		if (root[i].kids != NULL)
			free(root[i].kids);
	}
	free(root);
}
int seen(Node *root, int code){
	if(code < 0)
		die("Invalid code passed to trie.c");
	if(root[code].pref == 0) {
		root[code].seen = root[code].seen + 1;
		return 1;
	}
	root[code].seen = root[code].seen + 1;
	seen(root, root[code].pref);
	return 1;
}
int pruneTrie(Node *old, Node *new, int cur_codes, int empty){
	int i = 0;
	int seen = 0;
	int pref = 0;
	int c = 0;
	int new_codes = 257;
	int pastChar = 0;
	int pastPref = 0;
	int parent = 0;
	for(i = 257; i < cur_codes; i++) {
		if(old[i].seen > 1) {
			c = old[i].newChar;
			pref = old[i].pref;
			if(pref <= 255) {
				trieAdd(new, pref, c, new_codes);
				new[new_codes].seen = old[i].seen / 2;
				++new_codes;
			}
			else{
				pastChar = old[pref].newChar;
				pastPref = old[pref].pref;
				parent = binarySearch(new[pastPref].kids, pastChar, 0, new[pastPref].numKids - 1);
				old[i].pref = new[pastPref].kids[parent].code;
				trieAdd(new, old[i].pref, c, new_codes);
				new[new_codes].seen = old[i].seen / 2;
				++new_codes;
			}
		}
	}
	return new_codes;
}
int putString(Node *root, int *fK, int code, FILE *output){
	if(code < 0)
		die ("ERROR: Code not in table");
	if(root[code].pref == 0) {
		*fK = root[code].newChar;
		putc (root[code].newChar, output);
		return 1;
	}
	putString (root, fK, root[code].pref, output);
	putc (root[code].newChar, output);
	return 1;
}
void printTrie(Node *root, int c){
	printf("i,pref[i],char[i],used[i]\n");
	for(int i = 2; i < c; i++) {
		printf("%d,%d,%d,%d\n", i, root[i].pref, root[i].newChar, root[i].seen);
	}
}
void printChildren (kidNode *array, int count)
{
	int i;
	if (array == NULL)
		printf ("ERROR: children array is empty\n");
	for (i = 0; i < count; i++) {
		printf ("%d\t%d\n", array[i].myChar, array[i].code);
	}
}
void trieRemove(Node *root, int index){
}
int binarySearch(kidNode *node, int find, int start, int end){
	if(end < start)
		return -1;
	else{
		int middle = (start + end) / 2;
		if(node[middle].myChar > find)
			return binarySearch(node, find, start, middle-1);
		else if(node[middle].myChar < find)
			return binarySearch(node, find, middle + 1, end);
		else if(node[middle].myChar == find)
			return middle;
		else
			return -1;
	}
}
void putBits (int nBits, int code, FILE *output);
void flushBits (FILE *output);
int getBits (int nBits, FILE *input);
static int nExtra = 0;
static unsigned int extraBits = 0;
void putBits (int nBits, int code, FILE *output)
{
	unsigned int c;
	if (nBits > (sizeof(int)-1) * CHAR_BIT)
		exit (fprintf (stderr, "putBits: nBits = %d too large\n", nBits));
	code &= (1 << nBits) - 1;
	nExtra += nBits;
	extraBits = (extraBits << nBits) | code;
	while (nExtra >= CHAR_BIT) {
		nExtra -= CHAR_BIT;
		c = extraBits >> nExtra;
		putc (c, output);
		extraBits ^= c << nExtra;
	}
}
void flushBits (FILE *output)
{
	if (nExtra != 0)
		putc (extraBits << (CHAR_BIT - nExtra), output);
}
int getBits (int nBits, FILE *input)
{
	int c;
	static int nExtra = 0;
	static int unsigned extra = 0;
	if (nBits > (sizeof(extra)-1) * CHAR_BIT)
		exit (fprintf (stderr, "getBits: nBits = %d too large\n", nBits));
	while (nExtra < nBits) {
		if ((c = getc(input)) == EOF)
			return EOF;
		nExtra += CHAR_BIT;
		extra = (extra << CHAR_BIT) | c;
	}
	nExtra -= nBits;
	c = extra >> nExtra;
	extra ^= c << nExtra;
	return c;
}
#define AUTH1 17
#define AUTH2 29
void encode(FILE *input, FILE *output){
	int empty = 0;
	int maxbits = 12;
	Node *trie = NULL;
	Node *newTrie = NULL;
	int cur_codes = 257;
	int max_codes = 511;
	int cur_bits = 9;
	int target = 0;
	int triecount = 0;
	int c = 0, k = 0;
	createTrie(&trie, cur_bits);
	initTrie(trie, empty);
	while ((k = getc(input)) != EOF) {
		target = binarySearch(trie[c].kids, k, 0, trie[c].numKids - 1);
		if (target <= -1) {
			putBits (cur_bits, c, output);
			trie[c].seen += 1;
			if (max_codes >= cur_codes) {
				trieAdd(trie, c, k, cur_codes);
				cur_codes++;
			}
			if (cur_codes > max_codes && maxbits > cur_bits) {
				putBits(cur_bits, 0, output);
				cur_bits = cur_bits + 1;
				reallocTrie(&trie, cur_bits);
				max_codes = (1 << cur_bits) - 1;
			}
			if(empty) {
				c = searchTrie(trie, trie[k].pref, k);
				if(c == -1) {
					c = 0;
				}
			}
			else
				c = k + 1;
		}
		else if (target >= -1) {
			if (c != 0)
				trie[c].seen += 1;
			c = trie[c].kids[target].code;
		}
	}
	if(c != 0) {
		putBits(cur_bits, c, output);
		trie[c].seen = trie[c].seen + 1;
		destroyTrie(trie, cur_codes);
		flushBits(output);
	}
	return;
}
int main(int argc, char **argv){
	int i;
	FILE *input, *output;
	if (argc < 3)
	{
		printf("Usage: lzwkoder <input_file> <outpu_file>");
		return -1;
	}
	if ( !(input = fopen(argv[1], "rb")) )
	{
		printf("Can't open %s/n", argv[1]);
		return -2;
	}
	if ( !(output = fopen(argv[2], "wb+")) )
	{
		printf("Can't open %s/n", argv[2]);
		return -3;
	}
	encode(input, output);
	return 0;
}
