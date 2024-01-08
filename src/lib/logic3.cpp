
std::vector<std::pair<int, int>> swapedElement;

// dla ogarniecia zamiany tutaj odrazu i usuwam  z tych tablic  i  tworze nowa
void findSwaps(
    std::map<int, std::string>& deleted_file_one_indexes,
    std::map<int, std::string>& added_file_two_indexes) {
    
    std::vector<int> keys = getKeys(deleted_file_one_indexes);
    std::vector<int> keys2 = getKeys(added_file_two_indexes);//uzyc copy

    std::vector<int> keysToDeleteInMap1, keysToDeleteInMap2;

     for (int key : keys) { 
        std::pair<int,int>swapedForThisIndexElement=findIdenticalElement(deleted_file_one_indexes,added_file_two_indexes, key);
        if(swapedForThisIndexElement.first==0){
            continue;
        }
        else{swapedElement.push_back(swapedForThisIndexElement);
            std::vectorFordelete=elementsForDelete(deleted_file_one_indexes,added_file_two_indexes,key);
            for (auto key : elementsForDelete) {
                deleted_file_one_indexes.erase(key);
                added_file_two_indexes.erase(key+1);
                }
            if(key= keys.size()-1){
                break;
            }
            else{findSwaps(deleted_file_one_indexes,added_file_two_indexes)}
                 
        }
    
    }
}



// dla ogarniecia zamiany tutaj odrazu i usuwam  z tych tablic  i  tworze nowa
void findIdenticalElement(
    std::map<int, std::string>& deleted_file_one_indexes,
    std::map<int, std::string>& added_file_one_indexes,
    int& deleted_file_one_indexe_key;) {

    std::vector<int> keys2 = getKeys(deleted_file_one_indexes);//uzyc copy

    
    std::vector<int> keysToDeleteInMap1, keysToDeleteInMap2;

        for (int key2:keys2) {
            if (deleted_file_one_indexes[key] == added_file_two_indexes[key2]) {

                identicalElements.push_back({key, key2});
                deleted_file_one_indexes.erase(key);
                added_file_two_indexes.erase(key);
                break;
            }
        }
return identicalElements; //pozniej sprawdzic czy jest puste znaczenie czy nie

}

//porwnywanie objektow  jest to zrobione dla wyszukiwania ktory z  linijek jest zmieniony
std::vector<int> elementsForDelete(
    std::map<int, std::string>& deleted_file_one_indexes,
    std::map<int, std::string>& added_file_two_indexes,
    int& startFrom;) {

    std::vector<int> keys = getKeys(deleted_file_one_indexes);//uzyc copy

    std::vector<int> keysToDeleteInMap; 
        for (int key:keys) {
            if (key<startFrom) {
                continue;
            if deleted_file_one_indexes[key]= added_file_two_indexes[key+1]{
                keysToDeleteInMap.push_back[key];
            }   
        }
        }

    // usuniecia po iteracji
return keysToDeleteInMap

}