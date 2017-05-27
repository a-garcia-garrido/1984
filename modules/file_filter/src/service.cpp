#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "gsystem.h"

int
main (int argc, char *argv[])
{
  struct TStack filter; //structura de la pila
  char *mf = NULL; /* Memmory file */

  push ("image_filter", &filter);//añadir un filtro a la pila

  /*
   * int len = load_file(&mf);
  */

  int rv = pass_any(&filter);// meter el
  clear(&filter);

  return rv;
}
