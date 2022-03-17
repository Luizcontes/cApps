#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

typedef struct no {
    int numero;
    struct no *proximo;
} No;

No *cabeca=NULL;

No *criarNo(int data) {

    No *tmp = (No*)malloc(sizeof(No));

    tmp->numero = data;
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
            printf("Numero ja inserido anteriormente\n");
        }
    }
    else if (no->numero==busca->numero) {
        printf("Numero ja inserido anteriormente\n");
    }
    else {
        no->proximo = cabeca;
        cabeca = no;
    }

    return cabeca;
}

void imprimirLista(No *cabeca) {

    No *temp = cabeca;

    while (temp!=NULL) {
        printf("%d ", temp->numero);
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
/*
void inserirApos(int posicao, int data, No *cabeca) {

    No *busca = cabeca;
    No *busca2;
    No *temp;

    for(int i=9;i>posicao;i--) {
        busca = busca->proximo;
    }

    busca2 = busca;
    busca2 = busca2->proximo;

    temp = criarNo(data);
    busca->proximo = temp;
    temp->proximo = busca2;

    imprimirLista(cabeca);

}

int procurarValor(int data, No *cabeca) {

    No *temp = cabeca;

    int count=10;
    while (temp!=NULL) {
        if(temp->numero==data) {
            printf("numero encontrado na posicao %d\n", count);
            break;
        }
        else if(temp->numero<data) {
            printf("Posicao disponivel para insercao de numero %d\n", count);
            break;
        }

        temp= temp->proximo;
        count--;
    }

    if(count==0) {
        printf("Numero nao encontrado\n");
    }

    return count;
}
*/
int main() {

    char num[10];
    int numProc;
    int posicao;
    int sair=1;
    int count=0;
    No *no;

    int result;

    printf("Insira qualquer outro caracter para sair\n\n");
    do {
        printf("Insira um numero para adicionar a lista: ");
        fgets(num, 100, stdin);

        result = *num;

        if (isdigit(result)) {
            result = atoi(num);
            //printf("\n%d\n", result);
            //posicao = procurarValor(numProc, cabeca);
            no = criarNo(result);
            cabeca = inserirNo(no, cabeca);
            count++; 
        } else {
            sair = 0;
        }   
    } while (sair);

    imprimirLista(cabeca);
    apagarLista(cabeca, count);

    return 0;
}