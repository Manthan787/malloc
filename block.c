#include "block.h"
#include <stdio.h>
#include <stdlib.h>

Block* new_block(void* addr) {
  Block* b = (Block*)addr;
  b->startAddr = addr;
  b->size = 0;
  b->next = NULL;
  b->previous = NULL;
  b->status = FREE;
  return b;
}

Block* mark_block(Block* b, size_t totalSize) {
  Block* freeblock = b->startAddr;
  freeblock->size = totalSize;
  freeblock->status = USED;
  return freeblock;
}

void print_block(Block* b, int level) {
  if (b != NULL) {
    printf("----- Block Information (%d)-----\n", level);
    printf("\taddr: %p\n", b->startAddr);
    printf("\tsize: %zu\n", b->size);
    printf("\tstatus: %d\n", b->status);
    printf("\tNext: %p\n", b->next);
    printf("\tPrevious: %p\n", b->previous);
    printf("------------------------------\n");
  }
}