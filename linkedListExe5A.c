#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

typedef struct no {
    int numero;
    char nome[20];
    struct no *proximo;
    struct no *anterior;
} No;

//No *cabeca=NULL;

No *criarNo(int data, char nome[]) {

    No *tmp = (No*)malloc(sizeof(No));

    tmp->numero = data;
    strcpy(tmp->nome, nome);
    tmp->proximo = NULL;
    tmp->anterior = NULL;
 
    return tmp;
}

No *inserirNo(No *no, No *cabeca) {

    if(cabeca==NULL) {
        cabeca = no;
        no->proximo = cabeca;
        no->anterior = cabeca;
    }
    else if (cabeca->proximo==cabeca && cabeca->anterior==cabeca) {
        cabeca->proximo=no;
        no->proximo=cabeca;
        cabeca->anterior=no;
        no->anterior=cabeca;    
    } 
    else {

        No *busca=cabeca;

        do {
            
            busca=busca->proximo;
            
        } while(no->numero>busca->numero && busca->proximo!=cabeca);

        No *tmp=busca;

        if(no->numero==busca->numero) {
            printf("\n***Numero de registro ja utilizado***\n");
        }
        else {
            if (busca->proximo!=cabeca) {
                tmp=tmp->anterior;
            } else if (no->numero>busca->numero){
                busca=busca->proximo;
            } else {
                tmp=tmp->anterior;
            }     
        tmp->proximo=no;
        no->proximo=busca;
        busca->anterior=no;
        no->anterior=tmp;
        }

    }

    return cabeca;
}

void imprimirLista(No *cabeca) {
    
    No *temp = cabeca->proximo;

    printf("\n***FUNCIONARIOS CADASTRADOS***\n");
    printf("Numero\t");
    printf("Nome");
    printf("\n");

    while (temp!=NULL && temp!=cabeca) {
        printf("%d\t", temp->numero);
        printf("%s", temp->nome);
        printf("\n");
        temp = temp->proximo;
    }

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

void deletarRegistro(int data, No *cabeca){

    No *tmp = cabeca->proximo;
    while(tmp->numero!=data && tmp->proximo!=cabeca){
        tmp=tmp->proximo;
    }
    if(tmp->proximo==cabeca && tmp->numero!=data) {
        printf("\n***Registro nao encontrado***\n");
    }
    else {
        tmp->proximo->anterior=tmp->anterior;
        tmp->anterior->proximo=tmp->proximo;
        free(tmp);
    }
}

void buscarRegistro(int data,No *cabeca) {

    No *tmp=cabeca->proximo;
    while(tmp->numero!=data && tmp->proximo!=cabeca){
        tmp=tmp->proximo;
    }
    if(tmp->proximo==cabeca && tmp->numero!=data) {
        printf("\n***Registro nao encontrado***\n");
    }
    else {
        while(tmp->numero!=data) {
            tmp=tmp->proximo;
        }
        printf("\n***REGISTRO DE FUNCIONARIO***\n");
        printf("Numero\t");
        printf("Nome");
        printf("\n");
        printf("%d\t", tmp->numero);
        printf("%s", tmp->nome);
        printf("\n");
        
    }
}

void liberarMemoria(No *cabeca){

    No *tmp;
    while(cabeca!=NULL) {
        tmp=cabeca;
        cabeca=cabeca->proximo;    
        tmp->proximo->anterior=tmp->anterior;
        tmp->anterior->proximo=tmp->proximo;
        free(tmp);
    }
    
    printf("Memoria liberada...");
}

int main() {

    char nome[20];
    char numero[10];
    int sair;
    No *cabeca=NULL;
    No *no;

    no = criarNo(0, nome);
    cabeca = inserirNo(no, cabeca);

    int result;

    do {
        printf("\n*****GESTAO DE FUNCIONARIOS*****\n\n");
        printf("Insira (1) para buscar um funcionario\n");
        printf("Insira (2) para casdastrar um funcionario\n");
        printf("Insira (3) para deletar um funcionario\n");
        printf("Insira (0) para sair\n");

        scanf("%d", &sair);

        if(sair==1) {
            while(sair) {
                int buscar;
                printf("\n*****PROCURA DE FUNCIONARIO*****\n\n");
                printf("Insira o numero do funcionario: ");
                scanf("%d", &buscar);
                buscarRegistro(buscar, cabeca);
                printf("\nDeseja buscar outro funcionario? (0)sair");
                scanf("%d", &sair);
                printf("\n");
            }
            sair=1;
        }

        if(sair==2) {
            do {
                printf("\n*****CADASTRO DE FUNCIONARIO*****\n\n");
                printf("Insira o numero do funcionario: ");
                scanf(" %s", numero);
                printf("Insira o nome do funcionario: ");
                scanf(" %s", nome);

                result = *numero;

                if (isdigit(result)) {
                    result = atoi(numero);

                    no = criarNo(result, nome);
                    cabeca = inserirNo(no, cabeca);
                }
                
                printf("\nInserir outro? (0)sair ");
                scanf("%d", &sair);
                fflush(stdin);
                
            }while(sair);
            imprimirLista(cabeca);
            sair=1;
        }
        
        if(sair==3) {
            while(sair) {
                int deletar;
                printf("Insira um numero de registro para deletar: (0)sair ");
                scanf("%d", &deletar);
                deletarRegistro(deletar, cabeca);
                imprimirLista(cabeca);

                printf("\nDeletar outro? (0)sair ");
                scanf("%d", &sair);
                fflush(stdin);
            }
            sair=1;
        }
        
    } while(sair);

    liberarMemoria(cabeca);

    return 0;
}