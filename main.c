#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "domino.h"

int main() {
    
    printf("Seja bem vindo ao jogo de domino em C\n");

    int numberOfPlayers = 4;
    // criar jogadores
    Player players[numberOfPlayers];
    for (int i = 0; i < numberOfPlayers; i++) {
        players[i].name = malloc(MAX_NAME_LENGTH * sizeof(char));
        printf("Digite o nome do jogador %d: ", i + 1);
        scanf("%s", players[i].name);
        players[i].hand = NULL;
        players[i].score = 0;
    }
   
   while(1){
    //Menu
    int choice;

    printf("----------------------------------------\n");
    printf("Selecione a opcao desejada:\n");
    printf("(1) Jogar partida\n(2) Ranking\n(3) Fechar\n");
    printf("----------------------------------------\n");
    scanf("%d", &choice);
    
    if (choice == 1) {

        int numberOfPlayers = 4;

        Board *board = createBoard(numberOfPlayers); // criar o board

        // criar peças
        Node *stock = NULL;
        generatePieces(&stock);
        printStock(stock);

        // embaralhar peças
        shufflePieces(&stock);
        printStock(stock);
        
        // criar jogadores
        // Player players[numberOfPlayers];
        // for (int i = 0; i < numberOfPlayers; i++) {
        //     players[i].name = malloc(MAX_NAME_LENGTH * sizeof(char));
        //     printf("Digite o nome do jogador %d: ", i + 1);
        //     scanf("%s", players[i].name);
        //     players[i].hand = NULL;
        // }


        // distribuir peças
        int piecesPerPlayer = 7; 
        distributePieces(&stock, players, numberOfPlayers, piecesPerPlayer);
        for (int j = 0; j < numberOfPlayers; j++) {
            printPlayerInfo(&players[j]);
        }

        // iniciar partida e lógica do jogo

        // função whoStarts
        int startingPlayerIndex = whoStarts(players, numberOfPlayers);
        board->playersTurn = startingPlayerIndex;

        // exibir board e mão do jogador da vez
        int gameOver = 0;
        printf("\nJogo iniciado\n");
        while (gameOver < numberOfPlayers) { // loop da partida
    
        printBoard(board);

        printf("Jogador da vez: %s\n", players[board->playersTurn].name);
        printPlayerInfo(&players[board->playersTurn]);

        //escolha de peça
        int pieceIndex;
        printf("Escolha a peca para jogar (0 a %d): ", piecesPerPlayer - 1);
        scanf("%d", &pieceIndex);
    
    
        //Jogar peça
        playPiece(&players[board->playersTurn], board, pieceIndex);

        // Verifique se o jogador atual esvaziou sua mão, o que significaria que ele ganhou e o jogo terminou
        if (players[board->playersTurn].hand == NULL) {
            printf("\n%s ganhou o jogo!\n", players[board->playersTurn].name);
            gameOver = 1; // Isso terminará o loop do jogo
            players[board->playersTurn].score++;
            //limpeza da mão
            for (int i = 0; i < numberOfPlayers; i++) {
                Node* curr = players[i].hand; //curr abrevia current
                while (curr != NULL) {
                Node* next = curr->next; // Presume-se que seu Node tenha um ponteiro 'next'
                    free(curr); // Libera a peça atual
                    curr = next; // Avança para a próxima peça
                }
                
                players[i].hand = NULL; // Define a mão do jogador para NULL após limpar
            }
            break; // Sai do loop da partida
        }

    // Atualizar o turno para o próximo jogador
        board->playersTurn = (board->playersTurn + 1) % numberOfPlayers;
    }

    } else if (choice == 2) {
        bubbleSortPlayers(players, numberOfPlayers); // Ordena os jogadores pelo score
        printf("Ranking dos jogadores:\n");
        for (int i = 0; i < numberOfPlayers; i++) {
            printf("%dº Lugar: %s com %d pontos\n", i + 1, players[i].name, players[i].score);
        }
        

    } else if (choice == 3) {
        printf("Fechar programa\n");
        for (int i = 0; i < numberOfPlayers; i++) {

            // Libera o nome do jogador
            free(players[i].name); 

            // Libera a mão do jogador
            Node* curr = players[i].hand;

            while (curr != NULL) {
                Node* next = curr->next;
                free(curr);
                curr = next;
            }
    }
           
        break;
    } else {
        printf("Opcao invalida, tente novamente\n");
        
    }
   
   }

    return 0;
}
