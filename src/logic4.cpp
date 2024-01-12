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





//porównuje i zwraca  hashmap z numerem linijki i zawartoscą plików
std::map<int, std::pair<std::string, std::string>>
compare(const std::vector<std::string>& vec1, const std::vector<std::string>& vec2) {

    std::map<int, std::pair<std::string, std::string>> differences;

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
std::map<int, std::string> findAddDel(const std::string& lcs, const std::map<int, std::string>& mapa) { //++

    std::map<int, std::string> notFoundSubstrings;

    for (const auto& pair : mapa) {
        if (lcs.find(pair.second) == std::string::npos) {
            notFoundSubstrings.insert(pair);
        }
    }

    return notFoundSubstrings;
}

//funkcja dla threadsów
void threadFunction(const std::string& lcs, const std::map<int, std::string>& mapa,
                    std::map<int, std::string>& result) {
    result = findAddDel(lcs, mapa);
}



//konwertacja

std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::string, std::string>
convert_to_two_hashmaps_and_strings(const std::map<int, std::pair<std::string, std::string>>& differences) {

    std::string first_file_differences;
    std::string second_file_differences;

    std::map<int, std::string> firstElements;
    std::map<int, std::string> secondElements;

    for (const auto& diff : differences) {
        firstElements[diff.first] = diff.second.first;
        first_file_differences += diff.second.first;
        secondElements[diff.first] = diff.second.second;
        second_file_differences += diff.second.second;
    }
    return {firstElements, secondElements, first_file_differences, second_file_differences};
}


// metoda dla wypisywania
void printMap(const std::string& title, const std::map<int, std::string>& mapa) {
    std::cout << title << std::endl;
    for (const auto& pair : mapa) {
        std::cout << "Indeks: " << pair.first << ", Zawartosc " << pair.second << std::endl;
    }
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

    std::vector<int> keys2 = getKeys(added_file_two_indexes);//uzyc copy
    std::pair<int,int> identicalElements;



    for (int key2:keys2) {
        if (deleted_file_one_indexes[deleted_file_one_indexe_key] == added_file_two_indexes[key2]) {
            identicalElements =  std::make_pair(deleted_file_one_indexe_key, key2);

            break;
        }
    }
    return identicalElements; //pozniej sprawdzic czy jest puste znaczenie czy nie

}



//porwnywanie objektow  jest to zrobione dla wyszukiwania ktory z  linijek jest zmieniony
std::pair<std::vector<int>,std::vector<int>> elementsForDelete(
    std::map<int, std::string>& deleted_file_one_indexes,
    std::map<int, std::string>& added_file_two_indexes,
    int& startFrom,
    int& secondfileSwapIndex) {

    std::vector<int> keys = getKeys(deleted_file_one_indexes);

    std::vector<int> keysToDeleteInMap1;
    std::vector<int> keysToDeleteInMap2;
    for (int key:keys) {


        if (key>=startFrom && key-1<secondfileSwapIndex && deleted_file_one_indexes[key]== added_file_two_indexes[key-1]){

            keysToDeleteInMap1.push_back(key);
            keysToDeleteInMap2.push_back(key-1);
        }
        if (key>=startFrom && key-1>=secondfileSwapIndex && deleted_file_one_indexes[key]== added_file_two_indexes[key]){

            keysToDeleteInMap1.push_back(key);
            keysToDeleteInMap2.push_back(key);
        }
    }


    //  zrobic usuniecia po iteracji  moze sama funkcje?
    return std::make_pair(keysToDeleteInMap1,keysToDeleteInMap2);

}

void printIdenticalElements(const std::vector<std::pair<int, int>>& identicalElements) {
    for (const auto& elem : identicalElements) {
        std::cout << "Key 1: " << elem.first << ", Key 2: " << elem.second << std::endl;
    }
}

// dla ogarniecia zamiany tutaj odrazu i usuwam  z tych tablic  i  tworze nowa



// dla ogarniecia zamiany tutaj odrazu i usuwam  z tych tablic  i  tworze nowa
std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<std::pair<int, int>>> findSwaps(
    std::map<int, std::string>& deleted_file_one_indexes,
    std::map<int, std::string>& added_file_two_indexes,
    std::vector<std::pair<int, int>>& swapedElement,
    std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<std::pair<int, int>>>& tuple) {

    std::vector<int> keys = getKeys(deleted_file_one_indexes);
    std::vector<int> keys2 = getKeys(added_file_two_indexes);//uzyc copy


    std::vector<int> keysToDeleteInMap1, keysToDeleteInMap2;

    for (int key : keys) {


        std::pair<int,int>swapedForThisIndexElement=findIdenticalElement(deleted_file_one_indexes,added_file_two_indexes, key);


        if(swapedForThisIndexElement.first!=0 && swapedForThisIndexElement.second !=0){


            deleted_file_one_indexes.erase(swapedForThisIndexElement.first);
            added_file_two_indexes.erase(swapedForThisIndexElement.second);

            swapedElement.push_back(swapedForThisIndexElement);
            auto pairOfVectorsForDelete=elementsForDelete(deleted_file_one_indexes,added_file_two_indexes,key,swapedForThisIndexElement.second);
            for (auto key : pairOfVectorsForDelete.first) {
                deleted_file_one_indexes.erase(key);
            }
            for (auto key1 : pairOfVectorsForDelete.second) {
                added_file_two_indexes.erase(key1);
            }
            if(key== keys.size()-1){
                break;
            }
            else{
                tuple=findSwaps(deleted_file_one_indexes,added_file_two_indexes,swapedElement,tuple);}

        }

    }
    return std::make_tuple(deleted_file_one_indexes, added_file_two_indexes,swapedElement);
}


//



template <typename K, typename V>
std::map<K, V> unorderedMapToMap(const std::map<K, V>& unorderedMap) {
    std::map<K, V> orderedMap;
    for (const auto& kv : unorderedMap) {
        orderedMap.insert(kv);
    }
    return orderedMap;
}



//tutaj tez pytanie czy wyszukiwac modyfikacje tylko w odpowiednich linijach czy razem z zamiana
//zrobiono jak w meld
std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<int>>  findModificationsWithLevenshtein(
    std::map<int, std::string>& deleted_file_one_indexes,
    std::map<int, std::string>& added_file_two_indexes) {

    std::vector<int> modifications;
    std::vector<int> keysToDeleteInMap;

    for (const auto& kv : deleted_file_one_indexes) {
        std::cout << "Klucz: " << kv.first << std::endl;
    }

    for (const auto& kv : deleted_file_one_indexes) {
        double percentage = lcsPercentage(kv.second,added_file_two_indexes[kv.first] );
        if (percentage > 85) {
            modifications.push_back(kv.first);
            keysToDeleteInMap.push_back(kv.first);

        }
    }


    // Usuwanie kluczy po iteracji mozna w sumie dac funkcje do usuwania
    for (auto key : keysToDeleteInMap) {
        deleted_file_one_indexes.erase(key);
    }
    for (auto key : keysToDeleteInMap) {
        added_file_two_indexes.erase(key);
    }

    return  std::make_tuple(deleted_file_one_indexes, added_file_two_indexes, modifications);
}








std::tuple<std::map<int, std::string>,
           std::map<int, std::string>,
           std::vector<std::pair<int, int>>,
           std::vector<int>> mainFunction(std::vector<std::string>& lines_file1,
             std::vector<std::string>& lines_file2){



    std::map<int, std::string> deleted_lines;
    std::map<int, std::string> added_lines;
    std::vector<std::pair<int, int>> swapedElement;
    std::vector<int> modifications;

    std::map<int, std::pair<std::string, std::string>> differences_map =compare(lines_file1, lines_file2); //usuniecie podobnych linijek
    if(differences_map.size()==0){
        return std::make_tuple(added_lines,deleted_lines,swapedElement,modifications);
    }

    auto [first_file_differences_hashmap, second_file_differences_hashmap,firstDifferencesString, secondDifferencesString]
        =convert_to_two_hashmaps_and_strings(differences_map);


    std::vector<char> lcs_vector = fill_dyn_matrix(firstDifferencesString, secondDifferencesString);

    std::string lcss(lcs_vector.begin(), lcs_vector.end());

    //printMap("only  differences ",first_file_differences_hashmap);

    std::map<int, std::string>  result1;
    std::map<int, std::string>  result2;

    std::thread thread1(threadFunction, lcss, std::ref(first_file_differences_hashmap), std::ref(result1));
    std::thread thread2(threadFunction, lcss, std::ref(second_file_differences_hashmap), std::ref(result2));


    thread1.join();
    thread2.join();   // na ten moment widac add i dels


    std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<std::pair<int, int>>> tuple;
    std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<int>> result;

    //printMap("deletes ",result1);
    // printMap("adds",result2);


    tuple=findSwaps(result1,result2,swapedElement,tuple);


    deleted_lines= std::get<0>(tuple);
    added_lines= std::get<1>(tuple);
    swapedElement = std::get<2>(tuple);


    // printMap("deletes po swapach",deleted_lines);
    //printMap("adds po swapach",added_lines);
    // std::cout<<"swapy"<<std::endl;
    //printIdenticalElements(swapedElement);


    std::cout<<"po wyszukiwaniu modyfikacji"<<std::endl;
    //po wyszukiwaniu zmian
    result = findModificationsWithLevenshtein(deleted_lines,added_lines);

    deleted_lines= std::get<0>(result);
    added_lines= std::get<1>(result);
    modifications=std::get<2>(result);
    swapedElement=std::get<2>(tuple);

    //printMap("deletes po swapach",deleted_lines);
    //printMap("adds po swapach",added_lines);
    std::cout<<"swapy"<<std::endl;
    printIdenticalElements(swapedElement);

    return std::make_tuple(added_lines,deleted_lines,swapedElement,modifications);
    //tutaj troche poprawi to dodawanie do tuple

}
