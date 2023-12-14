#ifndef HASH_CALCULATOR_H
#define HASH_CALCULATOR_H

#include <string>

class HashCalculator {
public:
    std::string calculateStringHash(const std::string& input);
    std::string readFileToString(const std::string& filePath);
};

#endif 