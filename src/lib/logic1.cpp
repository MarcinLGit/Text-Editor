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

//sprawdzenie czy plik istnieje
bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
     return file.good();
}

//sprawdzenie czy 2 pliki istnieją
bool files_exist(const std::vector<std::string>& lines_file1, const std::vector<std::string>& lines_file2) {  //++
   
    
    bool first_file_exist = fileExists(firstFilePath); //podwojne sprawdzanie na itnienie pliku wykorzystuje metode z hash_calculator
    bool second_file_exist = fileExists(secondFilePath);
   
    if(!first_file_exist|| !second_file_exist){
        std::cerr << "Error: plik nie istnieje " << std::endl;
        return false;
        
    }
    return true;
}

//wczytywanie plików
void read_file(const std::string& file_name, std::vector<std::string>& lines) { //++
    std::ifstream file(file_name);
    std::string line;
    while (std::getline(file, line)) {
        lines.push_back(line);
    }
}

std::pair<std::vector<std::string>, std::vector<std::string>> read_files(const std::string& file1, const std::string& file2) { //++
    std::vector<std::string> lines_file1, lines_file2;

    // tworzenie wątków
    std::thread thread1(read_file, file1, std::ref(lines_file1));
    std::thread thread2(read_file, file2, std::ref(lines_file2));

    // oczekiwanie na koniec
    thread1.join();
    thread2.join();

    return {lines_file1, lines_file2};
}

//porównuje i zwraca  hashmap z numerem linijki i zawartoscą plików
std::unordered_map<int, std::pair<std::string, std::string>> 
compare(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2) {
    
    std::unordered_map<int, std::pair<std::string, std::string>> differences;

    size_t minSize = std::min(vec1.size(), vec2.size());
    
    // porównanie vectorów
    for (size_t i = 0; i < minSize; i++) {
        if (vec1[i] != vec2[i]) {
            differences[i] = {vec1[i], vec2[i]};
        }
    }

    // dodawanie reszty
    for (size_t i = minSize; i < vec1.size(); i++) {
        differences[i] = {vec1[i], ""}; 
    }
    for (size_t i = minSize; i < vec2.size(); i++) {
        differences[i] = {"", vec2[i]}; 
    }

    return differences;
}


//szuka substringi w lcs zwraca różnicy
std::pair<std::unordered_map<int, std::string>, std::unordered_map<int, std::string>> 
findAddDel(const std::string& lcs, const std::unordered_map<int, std::string>& mapa) { //++
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

//funkcja dla threadsów
void threadFunction(const std::string& lcs, const std::unordered_map<int, std::string>& mapa, 
                    std::pair<std::unordered_map<int, std::string>, std::unordered_map<int, std::string>>& result) {
    result = findAddDel(lcs, mapa);
}


std::pair<std::unordered_map<int, std::string>, std::unordered_map<int, std::string>> 
convert_to_two_hashmaps(const std::unordered_map<int, std::pair<std::string, std::string>>& differences) {

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
    return {firstElements, secondElements};
}


// metoda dla wypisywania
void printMap(const std::string& title, const std::unordered_map<int, std::string>& mapa) {
    std::cout << title << std::endl;
    for (const auto& pair : mapa) {
        std::cout << "Индекс: " << pair.first << ", Строка: " << pair.second << std::endl;
    }
}



int main() {
    std::string file1="file1.txt";
    std::string file2="file2.txt";

    if (fileExists(file1, file2) !=true){ //podać nazwe
       std::cout<"terminate"<endl
        std::terminate();
    }
    auto [lines_file1, lines_file2] = read_files("file1.txt", "file2.txt");

    std::unordered_map<int, std::pair<std::string, std::string>> differences_map =compare(lines_file1, lines_file2);
    auto [first_file_differences_hashmap, second_file_differences_hashmap] = convert_to_two_hashmaps(differences_map);

     
    std::vector<char> lcs = LCS::fill_dyn_matrix(lines_file1, lines_file2); 
    string lcss(lcs.begin(), lcs.end()); 
    std::cout<<lcss<<endl;

    std::pair<std::unordered_map<int, std::string>, std::unordered_map<int, std::string>> result1;
    std::pair<std::unordered_map<int, std::string>, std::unordered_map<int, std::string>> result2;

    std::thread thread1(threadFunction, lcs, std::ref(mapa1), std::ref(result1));
    std::thread thread2(threadFunction, lcs, std::ref(mapa2), std::ref(result2));

    thread1.join();
    thread2.join();

    std::cout << "pierwszy plik" << std::endl;
    printMap("znalezione stringi:", result1.first);
    printMap("usunięte stringi:", result1.second);

    // Вывод результатов для второго потока
    std::cout << "drugi plik:" << std::endl;
    printMap("znalezione stringi:", result2.first);
    printMap("dodane stringi:", result2.second);
   

    return 0;
}














/*

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

*/