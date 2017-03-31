#include "gsystem.h"

void prerror(const char *mssg, const char *origin){
    fprintf(stderr, "%s: %s\n", mssg, origin);
    exit(1);
}

int load_file(char **mf){
  char buffer[MAX_BUFFER];
  int total_len = 0, read_len = 0;

  while (read_len = fread(buffer, sizeof(char), MAX_BUFFER, stdin)){
      total_len += read_len;
      *mf = (char *) realloc(*mf, total_len);
      memcpy(*mf + total_len - read_len, buffer, read_len);
  }

  return total_len;
}
