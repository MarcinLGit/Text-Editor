#include "hash_calculator.h" 
#include "logic.h"
#include "leven.h"
#include "lcs.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <mutex>


HashCalculator hasher;
LCS lcs;
Leven leven;

CONST 
bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
     return file.good();
}


bool files_exist(const std::vector<std::string>& lines_file1, const std::vector<std::string>& lines_file2) {
   
    
    bool first_file_exist = fileExists(firstFilePath); //podwojne sprawdzanie na itnienie pliku wykorzystuje metode z hash_calculator
    bool second_file_exist = fileExists(secondFilePath);
   
    if(!first_file_exist|| !second_file_exist){
        std::cerr << "Error: plik nie istnieje " << std::endl;
        return false;
        
    }
    return true;
}


void read_file(const std::string& file_name, std::vector<std::string>& lines) {
    std::ifstream file(file_name);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
}

std::pair<std::vector<std::string>, std::vector<std::string>> read_files(const std::string& file1, const std::string& file2) {
    std::vector<std::string> lines_file1, lines_file2;

    // tworzenie wątków
    std::thread thread1(read_file, file1, std::ref(lines_file1));
    std::thread thread2(read_file, file2, std::ref(lines_file2));

    // oczekiwanie na koniec
    thread1.join();
    thread2.join();

    return {lines_file1, lines_file2};
}


std::unordered_map<int, std::string> compare(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2) {
   
    std::unordered_map<int, std::pair<std::string, std::string>> differences; //bez sensu robić templatowy
    int counter = 0;

    std::unordered_map<int, std::pair<std::string, std::string>> differences;

    size_t minSize = std::min(array1.size(), array2.size());
    
    // najkrotszy
    for (size_t i = 0; i < minSize; i++) {
        if (array1[i] != array2[i]) {
            differences[i] = {array1[i], array2[i]};
        }
    }

    // dodawanie resztek
    for (size_t i = minSize; i < array1.size(); i++) {
        differences[i] = {array1[i], ""}; 
    }
    for (size_t i = minSize; i < array2.size(); i++) {
        differences[i] = {"", array2[i]}; 
    }
return differences;

}


std::pair<std::unordered_map<int, std::string>, std::unordered_map<int, std::string>> 
findSubstring(const std::string& lcs, const std::unordered_map<int, std::string>& mapa) {
    std::unordered_map<int, std::string> foundSubstrings;
    std::unordered_map<int, std::string> notFoundSubstrings;

    for (const auto& pair : mapa) {
        if (lcs.find(pair.second) != std::string::npos) {
            // jeśli to substring
            foundSubstrings.insert(pair);
        } else {
            // jeśli to nie substring
            notFoundSubstrings.insert(pair);
        }
    }

    return {foundSubstrings, notFoundSubstrings};
}


std::pair<std::unordered_map<int, std::string>, std::unordered_map<int, std::string>> 
findDelAdd(const std::unordered_map<int, std::pair<std::string, std::string>>& differences) {

    std::string first_file_differences;
    std::string second_file_differences;

    std::unordered_map<int, std::string> firstElements;
    std::unordered_map<int, std::string> secondElements;

    for (const auto& diff : differences) {
        firstElements[diff.first] = diff.second.first;
        first_file_differences+=diff.second.first;
        secondElements[diff.first] = diff.second.second;
        second_file_differences+=diff.second.second;
    }

    std::vector<char> lcs = LCS::fill_dyn_matrix(x, y);
    string lcss(lcs.begin(), lcs.end()); 
    std::cout<<lcss<<endl;


    return {firstElements, secondElements};
}



    
    
    





std::pair<std::unordered_map<std::string, std::vector<int>>, int> countHashesAddToHashMaps() {
    
    std::string line;
    int lineNumber = 0;
    std::unordered_map<std::string, std::vector<int>> resultMap;

    
    while (std::getline(file, line)) {
        std::string hash = calculateStringHash(line);

        if (resultMap.find(hash) == resultMap.end()) {
            
            resultMap[hash] = {lineNumber};
        } else {
            resultMap[hash].push_back(lineNumber); //jesli istnieje dodajemy do vector
        }

        lineNumber++;
    }

    file.close();

    
    return {resultMap, lineNumber - 1};
}




int main() {

    if (fileExists !=true){
       std::cout<"terminate"<endl
        std::terminate();
    }
    auto [lines_file1, lines_file2] = read_files("file1.txt", "file2.txt");

   

    return 0;
}
