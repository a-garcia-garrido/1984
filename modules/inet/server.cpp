#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#define PORT 3550
#define BACKLOG 2

int main()
{

   int fd, fd2;
   struct sockaddr_in server;
   struct sockaddr_in client;
   socklen_t sin_size;


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
      write(fd2, "Bienvenido a mi servidor", 24);
      close(fd2);
   }
   close(fd);
   return EXIT_SUCCESS;
}
