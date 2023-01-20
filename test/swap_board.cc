#include <algorithm>
#include <experimental/random>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <inuput file> <output file>"
                  << std::endl;
        return 1;
    }
    std::ifstream in(argv[1]);
    std::string line;
    std::vector<std::string> board;
    while (std::getline(in, line))
    {
        board.push_back(line);
    }
    int n = board.size();

    int azer = std::experimental::randint(0, n - 1);
    auto board_copy = board;
    for (int i = 0; i < n * n - n; ++i)
    {
        int x = std::experimental::randint(0, n - 1);
        while (x == azer)
            x = (x + 1) % n;
        int y = std::experimental::randint(0, n - 1);
        while (x == y || y == azer)
            y = (y + 1) % n;

        auto begin = board_copy.begin();
        std::iter_swap(begin + x, begin + y);
    }

    std::ofstream out(argv[2]);

    for (int i = 0; i < n; ++i)
    {
        if (board[i] != board_copy[i])
            out << board_copy[i] << std::endl;
        else
            out << board_copy[i] << " @" << std::endl;
    }

    return 0;
}