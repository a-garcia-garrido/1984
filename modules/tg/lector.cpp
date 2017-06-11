#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


int main(){
    char cmd[512];
    char *path; //  MAX_PATH = 256
    char tuText[20];
    char aux = '/';
    FILE *pf;
    /*abre o crea el archivo indicado*/
    pf = fopen("/home/tester/1984/modules/recognition/src/lee/name.txt", "r");
    /*escanea en el archivo creado la frase */
    fscanf(pf, " %s", tuText);
    printf("%c%s\n",aux,tuText);
  //system("telegram_sendmsg.sh contact_list '%c%s' PyBot-1984");
  //system("send-telegram.sh tuText");
    //path = readLine(stdin); //  leemos una linea desde el buffer de entrada del teclado
    sprintf(cmd, "send-telegram.sh \"/%s\"", tuText); //  construimos la cadena por ejemplo: mkdir "c:\Hola Mundo desde C-ANSI"
    system(cmd);    //  Ejecutamos.
    //system("send-telegram.sh `date -I`:'fecha de ejecucion'");

    free(path);
    getchar();
    fclose(pf);
    return EXIT_SUCCESS;
}
