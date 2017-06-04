#include <stdio.h>
#include <stdlib.h>
int main(){
    char tuTex[20];
    char aux = '/';
    FILE *pf;
    /*abre o crea el archivo indicado*/
    pf = fopen("archivo_creado.txt", "r");
    /*escribe en el archivo creado la frase */
    fscanf(pf, " %s", tuTex);
    printf("%c%s\n",aux,tuTex);
    fclose(pf);
    return EXIT_SUCCESS;
}
