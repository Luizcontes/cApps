#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME_MAX_LEN 20
#define FILE_LINE_MAX_LEN 50+1

int main() {

    FILE* fp;
    char filename[FILE_NAME_MAX_LEN];
    char line[FILE_LINE_MAX_LEN];

    printf("Escreva o nome do ficheiro para ser aberto/criado: ");
    scanf("%20[^\n]", filename);
    fflush(stdin);

    //strcat(filename, ".txt");

    fp = fopen(filename, "wx");

    if (fp == NULL) {
        printf("This file alredy exists\n");
        fp = fopen(filename, "a");
        fputs("\n", fp);
            if (fp == NULL) {

                printf("ERRO na abertura do ficheiro %s !!!!\n", filename);

                return EXIT_FAILURE;
            }
    }
    else {
        printf("Ficheiro %s criado com sucesso!\n", filename);
    }

    printf("Escreva a frase ser inserida na proxima linha: ");
    scanf(" %50[^\n]", line);
    fflush(stdin);

    fputs(line, fp);

    fclose(fp);

    return EXIT_SUCCESS;
}