#define _POSIX_C_SOURCE 200809
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *hist[5] = {0};
  char *line = NULL;
  size_t n = 0, c = 0;

  for (;;) {
    printf("Enter input: ");
    fflush(stdout);

    if (getline(&line, &n, stdin) < 0) {
      break;
    }

    free(hist[c % 5]);
    hist[c % 5] = strdup(line);
    c++;

    if (!strcmp(line, "print\n") || !strcmp(line, "print")) {
      size_t start = (c > 5) ? (c - 5) : 0;
      for (size_t k = start; k < c; k++) {
        printf("%s", hist[k % 5]);
      }
    }
  }

  free(line);
  for (int i = 0; i < 5; i++) {
    free(hist[i]);
  }

  return 0;
}
