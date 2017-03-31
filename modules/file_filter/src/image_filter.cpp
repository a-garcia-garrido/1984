#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFF 0x4000

const char *filter_name = "image_filter";
const char *filter_desc = "image filetype filter";

bool
filter_passes ()
{
  char buffer[MAX_BUFF];
  FILE *pc = popen ("file - | grep \"image data\" > /dev/null", "w");
  int rv = 0;

  while (fgets (buffer, MAX_BUFF, stdin))
    {
      fprintf (pc, "%s", buffer);
    }

  rv = !pclose (pc);

#ifndef NDEBUG
  fprintf(stderr, "%s: %i\n", filter_name, rv);
#endif

  return rv;
}
