#include "solver.hh"

#include <cmath>
#include <random>

#include "tile.hh"

Board solve(Board &board)
{
    int size = board.size();
    int n = std::sqrt(size);
    int score = evaluate(board);
    int bestScore = score;
    Board bestBoard = board;
    int iterations = 0;
    int maxIterations = 1000000;
    double T0 = 5.0;
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);

    while (score > 0)
    {
        int i = std::experimental::randint(0, size - 1);
        while (!board[i].isMovable())
        {
            i = (i + 1) % size;
        }
        int j = std::experimental::randint(0, size - 1);
        while (!board[j].isMovable() || i == j)
        {
            j = (j + 1) % size;
        }

        Tile temp = board[i];
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
        // If the neighbor is worse, accept it with probability e^(-delta / T)
        else
        {
            double T = T0 / log(iterations + 2);
            double delta = score - bestScore;
            double p = exp(-delta / T);
            if (distribution(rng) < p)
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