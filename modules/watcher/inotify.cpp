#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>
#include <iostream>

#include "detector.h"

using namespace std;

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )

char *detector()
{
  int length, i = 0;
  int fd;
  int wd;
  char buffer[BUF_LEN];
  struct inotify_event *event;
  char *name = NULL;

  fd = inotify_init();

  if (fd < 0){
    perror("inotify_init");
  }

  wd = inotify_add_watch(fd, "/home/victor/work/1984/modules/watcher/watched",
                         IN_CREATE);
  length = read(fd, buffer, BUF_LEN);

  if (length < 0) {
    perror("read");
  }

  while (i < length) {
    inotify_event *event = (struct inotify_event *) &buffer[i];
    if (event->len) {
      if (event->mask & IN_CREATE) {
          printf("The file %s was created.\n", event->name);
          printf("1\n");
          name = event->name;
        }
      }
      printf("2\n");
    i += EVENT_SIZE + event->len;
  }

  printf("3\n");
  inotify_rm_watch( fd, wd );
  printf("4\n");
  close( fd );
  printf("5\n");

  return name;
}
