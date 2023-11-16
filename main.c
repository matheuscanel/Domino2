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
        Player players[numberOfPlayers];
        for (int i = 0; i < numberOfPlayers; i++) {
            players[i].name = malloc(MAX_NAME_LENGTH * sizeof(char));
            printf("Digite o nome do jogador %d: ", i + 1);
            scanf("%s", players[i].name);
            players[i].hand = NULL;
        }


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

    // Aqui você precisa implementar a lógica para o jogador selecionar uma peça para jogar
    // Isso pode ser feito com uma função separada ou diretamente aqui.
    // Por exemplo, você poderia pedir ao jogador para escolher o índice da peça que ele deseja jogar:
    int pieceIndex;
    printf("Escolha a peca para jogar (0 a %d): ", piecesPerPlayer - 1);
    scanf("%d", &pieceIndex);
    
    
    // Agora chame a função playPiece com o jogador atual, o tabuleiro e o índice da peça selecionada
    playPiece(&players[board->playersTurn], board, pieceIndex);

    // Verifique se o jogador atual esvaziou sua mão, o que significaria que ele ganhou e o jogo terminou
    if (players[board->playersTurn].hand == NULL) {
        printf("%s ganhou o jogo!\n", players[board->playersTurn].name);
        gameOver = 1; // Isso terminará o loop do jogo
        break; // Sai do loop da partida
    }

    // Atualizar o turno para o próximo jogador
    board->playersTurn = (board->playersTurn + 1) % numberOfPlayers;
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
