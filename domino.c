#include "domino.h"

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
    printf("Pecas de domino disponiveis:\n");
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

void printPlayerInfo(Player *player) {
    printf("Jogador: %s\n", player->name);
    printf("Mao: ");

    Node *handNode = player->hand;

    if (handNode == NULL) {
        printf("Vazia\n");
    } else {
        while (handNode != NULL) {
            printf("[%d|%d] ", handNode->values.left, handNode->values.right);
            handNode = handNode->next;
        }
        printf("\n");
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
    
int whoStarts(Player *players, int numberOfPlayers) {
    int startingPlayer = -1;  // Índice do jogador que começa
    int highestValue = -1;    // Valor da maior soma de extremidades encontrada até agora

    for (int i = 0; i < numberOfPlayers; i++) {
        Node *handNode = players[i].hand;
        
        // Iterar pelas peças na mão do jogador
        while (handNode != NULL) {
            int pieceValue = handNode->values.left + handNode->values.right;

            if (pieceValue > highestValue || (pieceValue == highestValue && 
                (handNode->values.left == handNode->values.right ||
                 handNode->values.left > handNode->values.right))) {
                highestValue = pieceValue;
                startingPlayer = i;  // Este jogador começa
            }

            handNode = handNode->next;
        }
    }

    return startingPlayer;  // Retorna o índice do jogador que começa
}

// Função para imprimir o estado atual do tabuleiro
void printBoard(const Board *board) {
    Node *currentPiece = board->game;

    
    printf("\n---------------------------------------------\nEstado atual do tabuleiro:\n\n");

    while (currentPiece != NULL) {
        printf("[%d|%d] ", currentPiece->values.left, currentPiece->values.right);
        currentPiece = currentPiece->next;
    }

    printf("\n\n---------------------------------------------\n");
}

int canPlay(Domino piece, Node *board) {
    if (board == NULL) {
        // Se o tabuleiro estiver vazio, qualquer peça pode ser jogada
        return 1;
    }

    // Checa as extremidades do tabuleiro
    Node *leftEnd = board;
    while (leftEnd->prev != NULL) {
        leftEnd = leftEnd->prev;
    }

    Node *rightEnd = board;
    while (rightEnd->next != NULL) {
        rightEnd = rightEnd->next;
    }

    // Se a peça encaixa em alguma das extremidades, a jogada é válida
    if (piece.left == leftEnd->values.left || piece.right == leftEnd->values.left ||
        piece.left == rightEnd->values.right || piece.right == rightEnd->values.right) {
        return 1;
    }

    return 0;
}

void playPiece(Player *player, Board *board, int pieceIndex) {
    // Encontrar a peça na mão do jogador
    Node *selectedPieceNode = player->hand;
    for (int i = 0; i < pieceIndex && selectedPieceNode != NULL; i++) {
        selectedPieceNode = selectedPieceNode->next;
    }

    if (selectedPieceNode == NULL) {
        printf("Peca invalida\n");
        return;
    }

    Domino selectedPiece = selectedPieceNode->values;

    // Verificar se a peça pode ser jogada
    if (canPlay(selectedPiece, board->game)) {
        // Remover a peça da mão do jogador
        if (selectedPieceNode->prev != NULL) {
            selectedPieceNode->prev->next = selectedPieceNode->next;
        }
        if (selectedPieceNode->next != NULL) {
            selectedPieceNode->next->prev = selectedPieceNode->prev;
        }
        if (player->hand == selectedPieceNode) {
            player->hand = selectedPieceNode->next;
        }

        // Colocar a peça no tabuleiro
        Node *newPieceNode = (Node*) malloc(sizeof(Node));
        newPieceNode->values = selectedPiece;
        newPieceNode->next = NULL;
        newPieceNode->prev = NULL;

        if (board->game == NULL) {
            // Se o tabuleiro estiver vazio, a peça se torna o início do jogo
            board->game = newPieceNode;
        } else {
            // Caso contrário, encontre a extremidade correta e adicione a peça
            Node *end = board->game;
            while (end->next != NULL) end = end->next; // Encontrar a extremidade direita

            // Verificar se deve ser colocado à esquerda ou à direita
            if (selectedPiece.right == end->values.right) {
                // Inverter a peça antes de colocar
                int temp = newPieceNode->values.left;
                newPieceNode->values.left = newPieceNode->values.right;
                newPieceNode->values.right = temp;

                // Colocar no lado direito
                end->next = newPieceNode;
                newPieceNode->prev = end;
            } else if (selectedPiece.left == end->values.right) {
                // Colocar no lado direito
                end->next = newPieceNode;
                newPieceNode->prev = end;
            } else {
                // O mesmo processo para o lado esquerdo, se necessário
                end = board->game;
                while (end->prev != NULL) end = end->prev; // Encontrar a extremidade esquerda

                if (selectedPiece.left == end->values.left) {
                    // Inverter a peça antes de colocar
                    int temp = newPieceNode->values.left;
                    newPieceNode->values.left = newPieceNode->values.right;
                    newPieceNode->values.right = temp;

                    // Colocar no lado esquerdo
                    newPieceNode->next = end;
                    end->prev = newPieceNode;
                    board->game = newPieceNode; // Atualizar a cabeça do tabuleiro
                } else if (selectedPiece.right == end->values.left) {
                    // Colocar no lado esquerdo
                    newPieceNode->next = end;
                    end->prev = newPieceNode;
                    board->game = newPieceNode; // Atualizar a cabeça do tabuleiro
                }
            }
        }

        printf("Jogada valida. Peca [%d|%d] jogada no tabuleiro.\n",
               selectedPiece.left, selectedPiece.right);
    } else {
        printf("Jogada invalida. A peca [%d|%d] não pode ser jogada.\n",
               selectedPiece.left, selectedPiece.right);
    }

    // Liberação do nó da peça jogada é removida daqui, pois agora ela faz parte do tabuleiro
}

void bubbleSortPlayers(Player players[], int count) {
    int i, j;
    for (i = 0; i < count - 1; i++) {
        for (j = 0; j < count - i - 1; j++) {
            if (players[j].score < players[j + 1].score) {
                // Troca os jogadores
                Player temp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = temp;
            }
        }
    }
}
