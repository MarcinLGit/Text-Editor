#include "hash_calculator.h"
#include <iostream>
#include <vector>
#include <fstream>


int main() {
    HashCalculator hashCalculator;
    std::string filePath = "cos.txt";
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return 1;
    }

    const size_t lines_per_chunk = 4;
    std::vector<std::string> chunkStrings;
    std::vector<std::string> hashes;

    while (!file.eof()) {
        std::string line;
        for (size_t i = 0; i < lines_per_chunk && std::getline(file, line); ++i) {
            chunkStrings.push_back(line);
        }

        if (chunkStrings.size() == lines_per_chunk) {
            std::string hash = hashCalculator.calculateStringHash(chunkStrings[0] + chunkStrings[1] + chunkStrings[2] + chunkStrings[3]);
            hashes.push_back(hash);
        }

        chunkStrings.clear();
    }

    file.close();

    for (const auto& hash : hashes) {
        std::cout << "SHA-256 Hash: " << hash << std::endl;
    }

    return 0;
}
