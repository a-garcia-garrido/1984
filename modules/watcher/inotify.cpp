#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

int main( int argc, char **argv )
{
  int length, i = 0;
  int fd;
  int wd;
  char buffer[BUF_LEN];
  char *pathname;

  fd = inotify_init();

  if ( fd < 0 ) {
    perror( "inotify_init" );
  }

  wd = inotify_add_watch( fd, "/home/victor/work/1984/modules/watcher/watched",
                         IN_CREATE);
  length = read( fd, buffer, BUF_LEN );

  if ( length < 0 ) {
    perror( "read" );
  }

  while ( i < length ) {
    struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
    if ( event->len ) {
      if ( event->mask & IN_CREATE ) {
          printf( "The file %s was created.\n", event->name );
        }
      }
    i += EVENT_SIZE + event->len;
  }

  inotify_rm_watch( fd, wd );
  close( fd );

  return EXIT_SUCCESS;
}
