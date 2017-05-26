#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>

#include "image_file.h"

int
main (int argc, char **argv)
{
  struct sockaddr_in client;	//Declaración de la estructura con información para la conexión
  struct hostent *server;	//Declaración de la estructura con información del host
  server = gethostbyname (argv[1]);	//Asignacion
  int port, fd;
  struct Timage image;
  char *filename;

  fd = socket (AF_INET, SOCK_STREAM, 0);	//Asignación del socket
  port = (atoi (argv[2]));	//conversion del argumento
  bzero ((char *) &client, sizeof ((char *) & client));	//Rellena toda la estructura de 0's
  //La función bzero() es como memset() pero inicializando a 0 todas la variables
  client.sin_family = AF_INET;	//asignacion del protocolo
  client.sin_port = htons (port);	//asignacion del puerto
  bcopy ((char *) server->h_addr, (char *) &client.sin_addr.s_addr,
	 sizeof (server->h_length));

  connect (fd, (struct sockaddr *) &client, sizeof (client));
  printf ("Escribe el nombre de la imagen: ");
  //fgets(filename, 100, stdin);
  scanf ("%s", filename);
  read_png_file (filename, image);
  write (fd, &image, sizeof (struct Timage));	//envio
  bzero (&image, sizeof (struct Timage));
  return 0;
}
