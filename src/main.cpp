#include <fstream>
#include <iostream>


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Input file path required\n";
        return 1;
    }

    std::ifstream input_file(argv[1]);

    if (!input_file) {
        std::cerr << "Cannot open file: " << argv[1] << "\n";
        return 1;
    }
}
