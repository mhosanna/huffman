#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "huffman.h"


unsigned long frequency[255];

int queueLength = 0;

struct QueueNode *pool[256];

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
  unsigned long totalChars = 0;

  totalChars = countFrequency(in);
  int i, j;
  int index = 0;
  for (i = 0; i < 255; i++)
  {
  	if(frequency[i])
  	{
  	  struct QueueNode *n = createNodes(frequency, i);	
  	  pool[index] = n;
  	  queueLength++;
  	  index++;
  	}
  }

  BuildTree();

  char *prefix = (char *)calloc(1, sizeof(char));
  traverseTree(*pool, prefix);

  freeList(*pool);
}

void traverseTree(struct QueueNode *pool, char *prefix)
{
  if(!pool->left && !pool->right)
  {
    if(pool->symbol < 33 || pool->symbol > 126)
    {
      printf("=%d \t %s \n" , pool->symbol, prefix);
    }
    else printf("%c \t %s \n", pool->symbol, prefix); 
  }
  else
  {
    if(pool->left)
    {
      traverseTree(pool->left, Concat(prefix, '0'));
    }
    if(pool->right)
    {
      traverseTree(pool->right, Concat(prefix, '1'));
    }
    free(prefix);
  }
}
char *Concat(char *prefix, char letter)
{
    char *result = (char *)malloc(strlen(prefix) + 2);
    sprintf(result, "%s%c", prefix, letter);
    return result;
}

void BuildTree()
{
  int length = queueLength;
  int i, j;

  while(length > 1)
  {
    qsort(pool, queueLength, sizeof(struct QueueNode *), SortFunc);

    struct QueueNode *node = malloc(sizeof(struct QueueNode));
    struct QueueNode** n = pop(pool, 0);
    struct QueueNode** m = pop(pool, 1); 
    node->left = (*n);
    node->right = (*m); 
    node->symbol = node->left->symbol;
    node->frequency = ((node->right->frequency)+(node->left->frequency));

    pool[0]= node;
    queueLength--;
    length--;

    for(i = 1; i <= queueLength; i++)
    {
      pool[i]=pool[i+1];
    } 
  }
}

void Sort(struct QueueNode pool[])
{
  qsort(pool, queueLength, sizeof(struct QueueNode), SortFunc);
}

int SortFunc(const void* a, const void* b)
{
  const struct QueueNode **first = (const struct QueueNode**)a;
  const struct QueueNode **second = (const struct QueueNode**)b;

  if((*first)->frequency < (*second)->frequency)
  {
    return -1;
  }
  else if((*first)->frequency > (*second)->frequency)
  {
    return +1;
  }
  else if((*first)->symbol < (*second)->symbol)
  {
    return +1;
  }
  else if((*first)->symbol > (*second)->symbol)
  {
    return -1;
  }
  else return 0;
}


struct QueueNode** pop(struct QueueNode** headRef, int i)
{
  struct QueueNode* temp = (*headRef)->right;
  struct QueueNode** popped = &headRef[i];
  (*popped)->frequency = headRef[i]->frequency;

  // free(*headRef);
  // *headRef = temp;

  return popped;

}
struct QueueNode* createNodes(unsigned long *frequency, int i)
{
  struct QueueNode *node = malloc(sizeof(struct QueueNode));
  node->symbol = i;
  node->frequency = frequency[i];
  node->right = NULL;
  node->left = NULL;

  return node;
}

/* Count the frequency of symbols in a stream */
unsigned long countFrequency(FILE* in)
{
  char c;

  unsigned long i;
  unsigned long count = 0;

  for (i = 0; i < 256; i++)
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
  printTable(frequency, count);
  return count;
}

void printTable(unsigned long *frequency, unsigned long count)
{
  int j;

  printf("Symbol\tFreq\n");

  for (j = 0; j < 256; j++)
  {
	if(frequency[j])
	{
	  if(j < 33 || j > 126)
	  {
		printf("=%d \t %lu \n" , j, frequency[j] );
	  }
	  else printf("%c \t %lu \n", j, frequency[j]);	
	}
		
  }
  printf("Total chars = %lu\n", count);
}

void freeList(struct QueueNode* head)
{
  struct QueueNode* current = head;
  struct QueueNode* temp;
  while (current != NULL)
  {
    temp = current;
  	current = current->right;
  	free(temp);
  }
  head = NULL;
}

/***************************************************/
/* Decode a Huffman encoded file.                  */
/* in -- File to decode.                           */
/* out -- File where decoded data will be written. */
/***************************************************/
void decodeFile(FILE* in, FILE* out);