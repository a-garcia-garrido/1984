#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "image_file.h"

#define PORT 3550
#define BACKLOG 2
#define MAXBUFF 4096

int main()
{

   int fd, fd2;
   struct sockaddr_in server;
   struct sockaddr_in client;
   socklen_t sin_size;
   struct Timage image;
   char *filename = (char *)"image1.png";


   fd=socket(AF_INET, SOCK_STREAM, 0);

   server.sin_family = AF_INET;
   server.sin_port = htons(PORT);
   server.sin_addr.s_addr = INADDR_ANY;
   bzero(&(server.sin_zero),8);

   bind(fd,(struct sockaddr*)&server, sizeof(struct sockaddr));

   listen(fd,BACKLOG);

   while(1) {
      sin_size = sizeof(struct sockaddr_in);
      fd2 = accept(fd,(struct sockaddr *)&client, &sin_size);
      read(fd2, &image, sizeof(struct Timage));
      write_png_file(filename, image);
      close(fd2);
   }
   close(fd);
   return EXIT_SUCCESS;
}
