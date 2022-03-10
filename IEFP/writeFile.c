#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "output_file.txt"
#define FILE_CONTENT_LINE_1 "Texto da primeira linha."
#define FILE_CONTENT_LINE_2 "Texto da segunda linha."
#define FILE_MAX_LINE 160

int main() {

    FILE* fp;
    char filename[] = FILE_NAME;
    char line[FILE_MAX_LINE];
    int i;

    fp = fopen(filename, "w");

    if (fp == NULL) {
        printf("ERRO na abertura do ficheiro %s !!!\n", filename);
        return EXIT_FAILURE;
    }
    else
        printf("Ficheiro %s aberto com sucesso!\n", filename);

    strcpy(line, FILE_CONTENT_LINE_1);

    printf(">>>> Vai escrever a primeira linha caracter a caracter: %s\n", line);

        for (i = 0; i < strlen(line); i++)
            fputc((int) line[i], fp);
    //i++;
    fputs("\n", fp);
            
    strcpy(line, FILE_CONTENT_LINE_2);

    printf(">>>> Vai escrever a segunda linha de uma assentada: %s\n", line);

    fputs(line, fp);

    if (fp != NULL)
        fclose(fp);

    return EXIT_SUCCESS;
}