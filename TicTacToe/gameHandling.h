
#ifndef TICTACTOE_GAMEHANDLING_H
#define TICTACTOE_GAMEHANDLING_H

#include "AI.h"

class gameHandling {
    int** gameBoard;
    int* helparray;
    int winner;
    bool turnX;

    void checkForResult();
public:
    gameHandling();
    ~gameHandling();
    void setTurn();
    bool getTurn();
    int getResult();
    int** getFullGameBoard();
    int getGameboard(int row, int column);
    void setGameboard(int row, int column, int value);
    void resetStats();

};

#endif //TICTACTOE_GAMEHANDLING_H
