#include "mem_chunk.h"

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define MEMORY_SIZE 30

void print_raw_bytes(memory_chunk* chunk);

int main(void)
{
  memory_chunk* chunk = create_chunk(MEMORY_SIZE);

  if (chunk == NULL) {
    fprintf(stderr, "Chunk memory allocation failed!\n");
    exit(1);
  }

  print_raw_bytes(chunk);

  destroy_chunk(chunk);
  chunk = NULL;

  return 0;
}

// cmemory_chunk* chusnk = create_chunk(100);

// printf("Pointer value: %p\n", (void*)chunk->first_byte);
// printf("Pointer as number: %lu\n", (unsigned long)chunk->first_byte);
// printf("Last byte of pointer: %u\n", (unsigned long)chunk->first_byte & 0xFF);

// unsigned char* f = (unsigned char*)chunk;
// printf("*f (first byte of struct): %u\n", *f);

// // Compare with actual data:
// printf("First byte of data: %u\n", chunk->first_byte[0]);  // This should be 0

void print_raw_bytes(memory_chunk* chunk)
{
  if (chunk == NULL) {
    assert(0 && "Chunk shoudl not be NULL!");
    return;
  }

  for (size_t i = 0; i < chunk->size; i++) {
    printf("data[%zu]: 0x%02x\n", i, chunk->first_byte[i]);
  }
}