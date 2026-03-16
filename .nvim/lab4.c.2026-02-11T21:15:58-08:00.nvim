#define _DEFAULT_SOURCE
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BUF_SIZE 256
#define handle_error(msg)                                                      \
  do {                                                                         \
    perror(msg);                                                               \
    exit(EXIT_FAILURE);                                                        \
  } while (0)

struct header {
  uint64_t size;
  struct header *next;
};

void print_out(char *format, void *data, size_t data_size) {
  char buf[BUF_SIZE];
  ssize_t len;
  if (data_size == sizeof(uint64_t)) {
    len = snprintf(buf, BUF_SIZE, format, *(uint64_t *)data);
  } else {
    len = snprintf(buf, BUF_SIZE, format, *(void **)data);
  }
  if (len < 0) {
    perror("snprintf");
    exit(EXIT_FAILURE);
  }
  write(STDOUT_FILENO, buf, len);
}

int main() {
  void *pbreak = sbrk(256);
  if (pbreak == (void *)-1) {
    perror("Failed to allocate memory with sbrk.\n");
    exit(1);
  }

  struct header *first_block_header = (struct header *)pbreak;
  struct header *second_block_header = (struct header *)((char *)pbreak + 128);

  first_block_header->size = 128;
  first_block_header->next = NULL;

  second_block_header->size = 128;
  second_block_header->next = first_block_header;

  unsigned char *first_data = (unsigned char *)(first_block_header + 1);
  memset(first_data, 0, 128 - sizeof(struct header));

  unsigned char *second_data = (unsigned char *)(second_block_header + 1);
  memset(second_data, 1, 128 - sizeof(struct header));

  print_out("first block:       %p\n", &first_block_header, sizeof(void *));
  print_out("second block:      %p\n", &second_block_header, sizeof(void *));
  print_out("first block size:  %lu\n", &first_block_header->size,
            sizeof(uint64_t));
  print_out("first block next:  %p\n", &first_block_header->next,
            sizeof(void *));
  print_out("second block size: %lu\n", &second_block_header->size,
            sizeof(uint64_t));
  print_out("second block next: %p\n", &second_block_header->next,
            sizeof(void *));

  for (size_t i = 0; i < 128 - sizeof(struct header); i++) {
    char buf[10];
    ssize_t len = snprintf(buf, 10, "%d\n", first_data[i]);
    write(STDOUT_FILENO, buf, len);
  }

  for (size_t i = 0; i < 128 - sizeof(struct header); i++) {
    char buf[10];
    ssize_t len = snprintf(buf, 10, "%d\n", second_data[i]);
    write(STDOUT_FILENO, buf, len);
  }

  return 0;
}
