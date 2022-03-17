#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

typedef struct no {
    int numero;
    char nome[20];
    struct no *proximo;
} No;

No *cabeca=NULL;

No *criarNo(int data, char nome[]) {

    No *tmp = (No*)malloc(sizeof(No));

    tmp->numero = data;
    strcpy(tmp->nome, nome);
    tmp->proximo = NULL;
 
    return tmp;
}

No *inserirNo(No *no, No *cabeca) {

    No *busca = cabeca;
    No *buscaAnt = cabeca;


    if(cabeca==NULL) {
        no->proximo = cabeca;
        cabeca = no;
    } 
    else if (no->numero>busca->numero) {
        int i=0;
        while(no->numero>busca->numero && busca->proximo!=NULL) {
            busca = busca->proximo;
            if(i>0) {
                buscaAnt = buscaAnt->proximo;
            }
            i++;
        }
        if(busca->proximo==NULL && no->numero>busca->numero) {
            busca->proximo = no;
        } else if (buscaAnt->numero<no->numero && no->numero<busca->numero) {
        buscaAnt->proximo = no;
        no->proximo = busca;
        } else {
            printf("\n***Funcionario ja cadastrado neste registro***\n");
        }
    }
    else if (no->numero==busca->numero) {
        printf("\n***Funcionario ja cadastrado neste registro***\n");
    }
    else {
        no->proximo = cabeca;
        cabeca = no;
    }

    return cabeca;
}

void imprimirLista(No *cabeca) {
    
    No *temp = cabeca;

    printf("***FUNCIONARIOS CADASTRADOS***\n\n");
    printf("Numero\t");
    printf("Nome");
    printf("\n");

    while (temp!=NULL) {
        printf("%d\t", temp->numero);
        printf("%s", temp->nome);
        printf("\n");
        temp = temp->proximo;
    }

    printf("\n\n\n");

}

void apagarLista(No *cabeca, int count) {

    No *tmp;

    do {
    
    tmp = cabeca;
        
        for(int i=1; i<count; i++) {

            tmp = tmp->proximo;
        }
        free(tmp);
        count--;
    } while(count>0);

    printf("\nMemoria liberada com sucesso...\n");

}

int main() {

    char nome[20];
    char numero[10];
    int numProc;
    int posicao;
    int sair=1;
    int count=0;
    No *no;

    int result;

    printf("*****Cadastro de novo funcionario*****\n\n");
    do {
        
        printf("Insira o numero do funcionario: ");
        scanf(" %s", numero);
        printf("Insira o nome do funcionario: ");
        scanf(" %s", nome);

        result = *numero;

        if (isdigit(result)) {
            result = atoi(numero);

            no = criarNo(result, nome);
            cabeca = inserirNo(no, cabeca);
            count++; 
        }
        
        printf("\nInserir outro? (1)sim (0)nao ");
        scanf("%d", &sair);
        fflush(stdin);
        
    }while(sair);  

    imprimirLista(cabeca);
    apagarLista(cabeca, count);

    return 0;
}