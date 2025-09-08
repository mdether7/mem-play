#include "mem_chunk.h"

#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <assert.h>

static char* TYPE_NAMES[NUM_DATA_TYPES] = 
{
  [TYPE_CHAR] = "CHAR",
  [TYPE_SHORT] = "SHORT",
  [TYPE_INT] = "INT",
  [TYPE_FLOAT] = "FLOAT",
  [TYPE_DOUBLE] = "DOUBLE",
};

static void print_raw_bytes(memory_chunk* chunk);

int main(void)
{
  setlocale(LC_ALL, "");

  memory_chunk* chunk = chunk_create(TYPE_DOUBLE, 1);

  if (chunk == NULL) {
    fprintf(stderr, "Chunk memory allocation failed!\n");
    exit(1);
  }

  memset(chunk->first_byte, -1, sizeof(double));

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

  printf("[Chunk stores: %s | (sizeof(%s) == %zu)]\n",
    TYPE_NAMES[chunk->type], TYPE_NAMES[chunk->type], TYPE_SIZES[chunk->type]);

  unsigned char *p = (unsigned char*)chunk->first_byte; // conversion for raw byte iteration.

  for (size_t i = 0; i < chunk->size; i++) {
    printf("BYTE[%zu] at ADDRESS[%p] with VALUE[0x%02x]\n", 
           i, (p + i), p[i]);
  }
}
