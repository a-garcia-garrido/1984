#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 0x100

int main(int argc, char const *argv[]) {

  char *name = (char *)malloc(MAX);
  char *newname;
  char *oldname;
  printf("Escribe el nombre del fichero\n");
  fgets(name, MAX, stdin);
  const char *newdir = "test/";
  const char *olddir = "watched/";

  strtok(name, "\n");

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

  printf("%s \n", newname);
  printf("%s \n", oldname);

  rename(oldname, newname);


  return 0;
}
