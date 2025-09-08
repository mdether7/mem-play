#ifndef MEM_CHUNK_H
#define MEM_CHUNK_H

#include <stddef.h>

// typedef struct memory_chunk_s memory_chunk; (good for opaque data types)

typedef enum {
  TYPE_CHAR,
  TYPE_SHORT,
  TYPE_INT,
  TYPE_FLOAT,
  TYPE_DOUBLE,
  NUM_DATA_TYPES,
} data_type_t;

typedef struct memory_chunk_s {

  void*        first_byte;

  size_t       size;

  data_type_t  type;

  size_t       element_count;

} memory_chunk;

extern size_t TYPE_SIZES[NUM_DATA_TYPES];

memory_chunk* chunk_create(data_type_t type, size_t element_count);
void chunk_destroy(memory_chunk* chunk);

#endif