#ifndef TICTACTOE_AI_H
#define TICTACTOE_AI_H

#include <iostream>

struct Move
{
    int row, col;
};

void setDifficulty(int difficulty);

//Funkcja zwracająca fałsz jeśli nie ma możliwości wykonania ruchu, prawdę jeśli jest
bool isMovesLeft(int board[3][3]);

// Funkcja ewaluacji ruchu
int evaluate(int b[3][3]);

//Funckja minimax szacująca wszystkie możliwe ruchy i zwracająca wartość najlepszego
int minimax(int board[3][3], int depth, bool isMax);

//Funkcja zwracająca najlepszy ruch
Move findBestMove(int board[3][3]);

#endif //TICTACTOE_AI_H
