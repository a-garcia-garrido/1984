#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <fstream>
#include <errno.h>
#include <signal.h>
#include <sys/wait.h>
#include <time.h>

using namespace std;

static void clean_up_child_process (int signal_number)
{
  int status;
  wait (&status);
}

int receive_image(int socket)
{ // Start function

  int buffersize = 0, recv_size = 0,size = 0, read_size, write_size, packet_index =1,stat;
  time_t current_time;
  char* c_time_string;
  char imagearray[10241],verify = '1';
  FILE *image;

  current_time = time(NULL);
  c_time_string = ctime(&current_time);
  //Find the size of the image
  do{
    stat = read(socket, &size, sizeof(int));
  }while(stat<0);

  printf("Packet received.\n");
  printf("Packet size: %i\n",stat);
  printf("Image size: %i\n",size);
  printf(" \n");

  char buffer[] = "Got it";

  //Send our verification signal
  do{
    stat = write(socket, &buffer, sizeof(int));
  }while(stat<0);

  printf("Reply sent\n");
  printf(" \n");

  image = fopen(c_time_string, "w");

  if( image == NULL) {
    printf("Error has occurred. Image file could not be opened\n");
    return -1; }

    //Loop while we have not received the entire file yet


    int need_exit = 0;
    struct timeval timeout = {10,0};

    fd_set fds;
    int buffer_fd, buffer_out;

    while(recv_size < size) {
      //while(packet_index < 2){

      FD_ZERO(&fds);
      FD_SET(socket,&fds);

      buffer_fd = select(FD_SETSIZE,&fds,NULL,NULL,&timeout);

      if (buffer_fd < 0)
      printf("error: bad file descriptor set.\n");

      if (buffer_fd == 0)
      printf("error: buffer read timeout expired.\n");

      if (buffer_fd > 0)
      {
        do{
          read_size = read(socket,imagearray, 10241);
        }while(read_size <0);

        printf("Packet number received: %i\n",packet_index);
        printf("Packet size: %i\n",read_size);


        //Write the currently read data into our image file
        write_size = fwrite(imagearray,1,read_size, image);
        printf("Written image size: %i\n",write_size);

        if(read_size !=write_size) {
          printf("error in read write\n");    }


          //Increment the total number of bytes read
          recv_size += read_size;
          packet_index++;
          printf("Total received image size: %i\n",recv_size);
          printf(" \n");
          printf(" \n");
        }

      }


      fclose(image);
      printf("Image successfully Received!\n");
      return 1;
    }

    int main(int argc , char *argv[])
    {
      int socket_desc , new_socket , c, read_size,buffer = 0;
      struct sockaddr_in server , client;
      char *readin;
      struct sigaction sigchld_action;
      pid_t child_pid;

      memset (&sigchld_action, 0, sizeof (sigchld_action));
      sigchld_action.sa_handler = &clean_up_child_process;
      sigaction (SIGCHLD, &sigchld_action, NULL);
      //Create socket
      socket_desc = socket(AF_INET , SOCK_STREAM , 0);
      if (socket_desc == -1)
      {
        printf("Could not create socket");
      }

      //Prepare the sockaddr_in structure
      server.sin_family = AF_INET;
      server.sin_addr.s_addr = INADDR_ANY;
      server.sin_port = htons( 8889 );

      //Bind
      if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
      {
        puts("bind failed");
        return 1;
      }

      puts("bind done");

      //Listen
      listen(socket_desc , 3);

      //Accept and incoming connection
      puts("Waiting for incoming connections...");
      c = sizeof(struct sockaddr_in);
      while (1){
        if ((new_socket = accept(socket_desc, (struct sockaddr *)&client,(socklen_t*)&c)) > 0) {

          fflush(stdout);

          if (new_socket<0)
          {
            perror("Accept Failed");
            return 1;
          }
          puts("Connection accepted");
          //child_pid = fork();
          if (fork() == 0)
          {
            close (STDIN_FILENO);
            close (STDOUT_FILENO);
            close (socket_desc);
            receive_image(new_socket);
            close (new_socket);
            exit(0);
          }

          close (new_socket);
        }
      }

      fflush(stdout);
      return 0;
    }
