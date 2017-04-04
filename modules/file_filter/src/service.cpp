#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "gsystem.h"

int
main (int argc, char *argv[])
{
  struct TStack filter;
  char *mf = NULL;		/* Memmory file */

  bzero (&filter, sizeof (filter));
  push ("image_filter", &filter);

  /*
   * int len = load_file(&mf);
   */

  int rv = pass_any (&filter);
  clear (&filter);

  return !rv;
}
