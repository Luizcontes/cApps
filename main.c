#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef struct no_lista {
  int data;
  struct no_lista* proximo;
}no;

no *cabeca=NULL;

no *criarNo(int data) {

    no *temporario = (no *) malloc(sizeof(no));

    temporario->data = data;
    temporario->proximo = NULL;

    return temporario;
}

no *inserirNo(no *x, no *novoNo) {

    novoNo->proximo = x;
    cabeca = novoNo;

    return novoNo;
}

void imprimeLista(no *lista) {

    no *tmp = lista;

    while (tmp!= NULL) {
        printf("%d -> ", tmp->data);
        tmp = tmp->proximo;
    }

}

void inserirAposNo(no *noAInserir, no* noNovo) {
    noNovo->proximo = noAInserir->proximo;
    noAInserir->proximo = noNovo;
}

no *buscarNo(no *x, int value) {

    no *tmp = x;
    while(tmp!=NULL) {
        if(tmp->data == value) {
            return tmp;
        }
        tmp = tmp->proximo;
    }
    return NULL;
}

no *buscarNo2(int n) {
    no *temp1 = cabeca;
    if(n==1) {
//        cabeca = temp1->proximo;
//        free(temp1);
//        return cabeca;
    }
    else {
        int i;
        for(i=0;i<n-1;i++) {
            temp1 = temp1->proximo;
        }
    //    no *temp2 = temp1->proximo;
    //    temp1->proximo = temp2->proximo;
    //    free(temp2);
    }
    return temp1;
}

void Delete(int n) {
    no *temp1 = cabeca;
    if(n==1) {
        cabeca = temp1->proximo;
        free(temp1);
        return;
    }
    int i;
    for(i=0;i<n-2;i++) {
        temp1 = temp1->proximo;
    }
    no *temp2 = temp1->proximo;
    temp1->proximo = temp2->proximo;
    free(temp2);
}

int main(){

    int numeros[] = {3, 2, 8, 6, 4, 4, 12};
    no *no;

    for (int i=0; i<7; i++){
      no = criarNo(numeros[i]);
      inserirNo(cabeca, no);
    }

    imprimeLista(cabeca);

    printf("\n");

    Delete(5);

    no = buscarNo(cabeca, 2);
    printf("No encontrado %d\n", no->data);

    inserirAposNo(no, criarNo(25));

    imprimeLista(cabeca);

    printf("\n");

    system("PAUSE");

    return 0;
}
