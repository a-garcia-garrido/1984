#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 0x1000

int main(int argc, char const *argv[]) {

  char *name = (char *)malloc(MAX);

  const char *before = "ffmpeg -i ";
  const char *after = " -r 2 -ss 00:00:00 ";
  const char *extension = "-%3d.png";
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

  free(command);
  free(name);
  free(finalname);

  return 0;
}
