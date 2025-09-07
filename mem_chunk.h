#ifndef MEM_CHUNK_H
#define MEM_CHUNK_H

#include <stddef.h>

// typedef struct memory_chunk_s memory_chunk;

typedef struct memory_chunk_s {

  unsigned char* first_byte;

  size_t size;

} memory_chunk;

memory_chunk* create_chunk(size_t size);
void destroy_chunk(memory_chunk* chunk);

#endif