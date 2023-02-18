#include "gameHandling.h"

gameHandling:: gameHandling() {
    gameBoard = new int *[3];
    for (int i = 0; i < 3; i++) {
        gameBoard[i] = new int[3];
        for (int j = 0; j < 3; j++) {
            gameBoard[i][j] = 0;
        }
    }
    helparray = new int[9];
    for (int i = 0; i < 9; i++) {
        helparray[i] = 0;
    }
    this -> winner = 0;
    turnX = false;
}

gameHandling:: ~gameHandling() {
    for (int i = 0; i < 3; i++) {
        delete[] gameBoard[i];
    }
    delete[] gameBoard;
    delete[] helparray;
}


//__________Public functions__________
void gameHandling::setTurn() {
    turnX = !turnX;
}

int** gameHandling::getFullGameBoard() {
    return gameBoard;
}

bool gameHandling::getTurn() {
    return turnX;
}

void gameHandling::checkForResult() {
    for (int i = 0; i < 9; i++)
    {helparray[i] = 1;}
    int h = 2;
    for (int i = 0; i < 3; i++) {
        helparray[0] *= gameBoard[0][i];
        helparray[1] *= gameBoard[1][i];
        helparray[2] *= gameBoard[2][i];
        helparray[3] *= gameBoard[i][0];
        helparray[4] *= gameBoard[i][1];
        helparray[5] *= gameBoard[i][2];
        helparray[6] *= gameBoard[i][i];
        helparray[7] *= gameBoard[h][i];
        h--;
    }
    for (int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            helparray[8] *= gameBoard[i][j];
        }
    }
    for (int i = 0; i<8; i++) {
        if (helparray[i] == 8) {
            winner = 1;
            break;
        } else if (helparray[i] == 27) {
            winner = 2;
            break;
        } else if (helparray[8] != 0 && helparray[3] != 27 && helparray[3] != 8 && helparray[4] != 27 && helparray[4] != 8 && helparray[5] != 27 && helparray[5] != 8 &&
                   helparray[6] != 27 && helparray[6] != 8 && helparray[7] != 27 && helparray[7] != 8) {
            winner = 3;
        }
    }
}

int gameHandling::getResult() {
    checkForResult();
    return winner;
}

int gameHandling::getGameboard(int row, int column) {
    return gameBoard[row][column];
}

void gameHandling::setGameboard(int row, int column, int value) {
    gameBoard[row][column] = value;
}

void gameHandling::resetStats() {
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            gameBoard[i][j] = 0;
        }
    }
    for (int i = 0; i < 9; i++)
    {
        helparray[i] = 0;
    }
    winner = 0;
    turnX = false;
}
