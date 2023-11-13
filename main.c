#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "domino.h" 


int main(){
   
    //Menu
    int choice;

    printf("----------------------------------------\n");
    printf("Selecione a opcao desejada:\n");
    printf("(1) Jogar partida\n(2) Ranking\n(3) Fechar\n");
    printf("----------------------------------------\n");
    scanf("%d", &choice);
    

    if(choice == 1){
        int numberOfPlayers;
        printf("Quantos jogadores irao jogar?");
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

