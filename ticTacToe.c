#include <stdlib.h>
#include <stdio.h>

char matrix[9];
int player1Score=0;
int player2Score=0;
char playerSign;
int counter;
int flow=1;
int indice=0;
char charIndice;

void imprimeMatrix() {  // Este metodo imprime o tabuleiro na consola

    int contador=0;
    printf("\nPlayer (O)  %dx%d  Player (X)\n",player1Score, player2Score);
    printf("\n\n");
    int y;
    for(y=0;y<3;y++){
        int i;
        printf("           ");
        for(i=0;i<3;i++) {
            printf(" ");
            if(matrix[contador]==' ') {
                printf("%d", contador+1);
            } else {
                printf("%c", matrix[contador]);
            }
            printf(" ");
            if(i<2) {
                printf("|");
            }
            contador++;
        }
        if(y<2) {
            printf("\n           -----------\n");
        }
    }
    contador=0;
    printf("\n\n");

}

void inicializar() {  // Este metodo preenche a matriz com caracteres ' '

    for(int i=0;i<9;i++) {
         matrix[i]=' ';
    }
    imprimeMatrix();
}

void outraPartida() {   // Este metodo pergunta ao jogador se deseja jogar novamente apos uma vitoria ou empate

    char charOPartida;

    printf("Gostaria de jogar outra partida?(s/n)");
    scanf("%c", &charOPartida);

    while(charOPartida!='s' && charOPartida!='n') {
        printf("Entre a opcao correta(s/n)\n");
        scanf("%c", &charOPartida);
    }

    if (charOPartida=='n') {
        imprimeMatrix();
        printf("\nPLAYER (O): %d",player1Score);
        printf("\nPLAYER (X): %d\n",player2Score);
        printf("\n\n\n\n\n\n");
        flow=0;
        indice=65;
    }
    else if(charOPartida=='s') {
        inicializar();
    }
}

void playerTurn() {  // Este metodo revesa entre jogadores e tambem retorna o simbolo utilizado por cada um delete

    char player1='O';
    char player2='X';

    if(counter==0){
        counter = 1;
    } else {
        counter = 0;
    }

    if(counter==1) {
        playerSign = player1;
    }
    else {
        playerSign = player2;
    }
}

void checkFullBoard() {  // Este metodo verifica se o tabuleiro ja nao esta totalmente preenchido

    int checkBoard=0;
    for(int i=0; i<9; i++) {
        checkBoard = checkBoard + matrix[i];
    }
    if(checkBoard>=747) {
        checkBoard=0;
        printf("Empate!!! ");
        outraPartida();
        }
}

void jogadaGet() {  // Este metodo pede ao jogador que escolha uma casa para jogar, tambem verifica se a casa escolhida ja nao se encontrada ocupada bem como,
                   // verifica se o caracter inserido corresponde aos que podem ser utilizados. Este metodo tambem possibilita que o jogador possa encerrar
    if(flow!=0) {   // o jogo a qualquer momento
        int inputValidation=0;
        do {
            printf("Selecione a casa para jogar(1-9). Pressione (q) para sair.\n");
            printf("Player (%c): ", playerSign);
            scanf(" %c", &charIndice);

            int p[] = {1,2,3,4,5,6,7,8,9};
            indice = charIndice-'0';
            for(int i=0; i<9;i++) {
                if (p[i]==indice) {
                    indice--;
                    inputValidation = 1;
                    break;
                }
            }

            if(indice==65) {
            inputValidation=1;
            break;
            }
            else if (inputValidation==0) {
                imprimeMatrix();
                printf("*** Insira um numero de 1-9 *** \n");
                inputValidation=0;
                }
            else if (matrix[indice]!=' ') {
                imprimeMatrix();
                printf("*** Escolha outra posicao para jogar ***\n");
                inputValidation=0;
            }
        } while(inputValidation==0);
    }
}

int checarGanhadorH() {   // checa se ha uma sequencia vencedora na posicao horizontal

    int winnerH=0;
    for(int z=0; z<7; z=z+3) {
        for(int i=0; i<3; i++) {
            if (matrix[i+z]==playerSign) {
                winnerH = winnerH + playerSign;
            }
            if(winnerH==playerSign*3) {
                return 1;
            }
        }
        winnerH=0;
    }

    return 0;
}

int checarGanhadorV() {  // checa se ha uma sequencia vencedora na posicao vertical

    int winnerV=0;;
    for(int z=0; z<4; z++) {
        for(int i=0; i<7; i=i+3) {
            if (matrix[i+z]==playerSign) {
                winnerV = winnerV + playerSign;
            }
            if(winnerV==playerSign*3) {
                return 1;
            }
        }
        winnerV=0;
    }

    return 0;
}

int checarGanhadorDDown() {  // checa se ha uma sequencia vencedora na posicao diagonal descendo

    int winnerDDown=0;
        for(int i=0; i<9; i=i+4) {
            if (matrix[i]==playerSign) {
                winnerDDown = winnerDDown + playerSign;
            }
            if(winnerDDown==playerSign*3) {
                return 1;
            }
        }
        winnerDDown=0;

    return 0;
}

int checarGanhadorDUp() { // checa se ha uma sequencia vencedora na posicao diagonal descendo

        int winnerDUp=0;
        for(int i=2; i<7; i=i+2) {
            if (matrix[i]==playerSign) {
                winnerDUp = winnerDUp + playerSign;
            }
            if(winnerDUp==playerSign*3) {
                return 1;
            }
        }
        winnerDUp=0;

    return 0;
}

void ganhador() {  // checa se ha um ganhador nesta partida e atualizada o placar

    int soma = checarGanhadorH()+checarGanhadorV()+checarGanhadorDDown()+checarGanhadorDUp();

    if(counter==1 && soma==1) {
        printf("Player (%c) vencedor\n", playerSign);
        player1Score++;
        outraPartida();
    }
    if(counter==0 && soma==1) {
        printf("Player (%c) vencedor\n", playerSign);
        player2Score++;
        outraPartida();
    }
}

void preencherMatrix() {  // preenche a matriz com a jogada ao fim de cada loop e chama a funcao para verificar se ha um ganhador

    matrix[indice] = playerSign;
    imprimeMatrix();
    ganhador();
}

int main(){

    inicializar();

    while (flow!=0) {
        playerTurn();
        checkFullBoard();
        jogadaGet();

        if(indice!=65) {
            preencherMatrix();
        } else {
           flow = 0;
        }
    }

    return 0;
}
