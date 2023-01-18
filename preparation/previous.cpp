#include <cmath>
#include <fstream>
#include <iostream>
#include <vector>

using Tiles = std::vector<int>; // 4 ints
using Board = std::vector<Tiles>; // n * n tiles
using Rows = std::vector<Tiles>; // n tiles
using Columns = std::vector<Tiles>; // n tiles

Board readBoard(std::ifstream &in)
{
    Board board;
    std::string line;
    while (std::getline(in, line))
    {
        Tiles tile;
        for (int i = 0; i < 4; ++i)
        {
            tile.push_back(line[i] - '0');
        }
        board.push_back(tile);
    }
    return board;
}

void printBoard(std::vector<std::vector<int>> &board)
{
    int n = std::sqrt(board.size());

    // Top separator
    std::cout << "+";
    for (int i = 0; i < n; ++i)
    {
        std::cout << "-----+";
    }
    std::cout << std::endl;

    for (int i = 0; i < n; ++i)
    {
        // North border
        std::cout << "|";
        for (int j = 0; j < n; ++j)
        {
            std::cout << "  " << board[i * n + j][0] << "  |";
        }
        std::cout << std::endl;

        // West and East borders
        std::cout << "|";
        for (int j = 0; j < n; ++j)
        {
            std::cout << " " << board[i * n + j][1] << " "
                      << board[i * n + j][2] << " |";
        }
        std::cout << std::endl;

        // South border
        std::cout << "|";
        for (int j = 0; j < n; ++j)
        {
            std::cout << "  " << board[i * n + j][3] << "  |";
        }
        std::cout << std::endl;
        std::cout << "+";

        // Row separator
        for (int j = 0; j < n; ++j)
        {
            std::cout << "-----+";
        }
        std::cout << std::endl;
    }
}

void writeBoard(std::ofstream &out, Board &board)
{
    int n = std::sqrt(board.size());
    for (int i = 0; i < n * n; ++i)
    {
        for (int k = 0; k < 4; ++k)
        {
            out << board[i][k];
        }
        out << std::endl;
    }
}

int evaluate(Board &board)
{
    int score = 0;
    int n = std::sqrt(board.size());

    // North and south borders
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            if (board[i * n + j][3] != board[(i + 1) * n + j][0])
            {
                score += 1;
            }
        }
    }

    // West and east borders
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n - 1; ++j)
        {
            if (board[i * n + j][2] != board[i * n + j + 1][1])
            {
                score += 1;
            }
        }
    }
    return score;
}

Rows getRow(Board &board, int i)
{
    int n = std::sqrt(board.size());
    Rows row;
    for (int j = 0; j < n; ++j)
    {
        row.push_back(board[i * n + j]);
    }
    return row;
}

Columns getColumn(Board &board, int i)
{
    int n = std::sqrt(board.size());
    Columns column;
    for (int j = 0; j < n; ++j)
    {
        column.push_back(board[j * n + i]);
    }
    return column;
}

Board swapRows(Board board, int i, int j)
{
    int n = std::sqrt(board.size());
    std::vector<std::vector<int>> temp;
    for (int k = 0; k < n; ++k)
    {
        temp.push_back(board[i * n + k]);
    }
    for (int k = 0; k < n; ++k)
    {
        board[i * n + k] = board[j * n + k];
    }
    for (int k = 0; k < n; ++k)
    {
        board[j * n + k] = temp[k];
    }
    return board;
}

Board swapColumns(Board board, int i, int j)
{
    int n = std::sqrt(board.size());
    for (int k = 0; k < n; ++k)
    {
        auto temp = board[k * n + i];
        board[k * n + i] = board[k * n + j];
        board[k * n + j] = temp;
    }
    return board;
}

void swapTiles(Board board, int i, int j)
{
    int n = std::sqrt(board.size());
    auto begin = board.begin();
    std::iter_swap(begin + i, begin + j);
}

Board solve(Board &board)
{
    // Use a Metropolis algorithm to solve the puzzle
    int n = std::sqrt(board.size());
    int score = evaluate(board);
    int bestScore = score;
    Board bestBoard = board;
    int iterations = 0;

    while (score > 0)
    {
        int i = rand() % n;
        int j = rand() % n;

        swapTiles(board, i, j);
        score = evaluate(board);

        if (score < bestScore)
        {
            bestScore = score;
            bestBoard = board;
        }
        else
        {
            swapTiles(board, i, j);
        }
        iterations += 1;
    }
    std::cout << "Iterations: " << iterations << std::endl;
    return bestBoard;
}

int main(int argc, char *argv[])
{
    std::ifstream in(argv[1]);
    std::ofstream out(argv[2]);
    int n = argv[1][12] - '0';
    Board board(n * n, std::vector<int>(4, 0));

    board = readBoard(in);
    auto solution = solve(board);

    writeBoard(out, solution);

    return 0;
}