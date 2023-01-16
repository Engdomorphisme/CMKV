#include <experimental/random>
#include <fstream>
#include <iostream>
#include <vector>

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: " << argv[0] << " <sizeof board> <output file>"
                  << std::endl;
        return 1;
    }
    int n = std::stoi(argv[1]);
    std::ofstream out(argv[2]);
    std::vector<std::string> board;
    srand(time(nullptr));
    for (int i = 0; i < n * n; ++i)
    {
        std::string line;
        for (int j = 0; j < 4; ++j)
        {
            line += std::to_string(std::experimental::randint(1, 9));
        }
        if (i % n != 0)
        {
            line[1] = board[i - 1][2];
        }
        if (i / n != 0)
        {
            line[0] = board[i - n][3];
        }
        board.push_back(line);
        out << board[i] << std::endl;
    }

    return 0;
}