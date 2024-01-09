#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

#include <vector>
#include <string>
#include <map>
#include <stdexcept>
#include <fstream>

// Преобразует вектор строк в карту, где ключ - это индекс строки
std::map<int, std::string> convertVectorToMap(const std::vector<std::string>& lines);

// Записывает карту строк в файл
void writeMapToFile(const std::map<int, std::string>& lineMap, const std::string& filePath);

// Записывает вектор строк в файл
void writeVectorToFile(const std::vector<std::string>& lines, const std::string& filePath);

// Удаляет строку из вектора и карты по индексу, затем сохраняет вектор в файл

std::pair<std::vector<std::string>,std::map<int,std::string>> deleteLine(int& indexToDelete, std::map<int,std::string>&deletedLines, std::vector<std::string>& file_lines,std::string& path);
    
#endif // FILE_OPERATIONS_H
