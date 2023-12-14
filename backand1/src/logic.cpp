#include "hash_calculator.h" 
#include "logic.h"
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>
#include <mutex>


//struct HashResult {
//  std::string hash;
 //   std::vector<int> lineNumbers;
//};



bool fileExists(const std::string& filePath) {
    std::ifstream file(filePath);
     return file.good();
}


bool filesIsTheSame(const std::string& firstFilePath,const std::string& secondFilePath){
    
    HashCalculator hasher;
    
    bool first_file_exist = fileExists(firstFilePath); //podwojne sprawdzanie na itnienie pliku wykorzystuje metode z hash_calculator
    bool second_file_exist = fileExists(secondFilePath);
   
    if(!first_file_exist|| !second_file_exist){
        std::cerr << "Error: plik nie istnieje " << std::endl;
        std::terminate();
    }

    std::string first_file_hash = hasher.calculateStringHash(hasher.readFileToString(firstFilePath));
    std::string second_file_hash = hasher.calculateStringHash(hasher.readFileToString(secondFilePath));

    return first_file_hash==second_file_hash;

}




std::pair<std::unordered_map<std::string, std::vector<int>>, int> countHashesAddToHashMaps(const std::string& filePath) {

    std::ifstream file(filePath);

    //znowu sprawdzenie usun
    if (!file.is_open()) {
        std::cerr << "Plik nie otwiera sie " << filePath << std::endl;
        
        return {{}, 0};
    }

    
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
    std::unordered_map<std::string, std::vector<int>> resultMap1, resultMap2;
    int lineNumber1, lineNumber2;
    std::string filePath1 = "file1.txt";
    std::string filePath2 = "file2.txt";

    std::thread thread1([&resultMap1, &lineNumber1, filePath1]() {
        std::tie(resultMap1, lineNumber1) = countHashesAddToHashMaps(filePath1);
    });

    std::thread thread2([&resultMap2, &lineNumber2, filePath2]() {
        std::tie(resultMap2, lineNumber2) = countHashesAddToHashMaps(filePath2);
    });

    thread1.join();
    thread2.join();

    //wyniki
    std::cout << "Thread 1 wynik:\n";
    for (const auto& entry : resultMap1) {
        std::cout << "Klucz: " << entry.first << ", Znaczenie: ";
        for (const auto& value : entry.second) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
    std::cout << "ilosc linijek 1: " << lineNumber1 << "\n";

    std::cout << "\n Thread 2 wynik:\n";
    for (const auto& entry : resultMap2) {
        std::cout << "Klucz: " << entry.first << ", Znaczenie: ";
        for (const auto& value : entry.second) {
            std::cout << value << " ";
        }
        std::cout << "\n";
    }
    std::cout << " ilosc linijek 2: " << lineNumber2 << "\n";

    return 0;
}