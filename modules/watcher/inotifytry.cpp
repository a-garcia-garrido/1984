#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <limits.h>

using namespace std;

#define EVENT_SIZE  ( sizeof (struct inotify_event) )
#define BUF_LEN     ( 1024 * ( EVENT_SIZE + 16 ) )
#define MAX 0x1000

void filter_pass(char *name){
  const char *before = "file test/";
  const char *after = " | grep \"image data\" > /dev/null";
  char *command;

  if((command = (char*)malloc(strlen(before)+strlen(after)+strlen(name)+1)) != NULL){
    command[0] = '\0';
    strcat(command, before);
    strcat(command, name);
    strcat(command, after);
    strcat(command, "\0");
  } else {
    fprintf(stderr,"malloc newname failed!\n");
  }
  printf("%s\n", command);
}

int
main(int argc, char *argv[])
{
  int inotifyFd, wd;
  //int j;
  char buf[BUF_LEN] __attribute__ ((aligned(8)));
  ssize_t numRead;
  char *p;
  struct inotify_event *event;

  //if (argc < 2 || strcmp(argv[1], "--help") == 0){
  //fprintf(stderr, "%s pathname...\n", argv[0]);
  //exit(1);
  //}

  inotifyFd = inotify_init();                 /* Create inotify instance */
  if (inotifyFd == -1){
    fprintf(stderr, "inotify init failure\n");
    abort();
  }

  /* For each command-line argument, add a watch for all events */
  //for (j = 1; j < argc; j++) {
  wd = inotify_add_watch(inotifyFd, "./watched", IN_CREATE);
  if (wd == -1){
    fprintf(stderr, "inotify watch failure\n");
    abort();
  }

  //printf("Watching %s using wd %d\n", argv[j], wd);
  //}

  while(1){                                  /* Read events forever */
    numRead = read(inotifyFd, buf, BUF_LEN);

    if (numRead == -1){
      fprintf(stderr, "read failure\n");
      abort();
    }
    else
    {
      for(p = buf; p < buf + numRead;){
        event = (struct inotify_event *) p;
        if(event->len){
          if(event->mask & IN_CREATE){
            printf("New directory %s created.\n", event->name);
            filter_pass(event->name);
          }
          p += sizeof(struct inotify_event) + event->len;
        }
      }
    }
  }

  inotify_rm_watch( inotifyFd, wd );
  close(inotifyFd);

  return EXIT_SUCCESS;
}
