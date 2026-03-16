#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *buff = NULL;
  size_t size = 0;

  while (1) {
    printf("Please enter some text!\n");

    // getline returns the total number of characters in the input string
    ssize_t n = getline(&buff, &size, stdin);
    if (n == -1) {
      perror("getline failed!");
      exit(EXIT_FAILURE);
    }

    // first call to strtok_r passes the string as the argument, and subsequent
    // calls pass null
    char *saveptr;
    char *token = strtok_r(buff, " ", &saveptr);
    while (token != NULL) {
      printf("%s\n", token);
      token = strtok_r(NULL, " ", &saveptr);
    }
  }

  free(buff);
  exit(EXIT_SUCCESS);
}
