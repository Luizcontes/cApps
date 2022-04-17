#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define M ";"

typedef struct no {
    int ativo;
    int num;
    char* nome;
    char tel[13];
    float cred;
    struct no* proximo;
} NO;

    //funcao para criar o no
NO* criarNo() {

    NO* tmp;
    tmp = (NO*)malloc(sizeof(NO));
    tmp->proximo = NULL;
    tmp->ativo = -1;
    tmp->num = -1;  

    return tmp;
}

    //funcao para inserir o no na lista
NO* inserirNo(NO* cabeca, NO* no) {

    NO* tmp;

    if (cabeca != NULL) {
        tmp = cabeca;
        while (tmp->proximo != NULL) {
                tmp = tmp->proximo;
        }
        tmp->proximo = no;
    } else {
        tmp = cabeca = no;
    }
    if (no->ativo == -1) {
        no->ativo = 1;
    }
    if (no->num == -1) {
        no->num = tmp->num+1;
    }
    return cabeca;
}
    
    //funcao com o layout a ser impresso quando da impresso do registro completo
void registroLayout(NO* tmp, char* titulo) {

    printf("\n%s\n", titulo);
    printf("\tNumero: %d\n", tmp->num);
    printf("\tNome: %s\n", tmp->nome);
    printf("\tTelefone: %s\n", tmp->tel);
    printf("\tCredito: %.2lf\n\n", tmp->cred);
}

    //funcao que imprimi a lista de clientes mostrando somente numero e nome
void imprimirListaSimples(NO* no, char* verAlt) {

    NO* tmp = no;
    int x;

    if (verAlt != "ativar") {
        printf("\nLISTA DE CLIENTES ATIVOS\n");
        x = 1;
    }
    else {
        printf("\nLISTA DE CLIENTES DESATIVADOS\n");
        x = 0;
    }
    while (tmp != NULL) {
        if (tmp->ativo == x)
            printf("%d %s\n", tmp->num, tmp->nome);
        tmp = tmp->proximo;
    }
}

    //funcao que libera a memoria ao sair do programa
void deleteList(NO* cabeca) {

    NO* tmp = cabeca;

    while (cabeca != NULL) {
        free(cabeca->nome);
        cabeca = tmp->proximo;
        free(tmp);
        tmp = cabeca;
    }
}

    //funcao para determinar o caminho do executavel e buscar pelo cadastro de clientes
char* getFilePath() {
    char cwd[100];
    char* filePath;
    getcwd(cwd, sizeof(cwd));
    strcat(cwd, "/cadastro.csv");
    filePath = strdup(cwd);

    return filePath;
}

    //funcao para abir o arquivo
FILE* acessarArquivo(char* modo) {

    FILE* pFile;
    char* filePath;
    
    filePath = getFilePath();
    pFile = fopen(filePath, modo);

    if (pFile == NULL) {
        pFile = fopen(filePath, "w");
        return pFile;
        if (pFile = NULL)
            printf("Impossivel abrir o arquivo com os registros...");
    }

    free(filePath);
    return pFile;
}

    //funcao para validar se o input fornecido pelo utilizador esta dentro das opcoes disponiveis
int inputValid(char* c) {

    char one;
    int opt;

    one = c[0];
    if (isdigit(one))
        opt = atoi(&one);
    else
        opt = 5;

    return opt;
}

    //funcao utilizada para preencher o array 'no->tel'
void inserirTel(NO* no, char* tel) {

    for (int i = 0; tel[i]; i++) {
        no->tel[i] = tel[i];
    }
}

    //funcao utlizada para substituir o '.' por ','
void replaceChar(char* crt) {

    for (int i = 0; crt[i]; i++) {
        if (crt[i] == ',')
            crt[i] = '.';
    }
}

    //funcao utlizada para substituir o ',' por '.'
void replaceCharInv(float pt, char* str) {

    gcvt(pt, 6, str);
    for (int i = 0; str[i]; i++) {
        if (str[i] == '.')
            str[i] = ',';
    }
}

    //funcao que verificar se o utlizador quer imprimir um registro com detalhes
int registroCompleto(char* ver) {

    char buffer[50];

    printf("\nSelecione:");
    printf("\n1 - para %s registro", ver);
    printf("\n0 - para voltar ao menu anterior ");
    scanf(" %49s", buffer);

    return inputValid(buffer);
}

    //layout de impressao da opcao desejada e registro completo
NO* imprimirRegistro(NO* cabeca, char* titulo) {

    int reg;
    NO* tmp = cabeca;

    printf("Insira o numero do registro: ");
    scanf(" %i", &reg);

    while (tmp->num != reg && tmp->proximo != NULL) {
        tmp = tmp->proximo;
    }

    if (tmp->num != reg) {
        printf("\nRegistro inexistente na base de dados...\n\n");
        return NULL;
    }
    else if (tmp->ativo == 1 && titulo != "REATIVACAO DE CLIENTE") {
        registroLayout(tmp, titulo);
    }
    else if (tmp->ativo == 0 && titulo == "REATIVACAO DE CLIENTE") {
        registroLayout(tmp, titulo);
    }
    else {
        if (tmp->ativo == 0 && titulo != "REATIVACAO DE CLIENTE")
            printf("\nCliente com cadastro ja desativado...\n\n");
        else
            printf("\nCliente com cadastro ja ativado...\n\n");
        tmp = NULL;
    }
    return tmp; // cuidado aqui
}


NO* verAltear(NO* cabeca, char* txt) {

    int opt = 0;
    NO* tmp;
    do {
        opt = registroCompleto(txt);
        if (!opt) {
            printf("\n");
            break;
        }
        else if (opt == 1) {
            if (txt == "ver") {
                imprimirRegistro(cabeca, "REGISTRO DE CLIENTE");
                break;
            }
            else if (txt == "alterar") {
                tmp = imprimirRegistro(cabeca, "ALTERACAO DE REGISTRO");
                return tmp;
            }
            else if (txt == "desativar") {
                tmp = imprimirRegistro(cabeca, "DESATIVACAO DE CLIENTE");
                break;
            }
            else if (txt == "ativar") {
                tmp = imprimirRegistro(cabeca, "REATIVACAO DE CLIENTE");
                break;
            }
        }
        printf("\nInsira uma opcao valida...\n");
    } while (1);
    return tmp;
}

    //funcao para inserir os dados de um novo cliente
void clienteIn(NO* no, char* titulo) {

    char buffer[50];
    char tel[13];
    char cred[10];

    printf("\n%s\n", titulo);
    printf("Nome: ");
    scanf(" %[^\n]", buffer);
    no->nome = strdup(buffer);
    printf("Telefone: ");
    scanf(" %13s", tel);
    strcpy(no->tel, tel);
    printf("Credito: ");
    scanf(" %10s", cred);
    replaceChar(cred);
    no->cred = strtof(cred, NULL);
    printf("\n");
}

    //funcao para ativar/desativar cliente na base de dados
void desativarAtivar(NO* no, char* verAlt) {

    if (verAlt == "desativar")
        no->ativo = 0;
    else if (verAlt == "ativar")
        no->ativo = 1;
}

    //Esta funcao le o arquivo e o carrega na memoria utilizando para isso
    //uma single linked list.
NO* lerArquivo() {

    char buffer[50];
    char* ptr;
    NO* cabeca = NULL;
    NO* no;
    FILE* pFile;

    pFile = acessarArquivo("r");
    while (fgets(buffer, 50, pFile)) {
        no = criarNo();
        ptr = strtok(buffer, M);
        no->ativo = atoi(ptr);
        ptr = strtok(NULL, M);
        no->num = atoi(ptr);
        ptr = strtok(NULL, M);
        no->nome = strdup(ptr);
        ptr = strtok(NULL, M);
        inserirTel(no, ptr);
        ptr = strtok(NULL, M);
        replaceChar(ptr);
        no->cred = strtof(ptr, NULL);
        cabeca = inserirNo(cabeca, no);
    }
    fclose(pFile);
    return cabeca;
}

    //funcao para atualizar a base de dados todas as vezes que uma acao e performada com um dado qualquer
void escreverArquivo(NO* c) {

    FILE* pFile;
    NO* tmp = c;
    pFile = acessarArquivo("w");
    char str[10];

    while (tmp != NULL) {
        fprintf(pFile, "%d;%d;%s;%s;", tmp->ativo, tmp->num, tmp->nome, tmp->tel);
        replaceCharInv(tmp->cred, str);
        fprintf(pFile, "%s\n", str);
        tmp = tmp->proximo;
    }
    fclose(pFile);
    printf("\nRegistros atualizado com sucesso...\n\n");
}

//Esta funcao imprimi as opcoes disponiveis para o utlizador do sistema
char menuPrincipal() {

    char opcao[50];

    printf("\t***CADASTRO DE CLIENTES***\n\n");
    printf("1 - Listar Clientes\n");
    printf("2 - Inserir novo Cliente\n");
    printf("3 - Alterar Cliente Existente\n");
    printf("4 - Desativar Cliente\n");
    printf("5 - Reativar cadastro\n");
    printf("0 - Sair do Programa\n\n");
    printf("Insira uma opcao: ");
    scanf(" %49s", opcao);

    return inputValid(opcao);
}

void opcao1(NO* cabeca) {

    imprimirListaSimples(cabeca, "");
    verAltear(cabeca, "ver");
}

NO* opcao2(NO* cabeca) {

    NO* no = criarNo();
    
    clienteIn(no, "INSERIR NOVO CLIENTE");
    cabeca = inserirNo(cabeca, no);
    escreverArquivo(cabeca);

    return cabeca;
}

void opcao3(NO* cabeca) {

    int clienteNumber;
    NO* no = NULL;

    imprimirListaSimples(cabeca, "");
    no = verAltear(cabeca, "alterar");
    if (no != 0) {
        clienteIn(no, "ALTERAR CLIENTE");
        escreverArquivo(cabeca);
    }
}

void opcao45(NO* cabeca, char* verAlt) {

    NO* no;

    imprimirListaSimples(cabeca, verAlt);
    no = verAltear(cabeca, verAlt);
    if (no != 0) {
        desativarAtivar(no, verAlt);
        escreverArquivo(cabeca);
    }
}

void main() {

    int opcao;
    NO* cabeca = NULL;

    // Loop criado para manter o programa rodando, e usado um switch
    // para escolher quais funcoes chamar de acordo com a operacao desejada
    do {
        if (cabeca == NULL)
            cabeca = lerArquivo();
        opcao = menuPrincipal();
        switch (opcao) {
        case 0:
            break;
        case 1:
            opcao1(cabeca);
            break;
        case 2:
            cabeca = opcao2(cabeca);
            break;
        case 3:
            opcao3(cabeca);
            break;
        case 4:
            opcao45(cabeca, "desativar");
            break;
        case 5:
            opcao45(cabeca, "ativar");
            break;
        default:
            printf("\nOpcao invalida...\n\n");
            break;
        }
    } while ((opcao != 0));
    deleteList(cabeca);
}