#include "gsystem.h"

char *
get_self_executable_dir ()
{
    int rval;
    char *last_slash;
    char link_target[MAX_FN];
    size_t result_length;
    char *result;

    rval = readlink ("/proc/self/exe", link_target, sizeof(link_target) - 1);
    if (rval == -1)
        perror("Couldn't resolve executable self name.\n");
    else
        link_target[rval] = '\0';

    last_slash = strrchr(link_target, '/');
    if (last_slash == NULL || last_slash == link_target)
        perror("Couldn't resolve executable self name.\n");
    result_length = last_slash - link_target; 

    result = (char *) malloc (result_length + 1);
    strncpy (result, link_target, result_length);

}

void
prerror (const char *mssg, ...)
{
  va_list args;
  va_start (args, mssg);
  char format = 0;
  bool formatting = false;
  int arg_int = 0;
  const char *arg_str = NULL;

  while (*mssg != '\0')
    {
      if (*mssg == '%')
	formatting = true;
      if (formatting)
	{
	  format = tolower (*(++mssg));
	  switch (format)
	    {
	    case 's':
	      arg_str = va_arg (args, const char *);
	      fprintf (stderr, "%s", arg_str);
	      break;
	    case 'i':
	      arg_int = va_arg (args, int);
	      fprintf (stderr, "%i", arg_int);
	      break;
	    }
	}
      else
	fprintf (stderr, "%c", *mssg++);

      formatting = false;
    }
  va_end (args);
  exit (1);
}

int
load_file (char **mf)
{
  char buffer[MAX_BUFFER];
  int total_len = 0, read_len = 0;

  while (read_len = fread (buffer, sizeof (char), MAX_BUFFER, stdin))
    {
      total_len += read_len;
      *mf = (char *) realloc (*mf, total_len);
      memcpy (*mf + total_len - read_len, buffer, read_len);
    }

  return total_len;
}
