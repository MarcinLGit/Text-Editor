
#include "leven.h"
#include "lcs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <map>
#include <vector>
#include <mutex>
#include <algorithm>
#include <map>




std::map<int, std::string> convertVectorToMap(const std::vector<std::string>& lines) {
    std::map<int, std::string> lineMap;
    for (size_t i = 0; i < lines.size(); ++i) {
        lineMap[static_cast<int>(i)] = lines[i];
    }
    return lineMap;
}


void writeMapToFile(const std::map<int, std::string>& lineMap, const std::string& filePath) {
    std::ofstream outFile(filePath);

    if (!outFile.is_open()) {
        throw std::runtime_error("Unable to open file: " + filePath);
    }

    for (const auto& pair : lineMap) {
        outFile << pair.second << "\n"; // Write the line content to the file
    }

    outFile.close();
}


void writeVectorToFile(const std::vector<std::string>& lines, const std::string& filePath) {
    std::ofstream outFile(filePath);

    if (!outFile.is_open()) {
        throw std::runtime_error("Nie można otworzyć pliku: " + filePath);
    }

    for (const auto& line : lines) {
        outFile << line << "\n"; // Zapisz zawartość linii do pliku
    }

    outFile.close();
}

std::pair<std::vector<std::string>,std::map<int,std::string>> deleteLine(int& indexToDelete, std::map<int,std::string>&deletedLines, std::vector<std::string>& file_lines,std::string& path){
    
    file_lines.erase(file_lines.begin() + indexToDelete);
    deletedLines.erase(indexToDelete);
    writeVectorToFile(file_lines, path);
    return std::make_pair(file_lines,deletedLines);
}