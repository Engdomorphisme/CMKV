#include <cmath>
#include <experimental/random>
#include <fstream>
#include <iostream>
#include <vector>

#include "solver.hh"
#include "tetravex.hh"
#include "tile.hh"

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