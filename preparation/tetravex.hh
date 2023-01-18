#pragma once

#include <cmath>
#include <iostream>

#include "tile.hh"

class Tetravex
{
public:
    Tetravex(const std::vector<Tile> &tiles, size_t size);
    Tetravex(const Tetravex &) = default;

    void print() const;
    void toFile(const std::string &filename) const;

    static Tetravex parse_from_file(const std::string &filename);

    const size_t getSize() const;
    int evaluate() const;

    void swap_tiles(int i, int j);

private:
    std::vector<Tile> board;
    const size_t size;
};