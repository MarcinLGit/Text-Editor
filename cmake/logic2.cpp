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
#include <algorithm>
#include <map>

//sprawdzenie czy plik istnieje
bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
     return file.good();
}

//sprawdzenie czy 2 pliki istnieją
bool files_exist(const std::string& firstFilePath, const std::string& secondFilePath) {  
    bool first_file_exist = fileExists(firstFilePath);
    bool second_file_exist = fileExists(secondFilePath);
   
    if(!first_file_exist || !second_file_exist){
        std::cerr << "Error: plik nie istnieje" << std::endl;
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




std::tuple<std::unordered_map<int, std::string>, std::unordered_map<int, std::string>, std::string, std::string> 
convert_to_two_hashmaps_and_strings(const std::unordered_map<int, std::pair<std::string, std::string>>& differences) {

    std::string first_file_differences;
    std::string second_file_differences;

    std::unordered_map<int, std::string> firstElements;
    std::unordered_map<int, std::string> secondElements;

    for (const auto& diff : differences) {
        firstElements[diff.first] = diff.second.first;
        first_file_differences += diff.second.first;
        secondElements[diff.first] = diff.second.second;
        second_file_differences += diff.second.second;
    }
    return {firstElements, secondElements, first_file_differences, second_file_differences};
}


// metoda dla wypisywania
void printMap(const std::string& title, const std::unordered_map<int, std::string>& mapa) {
    std::cout << title << std::endl;
    for (const auto& pair : mapa) {
        std::cout << "Indeks: " << pair.first << ", Zawartosc " << pair.second << std::endl;
    }
}

std::vector<char> fill_dyn_matrix( std::string &x,  std::string &y) {
        int m = x.length();
        int n = y.length();
        std::vector<std::vector<int>> L(m + 1, std::vector<int>(n + 1));

        // matrix L
        for (int i = 1; i <= m; i++) {
            for (int j = 1; j <= n; j++) {
                if (x[i-1] == y[j-1])
                    L[i][j] = L[i-1][j-1] + 1;
                else
                    L[i][j] = std::max(L[i-1][j], L[i][j-1]);
            }
        }

        // LCS
        std::vector<char> lcs;
        int x_i = m, y_i = n;
        while (x_i > 0 && y_i > 0) {
            if (x[x_i-1] == y[y_i-1]) {
                lcs.push_back(x[x_i-1]);
                x_i--;
                y_i--;
            } else if (L[x_i-1][y_i] > L[x_i][y_i-1]) {
                x_i--;
            } else {
                y_i--;
            }
        }

        std::reverse(lcs.begin(), lcs.end());
        return lcs;
    }


template <typename K, typename V>
std::vector<K> getKeys(const std::map<K, V>& map) {
    std::vector<K> keys;
    for (const auto& kv : map) {
        keys.push_back(kv.first);
    }
    return keys;
}

std::vector<std::pair<int, int>> swapedElement;

// dla ogarniecia zamiany tutaj odrazu i usuwam  z tych tablic  i  tworze nowa
std::pair<int,int> findIdenticalElement(
    std::map<int, std::string>& deleted_file_one_indexes,
    std::map<int, std::string>& added_file_two_indexes,
    int& deleted_file_one_indexe_key) {

    std::vector<int> keys2 = getKeys(deleted_file_one_indexes);//uzyc copy
    std::pair<int,int> identicalElements;

    
    std::vector<int> keysToDeleteInMap1, keysToDeleteInMap2;

        for (int key2:keys2) {
            if (deleted_file_one_indexes[deleted_file_one_indexe_key] == added_file_two_indexes[key2]) {
                identicalElements =  std::make_pair(deleted_file_one_indexe_key, key2);
                deleted_file_one_indexes.erase(deleted_file_one_indexe_key);
                added_file_two_indexes.erase(key2);
                break;
            }
        }
return identicalElements; //pozniej sprawdzic czy jest puste znaczenie czy nie

}



//porwnywanie objektow  jest to zrobione dla wyszukiwania ktory z  linijek jest zmieniony
std::vector<int> elementsForDelete(
    std::map<int, std::string>& deleted_file_one_indexes,
    std::map<int, std::string>& added_file_two_indexes,
    int& startFrom) {

    std::vector<int> keys = getKeys(deleted_file_one_indexes);//uzyc copy

    std::vector<int> keysToDeleteInMap; 
        for (int key:keys) {
            if (key<startFrom) {
                continue;
            if (deleted_file_one_indexes[key]== added_file_two_indexes[key+1]){
                keysToDeleteInMap.push_back(key);
            }   
        }
        }

    // usuniecia po iteracji
return keysToDeleteInMap;

}




// dla ogarniecia zamiany tutaj odrazu i usuwam  z tych tablic  i  tworze nowa



// dla ogarniecia zamiany tutaj odrazu i usuwam  z tych tablic  i  tworze nowa
std::vector<std::pair<int, int>> findSwaps(
    std::map<int, std::string>& deleted_file_one_indexes,
    std::map<int, std::string>& added_file_two_indexes,
    std::vector<std::pair<int, int>>& swapedElement) {
    
    std::vector<int> keys = getKeys(deleted_file_one_indexes);
    std::vector<int> keys2 = getKeys(added_file_two_indexes);//uzyc copy

    std::vector<int> keysToDeleteInMap1, keysToDeleteInMap2;

     for (int key : keys) { 
        std::pair<int,int>swapedForThisIndexElement=findIdenticalElement(deleted_file_one_indexes,added_file_two_indexes, key);
        if(swapedForThisIndexElement.first==0){
            continue;
        }
        else{swapedElement.push_back(swapedForThisIndexElement);
            std::vector<int>vectorFordelete=elementsForDelete(deleted_file_one_indexes,added_file_two_indexes,key);
            for (auto key : vectorFordelete) {
                deleted_file_one_indexes.erase(key);
                added_file_two_indexes.erase(key+1);
                }
            if(key= keys.size()-1){
                break;
            }
            else{swapedElement=findSwaps(deleted_file_one_indexes,added_file_two_indexes,swapedElement);}
                 
        }
    
    }
return swapedElement;
}











// 
void printIdenticalElements(const std::vector<std::pair<int, int>>& identicalElements) {
    for (const auto& elem : identicalElements) {
        std::cout << "Key 1: " << elem.first << ", Key 2: " << elem.second << std::endl;
    }
}


int levenshteinDistance(const std::string &s1, const std::string &s2) {
    int m = s1.length(), n = s2.length();
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1));

    for (int i = 0; i <= m; i++) dp[i][0] = i;
    for (int j = 0; j <= n; j++) dp[0][j] = j;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int cost = (s1[i - 1] == s2[j - 1]) ? 0 : 1;

            int deletion = dp[i - 1][j] + 1;
            int insertion = dp[i][j - 1] + 1;
            int substitution = dp[i - 1][j - 1] + cost;

            dp[i][j] = std::min(std::min(deletion, insertion), substitution);
        }
    }

    return dp[m][n];
}


double levenshteinPercentage(const std::string &s1, const std::string &s2) {
    int distance = levenshteinDistance(s1, s2);
    int maxLength = std::max(s1.length(), s2.length());
    
    //nie dzielić na zero
    if (maxLength == 0) return 0.0; 

    return 100.0 * distance / maxLength;
}


template <typename K, typename V>
std::map<K, V> unorderedMapToMap(const std::unordered_map<K, V>& unorderedMap) {
    std::map<K, V> orderedMap;
    for (const auto& kv : unorderedMap) {
        orderedMap.insert(kv);
    }
    return orderedMap;
}



//tutaj tez pytanie czy wyszukiwac modyfikacje tylko w odpowiednich linijach czy razem z zamiana
std::vector<int> findModificationsWithLevenshtein(
    std::unordered_map<int, std::string>& deleted_file_one_indexes,
    std::unordered_map<int, std::string>& added_file_two_indexes) {

    std::vector<int> modifications;
    std::vector<int> keysToDeleteInMap;

     for (const auto& kv : deleted_file_one_indexes) {
        std::cout << "Klucz: " << kv.first << std::endl;
    }

         for (const auto& kv : deleted_file_one_indexes) {
                double percentage = levenshteinPercentage(kv.second,added_file_two_indexes[kv.first] );
            if (percentage < 90) { 
                modifications.push_back(kv.first);
                keysToDeleteInMap.push_back(kv.first);
                
            }
        }
    

    // Usuwanie kluczy po iteracji
    for (auto key : keysToDeleteInMap) {
        deleted_file_one_indexes.erase(key);
    }
    for (auto key : keysToDeleteInMap) {
        added_file_two_indexes.erase(key);
    }

    return modifications;
}





int main() {

    std::string file1="file1.txt";
    std::string file2="file2.txt";

    if (files_exist(file1, file2) !=true){ //podać nazwe
        std::cout<<"terminate"<<std::endl;
        std::terminate();
    }
    auto [lines_file1, lines_file2] = read_files("file1.txt", "file2.txt");

    std::unordered_map<int, std::pair<std::string, std::string>> differences_map =compare(lines_file1, lines_file2);
    auto [first_file_differences_hashmap, second_file_differences_hashmap,firstDifferencesString, secondDifferencesString]
    =convert_to_two_hashmaps_and_strings(differences_map);
     
     LCS lcs_instance;


   
    
    std::vector<char> lcs_vector = fill_dyn_matrix(firstDifferencesString, secondDifferencesString); 
    std::string lcss(lcs_vector.begin(), lcs_vector.end()); 
    std::cout << lcss << std::endl;


    std::pair<std::unordered_map<int, std::string>, std::unordered_map<int, std::string>> result1;
    std::pair<std::unordered_map<int, std::string>, std::unordered_map<int, std::string>> result2;

    
    std::thread thread1(threadFunction, lcss, std::ref(first_file_differences_hashmap), std::ref(result1));
    std::thread thread2(threadFunction, lcss, std::ref(second_file_differences_hashmap), std::ref(result2));

    thread1.join();
    thread2.join();   // na ten moment widac add i del

    std::cout << "pierwszy plik" << std::endl;
    printMap("znalezione stringi:", result1.first);
    std::cout << " " << std::endl;
    printMap("usunięte stringi:", result1.second);
    std::cout << " " << std::endl;

    
    std::cout << "drugi plik:" << std::endl;
    std::cout << " " << std::endl;
    printMap("znalezione stringi:", result2.first);
    std::cout << " " << std::endl;
    printMap("dodane stringi:", result2.second);
   

    std::map<int, std::string>result12=unorderedMapToMap(result1.second);
    std::map<int,std::string>result22=unorderedMapToMap(result2.second);
    //std::vector<std::pair<int, int>> changes = findIdenticalElements(result12, result22);


    std::cout << "Po zmianie" << std::endl;
    std::cout << "  " << std::endl;

    std::cout << "pierwszy plik" << std::endl;
    printMap("znalezione stringi:", result1.first);
    std::cout << " " << std::endl;
    printMap("usunięte stringi:", result1.second);
    std::cout << " " << std::endl;

    
    std::cout << "drugi plik:" << std::endl;
    std::cout << " " << std::endl;
    printMap("znalezione stringi:", result2.first);
    std::cout << " " << std::endl;
    printMap("dodane stringi:", result2.second);
    std::cout << "  " << std::endl;
    std::cout << "  " << std::endl;
    std::vector<std::pair<int, int>> swapedElement;
    swapedElement=findSwaps(result12,result22,swapedElement);
    std::cout<<"swaped lines"<<std::endl;
    printIdenticalElements(swapedElement);


    std::cout<<"po wyszukiwaniu modyfikacji"<<std::endl;
    //po wyszukiwaniu zmian
    std::vector<int> modifications = findModificationsWithLevenshtein(result1.second,result2.second);
    for (int number : modifications) { 
        std::cout << number << " ";
    } 





    return 0;
}






