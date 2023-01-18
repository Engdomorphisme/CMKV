#include <cmath>
#include <experimental/random>
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

Board solve(Board &board)
{
    // TODO: Solve the board and return the solution board (or nullptr if no
    // solution exists

    // Use a Metropolis-Hastings algorithm to solve the board
    // https://en.wikipedia.org/wiki/Metropolis%E2%80%93Hastings_algorithm

    // 1. Generate a random solution
    // 2. Evaluate the solution
    // 3. Generate a random neighbor
    // 4. Evaluate the neighbor
    // 5. If the neighbor is better, accept it
    // 6. If the neighbor is worse, accept it with probability e^(-delta /
    // T)
    // 7. Repeat until the solution is good enough

    int size = board.size();
    int n = std::sqrt(size);
    int score = evaluate(board);
    int bestScore = score;
    Board bestBoard = board;
    int iterations = 0;
    int maxIterations = 1000000;
    srand(time(nullptr));

    while (score > 0)
    {
        int i = std::experimental::randint(0, size - 1);
        int j = std::experimental::randint(0, size - 1);
        if (i == j)
        {
            j = (j + 1) % size;
        }

        Tiles temp = board[i];
        board[i] = board[j];
        board[j] = temp;

        // Evaluate the neighbor
        score = evaluate(board);
        // If the neighbor is better, accept it
        if (score < bestScore)
        {
            bestScore = score;
            bestBoard = board;
        }
        // If the neighbor is worse, accept it with probability e^(-delta /
        // T)
        else
        {
            double T = 1.0 / (1.0 + iterations);
            double delta = score - bestScore;
            double p = exp(-delta / T);
            if (p < (double)rand() / RAND_MAX)
            {
                bestScore = score;
                bestBoard = board;
            }
            else // Reject the neighbor
            {
                board = bestBoard;
            }
        }

        iterations += 1;
    }
    return bestBoard;
}

int main(int argc, char *argv[])
{
    if (argc == 3 or argc == 4)
    {
        std::ifstream in(argv[1]);
        std::ofstream out(argv[2]);

        auto board = readBoard(in);
        auto solution = solve(board);

        writeBoard(out, solution);

        // To check the solution
        if (argc == 4)
        {
            printBoard(solution);
            std::ifstream solutionIn(argv[3]);
            auto solutionBoard = readBoard(solutionIn);
            printBoard(solutionBoard);
        }

        return 0;
    }
    return 1;
}