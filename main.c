#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "domino.h"

int main() {
   
    //Menu
    int choice;

    printf("----------------------------------------\n");
    printf("Selecione a opcao desejada:\n");
    printf("(1) Jogar partida\n(2) Ranking\n(3) Fechar\n");
    printf("----------------------------------------\n");
    scanf("%d", &choice);
    
    if (choice == 1) {
        int numberOfPlayers;
        printf("Quantos jogadores irao jogar?");
        scanf("%d", &numberOfPlayers); // perguntar o numero de jogadores

        Board *board = createBoard(numberOfPlayers); // criar o board

        // criar peças
        Node *stock = NULL;
        generatePieces(&stock);
        printStock(stock);

        // embaralhar peças
        shufflePieces(&stock);
        printStock(stock);
        
        // criar jogadores
        Player players[numberOfPlayers];
        for (int i = 0; i < numberOfPlayers; i++) {
            players[i].name = malloc(MAX_NAME_LENGTH * sizeof(char));
            printf("Digite o nome do jogador %d: ", i + 1);
            scanf("%s", players[i].name);
            players[i].hand = NULL;
        }


        // distribuir peças
        int piecesPerPlayer = 7; // isso se o máximo forem 4 (sujeito a ajuste)
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
        printf("\nJogo iniciado");
        while (gameOver<numberOfPlayers) { // loop da partida
            
            printBoard(board);

            printf("Jogador da vez: %s\n", players[board->playersTurn].name);
            printPlayerInfo(&players[board->playersTurn]);

            // Implemente a lógica do jogo (jogada válida, puxar/passar, etc.)
            // Você deve implementar a lógica do jogo aqui para permitir que os jogadores façam jogadas válidas,
            // puxar peças, passar o turno, determinar o fim do jogo, etc.

            // Defina a condição de fim de jogo (por exemplo, quando um jogador esvaziar sua mão)
            // gameOver = ?;

            // Atualizar o turno para o próximo jogador
            board->playersTurn = (board->playersTurn + 1) % numberOfPlayers;
            gameOver++;
        }
    } else if (choice == 2) {
        printf("Ranking dos jogadores\n");
        // Implemente a funcionalidade do ranking aqui, se necessário.
    } else if (choice == 3) {
        printf("Fechar programa\n");
        return 0;    
    } else {
        printf("Opcao invalida, tente novamente\n");
    }

    return 0;
}
