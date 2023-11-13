#ifndef DOMINO_H
#define DOMINO_H

#include "stdio.h"
#include "stdlib.h"
#include "time.h"

#define MAX_NAME_LENGTH 100

typedef struct Domino {
    int right;
    int left;
} Domino;

typedef struct Node {
    Domino values;
    struct Node* next;
    struct Node* prev;
} Node;

typedef struct Player {
    Node* hand;
    char* name;
} Player;

typedef struct Board {
    Node* game;
    int playersTurn;
    int NumberOfPlayers;
} Board;

Board* createBoard(int N);
void generatePieces(Node** stock);
void printStock(Node* stock);
void shufflePieces(Node** stock);
void printPlayersInfos(const Player* players, int numberOfPlayers);
void distributePieces(Node** stock, Player* players, int numberOfPlayers, int piecesPerPlayer);

#endif
