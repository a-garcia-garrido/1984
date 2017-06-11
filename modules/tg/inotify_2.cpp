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

int
main(int argc, char *argv[])
{
  int inotifyFd, wd;
  //int j;
  char buf[BUF_LEN] __attribute__ ((aligned(8)));
  ssize_t numRead;
  char *p;
  struct inotify_event *event;

  

  inotifyFd = inotify_init();                 /* Create inotify instance */
  if (inotifyFd == -1){
    fprintf(stderr, "inotify init failure\n");
    abort();
  }

  /* For each command-line argument, add a watch for all events */
  
  wd = inotify_add_watch(inotifyFd, "/home/tester/1984/modules/recognition/src/lee", IN_MODIFY);
  if (wd == -1){
    fprintf(stderr, "inotify watch failure\n");
    abort();
  }

 

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
          if(event->mask & IN_MODIFY){
            printf("New file %s moved.\n", event->name);
            system("gcc -o lector lector.cpp");
	    system("./lector"); 
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
