#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF 0x4000

int main(int argc, char const *argv[]) {
  char buffer[MAX_BUFF];
  FILE *pc = popen ("file - | grep \"image data\" > /dev/null", "w");
  int rv = 0;

  while (fgets (buffer, MAX_BUFF, stdin))
    {
      fprintf (pc, "%s", buffer);
    }

  rv = !pclose (pc);

  return 0;
}
