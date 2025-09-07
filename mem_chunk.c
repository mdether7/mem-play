#include "mem_chunk.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

memory_chunk* create_chunk(size_t size)
{
  memory_chunk* chunk = malloc(sizeof(*chunk));
  
  if (chunk == NULL) {
    return NULL;
  }

  unsigned char* first_byte = malloc(size);
  if (first_byte == NULL) {
    free(chunk);
    return NULL;
  }

  memset(first_byte, 255, size);

  chunk->first_byte= first_byte;
  chunk->size = size;

  return chunk;
}

void destroy_chunk(memory_chunk* chunk)
{
  if (chunk != NULL) {
    free(chunk->first_byte);
    free(chunk);
  }
}