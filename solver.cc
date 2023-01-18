#include "solver.hh"

#include "tile.hh"

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

    while (score > 0)
    {
        int i = std::experimental::randint(0, size - 1);
        while (!board[i].isMovable())
        {
            i = std::experimental::randint(0, size - 1);
        }
        int j = std::experimental::randint(0, size - 1);
        while (!board[j].isMovable() || i == j)
        {
            j = std::experimental::randint(0, size - 1);
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