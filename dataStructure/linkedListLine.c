#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct no {
    int number;
    char* nome;
    struct no* proximo;
} No;

No* criarNo(int i, char* a) {

    No* tmp = (No*)malloc(sizeof(No));

    tmp->number = i;
    tmp->nome = strdup(a);
    tmp->proximo = NULL;

    return tmp;
}

void inserirNo(No* cabeca, No* no) {

    No* y = NULL;

    if (cabeca->proximo == NULL)
        cabeca->proximo = no;
    else {
        y = cabeca;
        inserirNo(y->proximo,no);
    }
}

void imprimirLista(No* cabeca) {

    No* tmp = cabeca;

    while (tmp != NULL) {
        printf("numero: %d - nome: %s\n", tmp->number, tmp->nome);
        imprimirLista(tmp->proximo);    
        break;
    }
}

void deletarLista(No *cabeca) {

    No * y;

    while (cabeca->proximo != NULL) {
        y = cabeca;
        cabeca = y->proximo;
        free(y->nome);
        free(y);        
    }
    free(cabeca->nome);
    free(cabeca);
}

int main() {

    No* cabeca = NULL;

    int numero;
    char nome[20];

    for (int i = 0;i < 4;i++) {
        printf("Digite numero ");
        scanf("%d", &numero);
        printf("Digite o nome do funcionario ");
        scanf("%s", nome);
        No* no = criarNo(numero, nome);
        if (cabeca == NULL)
            cabeca = no;
        else
            inserirNo(cabeca, no);
    }

    imprimirLista(cabeca);
    deletarLista(cabeca);

    return 0;
}

