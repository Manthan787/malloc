#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include "freelist.h"
#include "block.h"
#include "config.h"

void print_blocklist(Block** blocks, int length) {
  assert(length > 0);
  int i;
  for (i = 0; i < length; i++) {
    printf("Level %d\n", i);
    Block* b = blocks[i];
    while (b != NULL) {
      print_block(b);
      b = b->next;
    }
  }
}

/**
 * Partition blocks until memory request for given `order` can
 * be satisfied.
 * For example, if a memory request for order 8 (2048 bytes) is requested
 * a single order 9 block (4096 bytes) is partitioned.
 */
void partition_blocks(Block** blocks, int order) {
  int split = MAX_INDEX + 1;
  printf("Start split at %d\n", split);
  while(blocks[order] == NULL && split > MIN_INDEX) {
    split--;
    if(blocks[split] == NULL) continue;
    int newsplit = split - 1;
    if(blocks[newsplit] == NULL) {
      printf("splitting %p into two\n", blocks[split]->startAddr);
      void *addr = blocks[split]->startAddr;
      blocks[split] = blocks[split]->next;
      Block *block1 = new_block(addr);
      Block *block2 = new_block(addr + (int)pow(2, newsplit + MIN_ORDER));
      block1->level = newsplit;
      block2->level = newsplit;
      block1->next = block2->startAddr;
      block2->previous = block1->startAddr;
      if(blocks[split] != NULL) blocks[split]->previous = block2->startAddr;
      blocks[newsplit] = block1;
    }
  }
}