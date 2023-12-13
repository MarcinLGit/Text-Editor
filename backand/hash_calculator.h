#pragma once

#include <string>

class HashCalculator {
public:
    static std::string calculateStringHash(const std::string& input);
    static std::string readFileToString(const std::string& filePath);
};
