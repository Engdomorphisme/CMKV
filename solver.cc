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
    double T0 = n + 1;

    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<double> distribution(0.0, 1.0);
    std::uniform_int_distribution<int> randint(0, size - 1);

    while (bestScore != 0)
    {
        int i = randint(rng);
        while (!board[i].isMovable())
        {
            i = (i + 1) % size;
        }
        int j = randint(rng);
        while (!board[j].isMovable() || i == j)
        {
            j = (j + 1) % size;
        }
        auto begin = board.begin();
        std::swap(*(begin + i), *(begin + j));

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
            // Reject the neighbor and restore the board
            else
            {
                board = bestBoard;
            }
        }
        iterations += 1;
    }
    return bestBoard;
}