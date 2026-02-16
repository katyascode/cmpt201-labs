#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

struct header {
  uint64_t size;
  struct header *next;
  int id;
};

void initialize_block(struct header *block, uint64_t size, struct header *next,
                      int id) {
  block->size = size;
  block->next = next;
  block->id = id;
}

int find_first_fit(struct header *free_list_ptr, uint64_t size) {
	struct header *current = free_list_ptr;
  while (current != NULL) {
    if (current->size >= size) {
      return current->id;
    }
    current = current->next;
  }
  return -1;
}

int find_best_fit(struct header *free_list_ptr, uint64_t size) {
  int best_fit_id = -1;
  uint64_t best_size = UINT64_MAX;
  struct header *current = free_list_ptr;
  while (current != NULL) {
    if (current->size >= size && current->size < best_size) {
      best_size = current->size;
      best_fit_id = current->id;
    }
    current = current->next;
  }
  return best_fit_id;
}

int find_worst_fit(struct header *free_list_ptr, uint64_t size) {
  int worst_fit_id = -1;
  uint64_t worst_size = 0;
  struct header *current = free_list_ptr;
  while (current != NULL) {
    if (current->size >= size && current->size > worst_size) {
      worst_size = current->size;
      worst_fit_id = current->id;
    }
    current = current->next;
  }
  return worst_fit_id;
}

int main(void) {

  struct header *free_block1 = (struct header*) malloc(sizeof(struct header));
  struct header *free_block2 = (struct header*) malloc(sizeof(struct header));
  struct header *free_block3 = (struct header*) malloc(sizeof(struct header));
  struct header *free_block4 = (struct header*) malloc(sizeof(struct header));
  struct header *free_block5 = (struct header*) malloc(sizeof(struct header));

  initialize_block(free_block1, 6, free_block2, 1);
  initialize_block(free_block2, 12, free_block3, 2);
  initialize_block(free_block3, 24, free_block4, 3);
  initialize_block(free_block4, 8, free_block5, 4);
  initialize_block(free_block5, 4, NULL, 5);

  struct header *free_list_ptr = free_block1;

  int first_fit_id = find_first_fit(free_list_ptr, 7);
  int best_fit_id = find_best_fit(free_list_ptr, 7);
  int worst_fit_id = find_worst_fit(free_list_ptr, 7);

  printf("First Fit ID: %d\n", first_fit_id);
	printf("Best Fit ID: %d\n", best_fit_id);			
	printf("Worst Fit ID: %d\n", worst_fit_id);

  return 0;
}

/*

COALESCE(freed_block):
      before = NULL
      after = NULL

      FOR each block in free list:
          IF block ends where freed_block starts:
              before = block
          IF freed_block ends where block starts:
              after = block

      IF before AND after:
          before.size += freed_block.size + after.size
          remove after from free list

      ELSE IF before:
          before.size += freed_block.size

      ELSE IF after:
          after.start = freed_block.start
          after.size += freed_block.size

      ELSE:
          add freed_block to free list

*/