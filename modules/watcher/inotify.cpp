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

bool filter_image(char *name){

}

bool filter_video(char * name){

}

void filter_pass(char *name){

  bool pass = false;
  char *pathnew = "test/";
  char *pathold = "wached/";
  strcat(pathold, name);
  strcat(pathnew, name);
  const char *oldname = pathold;
  const char *newname = pathnew;

  if(filter_image(name)){
    int rename(const char *oldname, const char *newname);
    pass = true;
  }
  if(filter_video(name)){
    int rename(const char *oldname, const char *newname);
    pass = true;
  }
  if((pass = false)){
    int remove(const char *oldname);
  }
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
     wd = inotify_add_watch(inotifyFd, "./watcher/watched", IN_CREATE);
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

     exit(EXIT_SUCCESS);
 }
