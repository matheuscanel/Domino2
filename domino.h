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
    int score;
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
void printPlayerInfo(Player *player);
void distributePieces(Node** stock, Player* players, int numberOfPlayers, int piecesPerPlayer);
int whoStarts(Player *players, int numberOfPlayers);
void printBoard(const Board *board);
int canPlay(Domino piece, Node *board);
void playPiece(Player *player, Board *board, int pieceIndex);
void bubbleSortPlayers(Player players[], int count);

#endif
