#include <iostream>
#include <stdlib.h>

using namespace std;

char matrix[6][7];
int player1Score=0;
int player2Score=0;
char playerSign;
bool counter;
int flow=1;
int colunaIndice;
char charColunaIndice;

void imprimeMatrix() { // Imprime o tabuleiro na consola

    //system("CLS");
    cout << endl << "   Player (O)  " << player1Score << "x" << player2Score << "  Player (X)" << endl;
    cout << endl << "    1  2  3  4  5  6  7" << endl;
    for(int i=0;i<6;i++) {
        cout << "   ";
        for(int j=0;j<7;j++) {
            cout << "[";
            cout << matrix[i][j];
            cout << "]";
        }
        cout << endl;
    }
    cout << endl;
}

void inicializar() {   // Preenche a matrix com vazios ' '

    for(int i=0;i<6;i++) {
        for(int j=0;j<7;j++) {
            matrix[i][j]=' ';
        }
    }
    imprimeMatrix();
}

void outraPartida() {  // Pergunta aos usuarios se querem jogar novamente

    char charOPartida;

    cout << "Gostaria de jogar outra partida?(s/n)";
    cin >> charOPartida;

    while(charOPartida!='s' && charOPartida!='n') {
        cout << "Entre a opcao correta(s/n)" << endl;
        cin >> charOPartida;
    }

    if (charOPartida=='n') {
        imprimeMatrix();
        cout << endl;
        cout << "PLAYER (O): " << player1Score << endl;
        cout << "PLAYER (X): " << player2Score << endl;
        cout << endl << endl << endl;
        cout << endl << endl << endl;
        flow=0;
        colunaIndice=65;
    }
    else if(charOPartida=='s') {
        inicializar();

    }
}

void playerTurn() {    // Faz a mudanca de jogador e informar qual o simbolo a utilizar quando cada um deles joga

    char player1='O';
    char player2='X';

    counter = !counter;
    if(counter==true) {
        playerSign = player1;
    }
    else {
        playerSign = player2;
    }
}

void checkFullBoard() {  // Confere se o tabuleiro ja nao se encontra totalmente cheio

    int checkUpperLine=0;
    for(int i=0; i<7; i++) {
        checkUpperLine = checkUpperLine + matrix[0][i];
    }
    if(checkUpperLine>=553) {
        checkUpperLine=0;
        cout << "Empate!!! ";
        outraPartida();
    }
}

void jogadaGet() {      // Pede ao jogador da vez que faca a sua jogada, confere se o caracter inserido e aceito, se o jogador nao pediu pra sair e se a coluna
                        // escolhida ja nao se encontra totalmente preenchida
    if(flow!=0) {
        bool inputValidation=false;
        do{
            cout << "Selecione o indice da coluna para joga(1-7). Pressione (q) para sair." << endl;
            cout << "Player (" << playerSign << ") ";
            cin >> charColunaIndice;

            int p[] = {1,2,3,4,5,6,7};
            colunaIndice = charColunaIndice-'0';
            for(int i=0; i<7;i++) {
                if (p[i]==colunaIndice) {
                colunaIndice--;
                inputValidation=true;
                break;
                }
            }
           if(colunaIndice==65) {
                inputValidation=true;
                break;
            }
            else if (inputValidation==false) {
                imprimeMatrix();
                cout << "*** Insira um numero de 1-7 *** " << endl;
                inputValidation=false;
            }
            else if (matrix[0][colunaIndice]!=' ') {
                imprimeMatrix();
                cout << "*** Escolha outra coluna para jogar ***" << endl;
                inputValidation=false;
            }
        } while(inputValidation==false);
    }
}

bool checarGanhadorH() {  // Checa se ha ganhador na horizontal

    int cCheck=0;

    for(int i=0; i<6; i++) {
        for(int z=0; z<4; z++) {
            int winner=0;
            for(int j=0; j<4; j++) {
                if (matrix[i][j+cCheck]==playerSign) {
                    winner = winner + playerSign;
                }
                if(winner==playerSign*4) {
                    return true;
                }
            }
            cCheck++;
        }
        cCheck=0;
    }
    return false;
}

bool checarGanhadorV() {  // Checa se ha ganhador na Vertical

    int cCheck=0;

    for(int z=0; z<3; z++) {
        for(int i=0; i<7; i++) {
            int winner=0;
            for(int j=0; j<4; j++) {
                if (matrix[j+cCheck][i]==playerSign) {
                    winner = winner + playerSign;
                }
                if(winner==playerSign*4) {
                    return true;
                }
            }
        }
        cCheck++;
    }
    return false;
}

bool checarGanhadorDUp() {  // Checa se ha ganhador na diagonal subindo

    int cCheck=0;
    int dCheck=0;

    for(int z=0; z<3; z++) {
        for(int i=0; i<4; i++) {
            int winner=0;
            for(int j=5; j>1; j--) {
                if (matrix[j+cCheck][i+dCheck]==playerSign) {
                        winner = winner + playerSign;
                    }
                if(winner==playerSign*4) {
                    return true;
                }
            dCheck++;
            }
            dCheck=0;
        }
        cCheck--;
    }
    return false;
}

bool checarGanhadorDDown() {  // Checa se ha ganhador na diagonal descendo

    int cCheck=0;
    int dCheck=0;

    for(int z=0; z<3; z++) {
        for(int i=0; i<4; i++) {
            int winner=0;
            for(int j=0; j<4; j++) {
                if (matrix[j+cCheck][j+dCheck]==playerSign) {
                    winner = winner + playerSign;
                }
                if(winner==playerSign*4) {
                    return true;
                }
            }
            dCheck++;
        }
        dCheck=0;
        cCheck++;
    }

    return false;
}

void ganhador() {             // Checa quem e o ganhador atualiza o placar e pergunta se gostariam de jogar mais uma vez

    int soma = checarGanhadorH()+checarGanhadorV()+checarGanhadorDUp()+checarGanhadorDDown();

    if(counter==true && soma==1) {
        cout << "Player (" << playerSign << ") vencedor" << endl;
        player1Score++;
        outraPartida();
    }
    if(counter==false && soma==1) {
        cout << "Player (" << playerSign << ") vencedor" << endl;
        player2Score++;
        outraPartida();
    }
}

void preencherMatrix() {      // preenche a matrix com a jogada efetuada, chama o metodo para reimprimir o tabuleiro e chama o metodo para verificar se ha ganhador

    int linha = 5;
    while (matrix[linha][colunaIndice]!=' ') {
        for (int i=0;i<6;i++) {
        linha--;
        break;
       }
    }
    matrix[linha][colunaIndice] = playerSign;
    imprimeMatrix();
    ganhador();
}

int main(){  // introduzir metodo para evitar multiplas jogadas deuma so vez

    inicializar();

    while (flow!=0) {
        playerTurn();
        checkFullBoard();
        jogadaGet();

        if(colunaIndice!=65) {
            preencherMatrix();
        } else {
            flow = 0;
        }
    }
    system("PAUSE");
    return 0;
}
