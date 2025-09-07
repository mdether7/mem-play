#include "mem_chunk.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

static void print_raw_bytes(memory_chunk* chunk);

int main(void)
{
  memory_chunk* chunk = chunk_create(TYPE_INT, 1);

  if (chunk == NULL) {
    fprintf(stderr, "Chunk memory allocation failed!\n");
    exit(1);
  }

  for (size_t i = 0; i < chunk->element_count; i++) {
    ((int*)chunk->first_byte)[i] = 16843009;
  }

  print_raw_bytes(chunk);

  chunk_destroy(chunk);
  chunk = NULL;

  return 0;
}

static void print_raw_bytes(memory_chunk* chunk)
{
  if (chunk == NULL) {
    assert(0 && "Chunk should not be NULL!");
    return;
  }

  unsigned char *p = (unsigned char*)chunk->first_byte;

  for (size_t i = 0; i < chunk->size; i++) {
    printf("BYTE[%zu] at ADDRESS[%p] with VALUE[0x%02x]\n", 
           i, (p + i), p[i]);
  }
}