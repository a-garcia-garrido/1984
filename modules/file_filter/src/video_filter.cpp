#include "image_filter.h"

#ifndef NDEBUG
void
on_load()
{
    fprintf(stderr, "%s loaded.\n", filter_name);
}

void
on_unload()
{
    fprintf(stderr, "%s unloaded.\n", filter_name);
}
#endif

bool
filter_passes ()
{
  char buffer[MAX_BUFF];
  FILE *pc = popen ("file - | grep \"video data\" > /dev/null", "w");
  int rv = 0;

  while (fgets (buffer, MAX_BUFF, stdin))
    {
      fprintf (pc, "%s", buffer);
    }

  rv = !pclose (pc);

#ifndef NDEBUG
  fprintf (stderr, "%s: %i\n", filter_name, rv);
#endif

  return rv;
}
