#include <stdio.h>
#include <stdlib.h>

#include "detector.h"

int main(int argc, char const *argv[]) {
  char * filename;

  printf("0\n");
  filename = detector();
  printf("6\n");
  printf("%s\n", filename);

  return EXIT_SUCCESS;
}
