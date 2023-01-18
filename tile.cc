#include "tile.hh"

Tile::Tile(char north, char west, char east, char south, bool movable)
    : north(north)
    , west(west)
    , east(east)
    , south(south)
    , movable(movable)
{}

char Tile::getNorth() const
{
    return north;
}

char Tile::getWest() const
{
    return west;
}

char Tile::getEast() const
{
    return east;
}

char Tile::getSouth() const
{
    return south;
}

bool Tile::isMovable() const
{
    return movable;
}

Tile Tile::parse_from_string(const std::string &str)
{
    if (str.length() == 7 && str[6] == '@')
    {
        return Tile(str[0], str[1], str[2], str[3], true);
    }
    return Tile(str[0], str[1], str[2], str[3], false);
}

std::vector<Tile> Tile::parse_from_file(const std::string &filename)
{
    std::vector<Tile> tiles;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        tiles.push_back(parse_from_string(line));
    }
    return tiles;
}

std::string Tile::to_string() const
{
    return std::string(1, north) + west + east + south;
}