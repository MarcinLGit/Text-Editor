#include "hash_calculator.h"
#include <iostream>
#include <fstream>

int main() {
    HashCalculator hashCalculator;

    std::string filePath = "/path/to/your/textfile.txt";
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filePath << std::endl;
        return 1;
    }

    std::string line;
    std::string fileContent;

 //plik jest odczytywany linujka po linijce
    while (std::getline(file, line)) {
        // Tutaj możesz wykonać operacje na każdej linijce, np. obliczyć hash
        std::string lineHash = hashCalculator.calculateStringHash(line);

        // Możesz także dodawać hash każdej linijki do całkowitego hasza pliku
        fileContent += lineHash;

        // Wyświetl hash dla każdej linijki
        std::cout << "Hash for line: " << lineHash << std::endl;
    }

    // Oblicz hash dla całego pliku
    std::string fileHash = hashCalculator.calculateStringHash(fileContent);

    // Wyświetl hash dla całego pliku
    std::cout << "Hash for the entire file: " << fileHash << std::endl;

    file.close();

    return 0;
}
