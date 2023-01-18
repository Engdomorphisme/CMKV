#include "tetravex.hh"

#include <cmath>

#include "tile.hh"

Board readBoard(std::ifstream &in)
{
    Board board;
    std::string line;
    while (std::getline(in, line))
    {
        auto north = line[0];
        auto west = line[1];
        auto east = line[2];
        auto south = line[3];
        auto movable = true;
        if (line.length() == 6 && line[5] == '@')
        {
            movable = false;
        }

        Tile tile(north, west, east, south, movable);
        board.push_back(tile);
    }
    return board;
}

void printBoard(Board &board)
{
    int n = std::sqrt(board.size());

    // Top separator[1]
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
            std::cout << "  " << board[i * n + j].getNorth() << "  |";
        }
        std::cout << std::endl;

        // West and East borders
        std::cout << "|";
        for (int j = 0; j < n; ++j)
        {
            std::cout << " " << board[i * n + j].getWest() << " "
                      << board[i * n + j].getEast() << " |";
        }
        std::cout << std::endl;

        // South border
        std::cout << "|";
        for (int j = 0; j < n; ++j)
        {
            std::cout << "  " << board[i * n + j].getSouth() << "  |";
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
    for (int i = 0; i < board.size(); ++i)
    {
        out << board[i].to_string() << std::endl;
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
            if (board[i * n + j].getSouth()
                != board[(i + 1) * n + j].getNorth())
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
            if (board[i * n + j].getEast() != board[i * n + j + 1].getWest())
            {
                score += 1;
            }
        }
    }
    return score;
}