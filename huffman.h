#ifndef HUFFMAN_H
#define HUFFMAN_H

struct QueueNode
{
	int symbol;
	unsigned long frequency;
	struct QueueNode* right;
	struct QueueNode* left;
};


/* The following 2 functions are used in my huffencode and huffdecode
   programs. You'll need to write them if you want to use my code.  */

/**************************************************************/
/* Huffman encode a file.                                     */
/* in -- File to encode.                                      */
/*       May be binary, so don't assume printable characters. */
/* out -- File where encoded data will be written.            */
/* printTable -- If not zero, print table of bytes,           */
/*               frequencies, and codes to standard output.   */
/**************************************************************/
void encodeFile(FILE* in, FILE* out, int printTable);

/***************************************************/
/* Decode a Huffman encoded file.                  */
/* in -- File to decode.                           */
/* out -- File where decoded data will be written. */
/***************************************************/
void decodeFile(FILE* in, FILE* out);

int SortFunc(const void* a, const void* b);

int compare(struct QueueNode *head, struct QueueNode *node);

void Sort(struct QueueNode pool[]);

void BuildTree();

void traverseTree(struct QueueNode *pool, char *prefix);

char *Concat(char *prefix, char letter);

/* Count the frequency of symbols in a stream */
unsigned long countFrequency(FILE* in);

struct QueueNode* createNodes(unsigned long *frequency, int i);

struct QueueNode** pop(struct QueueNode** headRef, int i);

void refillArray();

/* Print list data on single line, separated with spaces. */
void printList(struct QueueNode* queue);

void printTable(unsigned long *frequency, unsigned long count);

void freeList(struct QueueNode* head);

#endif
