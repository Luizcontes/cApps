#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {

    FILE* fp;
    char filename[15];
    char file_line[150];

    printf("Escreva o nome do ficheiro para ser aberto/criado: ");
    scanf("%15[^\n]", filename);
    fflush(stdin);

    fp = fopen(filename, "wx");

    if (fp == NULL) {
        printf("This file alredy exists\n");
        fp = fopen(filename, "r+");
        if (fp == NULL) {

            printf("ERRO na abertura do ficheiro %s !!!!\n", filename);

            return EXIT_FAILURE;
        }
    }
    else {
        printf("Ficheiro %s criado com sucesso!\n", filename);
    }

    FILE* fp2;
    fp2 = fopen("tabulacao2.txt", "w");
    char* pch;

    printf("\n\t");
    while (fgets(file_line, 200, fp) != NULL) {
        pch = strtok(file_line, ";");
        while (pch != NULL) {
            printf("%s\t", pch);
            pch = strtok(NULL, ";");
        }
    }

    fclose(fp);

    return EXIT_SUCCESS;
}