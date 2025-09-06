#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEMORY_SIZE 20

typedef struct memory_chunk_s {

  unsigned char* first_byte;

  size_t size;

} memory_chunk;


int main(void)
{
  malloc(MEMORY_SIZE);
  return 0;
}
