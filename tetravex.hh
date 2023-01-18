#include <iostream>

#include "tile.hh"

using Board = std::vector<Tile>;

void printBoard(Board &board);

void writeBoard(std::ofstream &out, Board &board);

Board readBoard(std::ifstream &in);

int evaluate(Board &board);