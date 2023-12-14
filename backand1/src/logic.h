#ifndef LOGIC_H
#define LOGIC_H

#include <string>
#include <vector>
#include <unordered_map>

struct HashResult {
    std::string hash;
    std::vector<int> lineNumbers;
};

bool fileExists(const std::string& filePath);
bool filesIsTheSame(const std::string& firstFilePath, const std::string& secondFilePath);
std::string calculateStringHash(const std::string& input);

std::pair<std::unordered_map<std::string, std::vector<int>>, int> countHashesAddToHashMaps(const std::string& filePath);

#endif // LOGIC_H
