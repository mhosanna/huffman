#include <stdio.h>
#include "huffman.h"

/**************************************************************/
/* Huffman encode a file.                                     */
/* in -- File to encode.                                      */
/*       May be binary, so don't assume printable characters. */
/* out -- File where encoded data will be written.            */
/* printTable -- If not zero, print table of bytes,           */
/*               frequencies, and codes to standard output.   */
/**************************************************************/
void encodeFile(FILE* in, FILE* out, int printTable)
{
	countFrequency(in);
}

/***************************************************/
/* Decode a Huffman encoded file.                  */
/* in -- File to decode.                           */
/* out -- File where decoded data will be written. */
/***************************************************/
void decodeFile(FILE* in, FILE* out);

/* Count the frequency of symbols in a stream */
void countFrequency(FILE* in)
{
	unsigned long frequency[255];
	char c;
	int i, j;
	unsigned long count = 0;
	for (i = 0; i < 255; i++)
	{
		frequency[i] = 0;
	}

	c = getc(in);
	while (c != EOF)
	{
		frequency[c]++; 
		c = getc(in);
		count++;
	}

	for (j = 0; j < 255; j++)
	{
		printf("%c:%lu \n", j, frequency[j]);
	}
	printf("COUNT: %lu\n", count);
}