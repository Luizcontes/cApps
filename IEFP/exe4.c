#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef union {
    char* nome;
    long tel;
} coluna;
typedef struct cadastro {
    int count;
    char* nome;
    coluna valor;
    char* email;
    struct cadastro* proximo;
} cadastro;

cadastro* criar(int count) {

    cadastro* tmp = (cadastro*)malloc(sizeof(cadastro));

    tmp->count = count;


    return tmp;
}

void inserir(cadastro* head, cadastro* n) {

    if (head->proximo == NULL)
        head->proximo = n;
    else
        while (head->proximo != NULL)
            head = head->proximo;
    head->proximo = n;
}

void imprimirLista(cadastro* head) {

    cadastro* tmp;

    tmp = head;

    printf("%s\t%s\t%s\n", tmp->nome, tmp->valor.nome, tmp->email);

    tmp = head->proximo;
    while (tmp != NULL) {
        printf("%s\t%ld\t%s", tmp->nome, tmp->valor.tel, tmp->email);
        tmp = tmp->proximo;
    }
}

void escreverArquivo(cadastro* head) {

    FILE* op2 = fopen("cadastro2.txt", "w");;
    char* result;

    while (head != NULL) {
        result = strdup(head->nome);
        result = strcat(result, "#");
        if (head->count == 0) {
            result = strcat(result, head->valor.nome);
            result = strcat(result, "#");
        }
        else {
            char buffer[10];
            sprintf(buffer, "%ld", head->valor.tel);
            result = strcat(result, buffer);
            result = strcat(result, "#");
        }
        result = strcat(result, head->email);
        fputs(result, op2);
        head = head->proximo;
        free(result);
    }

    fclose(op2);
}

int liberarMemoria(cadastro* head) {

    cadastro* tmp;
    if (head == NULL)
        return 0;
    tmp = head;
    head = tmp->proximo;
    if (tmp->count == 0)
        free(tmp->valor.nome);
    free(tmp->nome);
    free(tmp->email);
    free(tmp);
    liberarMemoria(head);

}

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

    char* pch;
    cadastro* head;
    cadastro* n;
    int count = 0;

    while (fgets(file_line, 200, fp) != NULL) {
        pch = strtok(file_line, ";");
        n = criar(count);
        n->nome = strdup(pch);
        pch = strtok(NULL, ";");
        if (count == 0)
            n->valor.nome = strdup(pch);
        else
            n->valor.tel = atol(pch);
        pch = strtok(NULL, ";");
        n->email = strdup(pch);
        pch = strtok(NULL, ";");
        count++;
        if (head == NULL)
            head = n;
        else
            inserir(head, n);
    }

    fclose(fp);
    imprimirLista(head);
    escreverArquivo(head);
    liberarMemoria(head);

    printf("\n");

    return EXIT_SUCCESS;
}