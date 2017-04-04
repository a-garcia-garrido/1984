#include "filter.h"

bool
pass_one (void *filter)
{
  bool (*fn) ();
  //fn = (bool (*)())dlsym (filter, "filter_passes");
  *(void **) (&fn) = dlsym (filter, "filter_passes");  // Adapt the previous line to ISO C

  if (!fn)
    prerror ("Couldn't pass filter.\n");

  return (*fn) ();
}
