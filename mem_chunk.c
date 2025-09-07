#include "mem_chunk.h"

#include <stdlib.h>
#include <string.h>
#include <assert.h>

static const size_t MAX_ELEMENTS = 100;

static size_t TYPE_SIZES[NUM_DATA_TYPES] = 
{
  [TYPE_CHAR] = sizeof(char),
  [TYPE_SHORT] = sizeof(short),
  [TYPE_INT] = sizeof(int),
  [TYPE_FLOAT] = sizeof(float),
  [TYPE_DOUBLE] = sizeof(double),
};

memory_chunk* chunk_create(data_type_t type, size_t element_count)
{
  assert(element_count > 0 && element_count <= MAX_ELEMENTS);
  assert(type >= 0 && type < NUM_DATA_TYPES);
  
  if (element_count == 0 || element_count > MAX_ELEMENTS) {
    return NULL;
  }

  if (type < 0 || type >= NUM_DATA_TYPES) {
    return NULL;
  }

  memory_chunk* chunk = malloc(sizeof(*chunk));

  if (chunk == NULL) {
    return NULL;
  }

  size_t element_size = TYPE_SIZES[type];

  chunk->first_byte = calloc(element_count, element_size);

  if (chunk->first_byte == NULL) {
    free(chunk);
    return NULL;
  }

  chunk->size =           element_size * element_count;
  chunk->element_count =  element_count;
  chunk->type =           type;

  return chunk;
}

void chunk_destroy(memory_chunk* chunk)
{
  if (chunk != NULL) {
    free(chunk->first_byte);
    free(chunk);
  }
}