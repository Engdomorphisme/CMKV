#include "tetravex.hh"

Tetravex::Tetravex(const std::vector<Tile> &tiles, size_t size)
    : board(tiles)
    , size(size)
{}

void Tetravex::print() const
{
    int n = size;

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

void Tetravex::toFile(const std::string &filename) const
{
    std::ofstream file(filename);
    for (auto &tile : board)
    {
        file << tile.to_string() << std::endl;
    }
}

Tetravex Tetravex::parse_from_file(const std::string &filename)
{
    std::vector<Tile> tiles;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line))
    {
        tiles.push_back(Tile::parse_from_string(line));
    }
    return Tetravex(tiles, std::sqrt(tiles.size()));
}

const size_t Tetravex::getSize() const
{
    return size;
}

int Tetravex::evaluate() const
{
    int score = 0;
    for (int i = 0; i < size; ++i)
    {
        for (int j = 0; j < size; ++j)
        {
            if (i < size - 1)
            {
                score += board[i * size + j].getSouth()
                    != board[(i + 1) * size + j].getNorth();
            }
            if (j < size - 1)
            {
                score += board[i * size + j].getEast()
                    != board[i * size + j + 1].getWest();
            }
        }
    }
    return score;
}

void Tetravex::swap_tiles(int i, int j)
{
    auto begin = board.begin();
    std::iter_swap(begin + i, begin + j);
}