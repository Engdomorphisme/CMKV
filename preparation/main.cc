#include "tetravex.hh"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cerr << "Usage: " << argv[0] << " <input_file> <output_file>"
                  << std::endl;
        return 1;
    }
    Tetravex tetravex = Tetravex::parse_from_file(argv[1]);
    tetravex.print();
    tetravex.toFile(argv[2]);
    std::cout << "Score: " << tetravex.evaluate() << std::endl;

    tetravex.swap_tiles(0, 1);
    tetravex.swap_tiles(0, 2);

    tetravex.print();
    std::cout << "Score: " << tetravex.evaluate() << std::endl;
    return 0;
}