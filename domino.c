#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_NAME_LENGTH 100

typedef struct Domino{
    int right;
    int left;
}Domino;

typedef struct Node{
    Domino values;
    struct Node *next;
    struct Node *prev;
}Node;

typedef struct Player{
    Node *hand;
    char *name;  
}Player;

typedef struct Board{
    Node *game;
    int playersTurn;
    int NumberOfPlayers;
}Board;

Board *createBoard(int N);
void generatePieces(Node **stock);
void printStock(Node *stock);
void shufflePieces(Node **stock);
void printPlayersInfos(const Player *players, int numberOfPlayers);
void distributePieces(Node **stock, Player *players, int numberOfPlayers, int piecesPerPlayer);



int main(){
   
    //Menu
    int choice;

    printf("----------------------------------------\n");
    printf("Selecione a opcao desejada:\n");
    printf("(1) Jogar partida\n (2)Ranking\n (3)fechar\n");
    printf("----------------------------------------\n");
    scanf("%d", &choice);
    

    if(choice == 1){
        int numberOfPlayers;
        printf("Quantos jogadores irão jogar?");
        scanf("%d", &numberOfPlayers);//perguntar o numero de jogadores

        Board *board = createBoard(numberOfPlayers); //criar o board

        //criar peças

        Node *stock=NULL;
        generatePieces(&stock);
        printStock(stock);

        //embaralhar peças
        shufflePieces(&stock);
        printStock(stock);
        
        //criar jogadores
        Player players[numberOfPlayers];
        for(int i=0; i<numberOfPlayers; i++){

            players[i].name = malloc(MAX_NAME_LENGTH * sizeof(char));
            printf("Digite o nome do jogador %d ", i+1);
            scanf("%s", players[i].name);
            players[i].hand = NULL;

        }

        printPlayersInfos(players, numberOfPlayers);

        //destribuir peças
        int piecesPerPlayer = 7;// isso se o maximo forem 4(sujeito a ajuste)
        distributePieces(&stock,players,numberOfPlayers, piecesPerPlayer);
        printPlayersInfos(players, numberOfPlayers);
        printStock(stock);
        

        //iniciar partida e logica do jogo
        printf("Logica do jogo");
    }
    else if(choice == 2){
        printf("Ranking dos jogadores");
    }
    else if (choice == 3) {
        printf("Fechar programa");
        return 0;    
    }
    else{
        printf("Opcao invalida, tente novamente");
    }


    return 0;
}

Board *createBoard(int N){
    Board *board = (Board*) malloc(sizeof(Board));

    board->game = NULL;  // Inicialmente, não há peças no tabuleiro
    board->playersTurn = 0;  // O primeiro jogador (índice 0) começa
    board->NumberOfPlayers = N;  // Define o número de jogadores

    return board;

}

void generatePieces(Node **stock){
    for (int left = 0; left <= 6; left++) {
        for (int right = left; right <= 6; right++) {
            // Alocar memória para um novo nó
            Node *newNode = (Node*) malloc(sizeof(Node));

            // Configurar os valores da peça de dominó
            newNode->values.left = left;
            newNode->values.right = right;
            newNode->next = NULL;
            newNode->prev = NULL;

            // Anexar o novo nó à lista de peças (stock)
            if (*stock == NULL) {
                // Primeira peça a ser inserida
                *stock = newNode;
            } else {
                // Anexar ao final da lista
                Node *current = *stock;
                while (current->next != NULL) {
                    current = current->next;
                }
                current->next = newNode;
                newNode->prev = current;
            }
        }
    }
}

void printStock(Node *stock) {
    printf("Peças de domino disponiveis:\n");
    while (stock != NULL) {
        printf("[%d|%d] ", stock->values.left, stock->values.right);
        stock = stock->next;
    }
    printf("\n");
}

void shufflePieces(Node **stock){

    int size = 0;
    Node *current = *stock;
    while (current != NULL) {
        size++;
        current = current->next;
    }

    srand((int)time(NULL)); // Inicializar o gerador de números aleatórios
    for (int i = 0; i < size - 1; i++) {
        int j = i + rand() % (size - i); // Escolher uma posição aleatória para trocar

        // Encontrar os nós nas posições i e j
        Node *node_i = *stock;
        Node *node_j = *stock;
        for (int k = 0; k < i; k++)
            node_i = node_i->next;
            
        for (int k = 0; k < j; k++) 
            node_j = node_j->next;

        // Trocar os valores dos nós i e j
        Domino temp = node_i->values;
        node_i->values = node_j->values;
        node_j->values = temp;
    }
}

void printPlayersInfos(const Player *players, int numberOfPlayers){

    printf("Informacoes dos jogadores:\n");
    for (int i = 0; i < numberOfPlayers; i++) {

        printf("\nJogador %d: %s\n", i + 1, players[i].name);
        printf("Mao: ");
        Node *handNode = players[i].hand;

        if (handNode == NULL) {
            printf("Vazia\n");
        } else {
            // Percorrer a mão do jogador e imprimir as peças
            while (handNode != NULL) {
                printf("[%d|%d] ", handNode->values.left, handNode->values.right);
                handNode = handNode->next;
            }
            printf("\n");
        }
    }
}
    
void distributePieces(Node **stock, Player *players, int numberOfPlayers, int piecesPerPlayer) {
    for (int i = 0; i < numberOfPlayers; i++) {
        for (int j = 0; j < piecesPerPlayer; j++) {

            // Remover a peça do stock
            Node *piece = *stock;
            *stock = (*stock)->next;

            if (*stock != NULL) {
                (*stock)->prev = NULL;
            }

            // Limpar os ponteiros de 'piece' para não apontar mais para o stock
            piece->next = NULL;
            piece->prev = NULL;

            // Adicionar a peça à mão do jogador
            if (players[i].hand == NULL) {
                players[i].hand = piece;
            } else {
                // Encontrar o final da mão do jogador
                Node *end = players[i].hand;
                while (end->next != NULL) {
                    end = end->next;
                }
                end->next = piece;
                piece->prev = end;
            }
        }
    }
}
    