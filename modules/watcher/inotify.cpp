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

bool filter_image(char *name){
  const char *before = "file /var/www/html/login_register/images/";
  const char *after = " | grep \"image data\"";
  char *command;
  int rv = 0;

  if((command = (char*)malloc(strlen(before)+strlen(after)+strlen(name)+1)) != NULL){
    command[0] = '\0';
    strcat(command, before);
    strcat(command, name);
    strcat(command, after);
    strcat(command, "\0");
  } else {
    fprintf(stderr,"malloc newname failed!\n");
  }

  FILE *pc = popen (command, "w");

  rv = pclose(pc);

  //printf("%i\n", rv);

  free(command);

  if (rv == 0) {
    return true;
  }

  return false;
}

bool filter_video(char * name){
  const char *before = "file /var/www/html/login_register/images/";
  const char *after = " | grep \"ISO Media\" > /dev/null";
  char *command;
  int rv = 0;

  if((command = (char*)malloc(strlen(before)+strlen(after)+strlen(name)+1)) != NULL){
    command[0] = '\0';
    strcat(command, before);
    strcat(command, name);
    strcat(command, after);
    strcat(command, "\0");
  } else {
    fprintf(stderr,"malloc newname failed!\n");
  }

  FILE *pc = popen (command, "w");

  rv = pclose(pc);

  //printf("%i\n", rv);
  free(command);

  if (rv == 0) {
    return true;
  }

  return false;
}

void filter_pass(char *name){

  bool pass = false;
  const char *newdir = "/var/www/html/login_register/final/";
  const char *olddir = "/var/www/html/login_register/images/";
  char *newname;
  char *oldname;

  printf("try filter image\n");
  if(filter_image(name) == true){
    if((newname = (char*)malloc(strlen(newdir)+strlen(name)+1)) != NULL){
      newname[0] = '\0';
      strcat(newname, newdir);
      strcat(newname, name);
      strcat(newname, "\0");
    } else {
      fprintf(stderr,"malloc newname failed!\n");
    }

    if((oldname = (char*)malloc(strlen(olddir)+strlen(name)+1)) != NULL){
      oldname[0] = '\0';
      strcat(oldname, olddir);
      strcat(oldname, name);
    } else {
      fprintf(stderr,"malloc oldname failed!\n");
    }
    rename(oldname, newname);
    printf("renamed\n");
    pass = true;
  }
  printf("try filter video\n");
  if(filter_video(name)){
    const char *before = "ffmpeg -i ";
    const char *after = " -r 2 -ss 00:00:00 ";
    const char *extension = "-%3d.png > /dev/null";
    char *command;
    char * finalname = (char *)malloc(MAX);

    printf("Escribe el nombre del fichero\n");
    fgets(name, MAX, stdin);

    strtok(name, "\n");

    strcpy(finalname, name);

    strtok(finalname, ".");

    if((command = (char*)malloc(strlen(before)+strlen(after)+strlen(name)+ strlen(finalname)+strlen(extension)+1)) != NULL){
      command[0] = '\0';
      strcat(command, before);
      strcat(command, name);
      strcat(command, after);
      strcat(command, finalname);
      strcat(command, extension);
      strcat(command, "\0");
    } else {
      fprintf(stderr,"malloc newname failed!\n");
    }

    printf("%s\n", command);

    FILE *pc = popen (command, "w");
    pclose(pc);
    free(finalname);
    free(command);

    printf("ffmpeg\n");

    pass = false;
  }
  if((pass == false)){

    if((oldname = (char*)malloc(strlen(olddir)+strlen(name)+1)) != NULL){
      oldname[0] = '\0';
      strcat(oldname, olddir);
      strcat(oldname, name);
    } else {
      fprintf(stderr,"malloc oldname failed!\n");
    }
    remove(oldname);
    printf("removed %s\n", oldname);
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
  wd = inotify_add_watch(inotifyFd, "/var/www/html/login_register/images", IN_MOVED_TO);
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
          if(event->mask & IN_MOVED_TO){
            printf("New file %s moved.\n", event->name);
            sleep(2);
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
