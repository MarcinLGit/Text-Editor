#ifndef FILE_COMPARISON_UTILS_H
#define FILE_COMPARISON_UTILS_H

#include <string>
#include <vector>
#include <map>
#include <tuple>

// Function declarations

std::map<int, std::pair<std::string, std::string>> compare(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2);// sprawdzomo
std::map<int, std::string> findAddDel(const std::string& lcs, const std::map<int, std::string>& mapa);//sprawdzono

std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::string, std::string> convert_to_two_hashmaps_and_strings(const std::map<int, std::pair<std::string, std::string>>& differences); //stestowane

template<typename K, typename V>
std::vector<K> getKeys(const std::map<K, V>& m);

std::pair<int,int> findIdenticalElement(std::map<int, std::string>& deleted_file_one_indexes,std::map<int, std::string>& added_file_two_indexes,int& deleted_file_one_indexe_key);//testy
std::pair<std::vector<int>,std::vector<int>> elementsForDelete(std::map<int, std::string>& deleted_file_one_indexes, std::map<int, std::string>& added_file_two_indexes, int& startFrom, int& secondfileSwapIndex); //sprawdzono
std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<std::pair<int, int>>> findSwaps(std::map<int, std::string>& deleted_file_one_indexes, std::map<int, std::string>& added_file_two_indexes, std::vector<std::pair<int, int>>& swapedElement, std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<std::pair<int, int>>>& tuple);//sprawdzono

std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<int>> findModificationsWithLevenshtein(std::map<int, std::string>& deleted_file_one_indexes, std::map<int, std::string>& added_file_two_indexes);
std::tuple<std::map<int, std::string>,std::map<int, std::string>,std::vector<std::pair<int, int>>,std::vector<int>> mainFunction(std::vector<std::string>& lines_file1, std::vector<std::string>& lines_file2);
#endif // FILE_COMPARISON_UTILS_H
