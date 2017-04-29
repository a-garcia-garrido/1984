#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
int main(int argc, char **argv){
  struct sockaddr_in cliente; //Declaración de la estructura con información para la conexión
  struct hostent *servidor; //Declaración de la estructura con información del host
  servidor = gethostbyname(argv[1]); //Asignacion
  int puerto, conexion;
  char buffer[100];

  conexion = socket(AF_INET, SOCK_STREAM, 0); //Asignación del socket
  puerto=(atoi(argv[2])); //conversion del argumento
  bzero((char *)&cliente, sizeof((char *)&cliente)); //Rellena toda la estructura de 0's
        //La función bzero() es como memset() pero inicializando a 0 todas la variables
  cliente.sin_family = AF_INET; //asignacion del protocolo
  cliente.sin_port = htons(puerto); //asignacion del puerto
  bcopy((char *)servidor->h_addr, (char *)&cliente.sin_addr.s_addr, sizeof(servidor->h_length));

  connect(conexion,(struct sockaddr *)&cliente, sizeof(cliente));
  printf("Escribe un mensaje: ");
  fgets(buffer, 100, stdin);
  write(conexion, buffer, 100); //envio
  bzero(buffer, 100);
return 0;
}
