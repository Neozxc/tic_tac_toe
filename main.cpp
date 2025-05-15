#include <iostream>
#include <vector>
#include <limits>
#include <memory>

const char PLAYER = 'X';
const char AI = 'O';
const char EMPTY = ' ';

class Board
{
    std::vector<char> cells;

public:
    Board() : cells(9, EMPTY) {}

    void display() const
    {
        for (int i = 0; i < 9; i++)
        {
            std::cout << cells[i];
            if ((i + 1) % 3 == 0)
            {
                std::cout << "\n";
            }
            else
            {
                std::cout << " | ";
            }
        }
        std::cout << "\n";
    }

    bool makeMove(int index, char player)
    {
        if (index < 0 || index >= 9 || cells[index] != EMPTY)
            return false;

        cells[index] = player;
        return true;
    }

    void undoMove(int index)
    {
        if (index >= 0 && index < 9)
            cells[index] = EMPTY;
    }

    bool isFull() const
    {
        for (char c : cells)
        {
            if (c == EMPTY)
                return false;
        }

        return true;
    }

    bool hasWinner(char player) const
    {
        const int winPatterns[8][3] = {
            {0, 1, 2},
            {3, 4, 5},
            {6, 7, 8},
            {0, 3, 6},
            {1, 4, 7},
            {2, 5, 8},
            {0, 4, 8},
            {2, 4, 6}};

        for (auto &pattern : winPatterns)
        {
            if (cells[pattern[0]] == player && cells[pattern[1]] == player && cells[pattern[2]] == player)
                return true;
        }

        return false;
    }

    std::vector<int> availableMoves() const
    {
        std::vector<int> moves;

        for (int i = 0; i < 9; i++)
        {
            if (cells[i] == EMPTY)
            {
                moves.push_back(i);
            }
        }

        return moves;
    }
};

int minimax(Board &board, bool isMaximizing)
{
    if (board.hasWinner(AI))
        return 1;
    if (board.hasWinner(PLAYER))
        return -1;
    if (board.isFull())
        return 0;

    int bestScore = isMaximizing ? -1000 : 1000;

    for (int move : board.availableMoves())
    {
        board.makeMove(move, isMaximizing ? AI : PLAYER);
        int score = minimax(board, !isMaximizing);
        board.undoMove(move);

        if (isMaximizing)
        {
            bestScore = std::max(score, bestScore);
        }
        else
        {
            bestScore = std::min(score, bestScore);
        }
    }

    return bestScore;
}

int bestMove(Board &board)
{
    int bestScore = -1000;
    int move = -1;

    for (int i : board.availableMoves())
    {
        board.makeMove(i, AI);
        int score = minimax(board, false);
        board.undoMove(i);

        if (score > bestScore)
        {
            bestScore = score;
            move = i;
        }
    }

    return move;
}

int main()
{
    Board board;
    int move;

    std::cout << "Tic Tac Toe - You (X) vs (AI) (0) \n";

    while (true)
    {
        std::cout << "Your move (0-0)";
        std::cin >> move;

        if (!board.makeMove(move, PLAYER))
        {
            std::cout << "Invalid move.\n";
            continue;
        }

        if (board.hasWinner(PLAYER))
        {
            std::cout << "You win!";
            break;
        }

        if (board.isFull())
        {
            std::cout << "Draw!";
            break;
        }

        int aiMove = bestMove(board);
        board.makeMove(aiMove, AI);
        std::cout << "AI move: " << aiMove << "\n";

        board.display();

        if (board.hasWinner(AI))
        {
            std::cout << "AI wins!\n";
        }

        if (board.isFull())
        {
            std::cout << "Draw!";
        }
    }

    return 0;
}
