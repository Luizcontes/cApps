#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILENAME 20
#define MAX_LINE 160

int main() {

    FILE* fp;
    char filename[MAX_FILENAME];
    char line[MAX_LINE];
    int ch;

    printf("Escreva o nome do ficheiro: ");
    scanf("%s", filename);

    fp = fopen(filename, "r");

    if (fp == NULL) {
        printf("ERRO na abertura do ficheiro %s !!!\n", filename);
        return EXIT_FAILURE;
    }
    else
        printf("Ficheiro %s aberto com sucesso!\n", filename);

    /*
    printf("\n>>> Conteudo do ficheiro lendo caracter a caracter:\n\n");

    ch = fgetc(fp);

    while (ch != EOF) {
        printf("%c", (unsigned char)ch);
        ch = fgetc(fp);
    }
    */
   
    printf("\n\n>>> Conteudo do ficheiro lendo linha a linha:\n\n");

    //rewind(fp);

    while (fgets(line, MAX_LINE, fp) != NULL)
        printf("%s", line);

    //printf("\n");


    if (fp != NULL)
        fclose(fp);


    return EXIT_SUCCESS;
}