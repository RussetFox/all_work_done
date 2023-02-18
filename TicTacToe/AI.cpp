#include "AI.h"

int player, opponent;
void setDifficulty(int difficulty) {
    if (difficulty == 1) {
        player = 3;
        opponent = 2;
    } else if (difficulty == 2) {
        player = 2;
        opponent = 3;
    }
}

bool isMovesLeft(int board[3][3])
{
    for (int i = 0; i<3; i++)
        for (int j = 0; j<3; j++)
            if (board[i][j]==0)
                return true;
    return false;
}

int evaluate(int b[3][3]){
        //Sprawdzenie rzędów w celu ustalenia czy któraś z figur wygrywa
        for (int row = 0; row<3; row++)
        {
            if (b[row][0]==b[row][1] &&
                b[row][1]==b[row][2])
            {
                if (b[row][0]==player)
                    return +10;
                else if (b[row][0]==opponent)
                    return -10;
            }
        }

        // Sprawdzenie kolumn w celu ustalenia czy któraś z figur wygrywa
        for (int col = 0; col<3; col++)
        {
            if (b[0][col]==b[1][col] &&
                b[1][col]==b[2][col])
            {
                if (b[0][col]==player)
                    return +10;

                else if (b[0][col]==opponent)
                    return -10;
            }
        }

        // Sprawdzenie przekątnych w celu ustalenia czy któraś z figur wygrywa
        if (b[0][0]==b[1][1] && b[1][1]==b[2][2])
        {
            if (b[0][0]==player)
                return +10;
            else if (b[0][0]==opponent)
                return -10;
        }

        if (b[0][2]==b[1][1] && b[1][1]==b[2][0])
        {
            if (b[0][2]==player)
                return +10;
            else if (b[0][2]==opponent)
                return -10;
        }

        // Jeśli nikt nie wygrał, to zwróć 0
        return 0;
};

int minimax(int board[3][3], int depth, bool isMax)
{
    int score = evaluate(board);

    // Jeśli wygrał maksymalny, zwraca punktację
    if (score == 10)
        return score;

    // Jeśli wygrał minimalny, zwraca -punktację
    if (score == -10)
        return score;

    // Jeśli nie ma ruchów i brak zwycięzcy - remis
    if (isMovesLeft(board)==false)
        return 0;

    // Jeśli ruch maksymalnego
    if (isMax)
    {
        int best = -1000;

        // Sprawdza komórki
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Sprawdzenie czy pusta
                if (board[i][j]==0)
                {
                    // Wykonaj ruchr
                    board[i][j] = player;

                    // Rekursywne wywołanie funkcji minimax
                    best = std::max( best, minimax(board, depth+1, !isMax) );

                    // Cofnij ruch
                    board[i][j] = 0;
                }
            }
        }
        return best;
    }

        // Jeśli ruch maksymalnego
    else
    {
        int best = 1000;

        // Sprawdza komórki
        for (int i = 0; i<3; i++)
        {
            for (int j = 0; j<3; j++)
            {
                // Sprawdzenie czy pusta
                if (board[i][j]==0)
                {
                    // Wykonaj ruch
                    board[i][j] = opponent;

                    // Rekursywne wywołanie funkcji minimax
                    best = std::min(best, minimax(board, depth+1, !isMax));

                    // Cofnij ruch
                    board[i][j] = 0;
                }
            }
        }
        return best;
    }
}

Move findBestMove(int board[3][3])
{
    int bestVal = -1000;
    Move bestMove;
    bestMove.row = -1;
    bestMove.col = -1;
    // Sprawdza komórki, aby znaleźć najlepszy ruch dla wszystkich pustych komórek.
    //Zwraca komórkę z najlepszym wynikiem
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            // Sprawdzenie czy pusta
            if (board[i][j]==0)
            {
                // Wykonaj ruch
                board[i][j] = player;

                //zwróc ewaluacje wyniku dla ruchu
                int moveVal = minimax(board, 0, false);

                // Cofnij ruch
                board[i][j] = 0;

                //Jesli wartość obecnego ruchu > wartość najlepszego ruchu
                //to zaktualizuj najlepszy ruch
                if (moveVal > bestVal)
                {
                    bestMove.row = i;
                    bestMove.col = j;
                    bestVal = moveVal;
                }
            }
        }
    }
    return bestMove;
}