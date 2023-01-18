#pragma once

#include <fstream>
#include <string>
#include <vector>

class Tile
{
public:
    explicit Tile(char north, char west, char east, char south, bool movable);
    Tile(const Tile &) = default;

    char getNorth() const;
    char getWest() const;
    char getEast() const;
    char getSouth() const;

    bool isMovable() const;

    static Tile parse_from_string(const std::string &str);
    static std::vector<Tile> parse_from_file(const std::string &filename);

    std::string to_string() const;

private:
    char north;
    char west;
    char east;
    char south;

    bool movable;
};