#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {

    FILE* fp;
    char filename[15];
    char newFilename[16];
    char file_line[150];

    printf("Escreva o nome do ficheiro para ser aberto/criado: ");
    scanf("%15[^\n]", filename);
    fflush(stdin);

    //strcat(filename, ".txt");

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

    while (fgets(file_line, 200, fp) != NULL) {
        printf("%s", file_line);
    }

    printf("\n");

    rewind(fp);
    /*
    while (fgets(file_line, 200, fp) != NULL) {
        char c;
        int i = 0;
        while (file_line[i]) {
            c = file_line[i];
            printf("%c", toupper(c));
            i++;
        }
    }
    
    rewind(fp);
    */
   
    FILE* fp2;

    fp2 = fopen("123b.txt", "w");

   while (fgets(file_line, 200, fp) != NULL) {
        char c;
        int i = 0;
        while (file_line[i]) {
            c = file_line[i];
            printf("%c", toupper(c));
            putc(toupper(c), fp2);
            i++;
        }
        //fputs("\n", fp2);
    }


    fclose(fp);

    return EXIT_SUCCESS;

}