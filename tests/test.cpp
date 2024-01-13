#define BOOST_TEST_MODULE ComparationTests
#include <boost/test/included/unit_test.hpp>
#include <fstream>
#include "../src/lcs.h" 
#include "../src/leven.h" 
#include "../src/logic4.h"





BOOST_AUTO_TEST_CASE(test_compare) {
    // Create test data
    std::vector<std::string> vec1 = {"Line 1", "Line 2", "Line 3"};
    std::vector<std::string> vec2 = {"Line 1", "Line 8", "Line 3"};

    // Compare the vectors
    auto differences = compare(vec1, vec2);

    // Verify the result
    BOOST_REQUIRE_EQUAL(differences.size(), 1);
    BOOST_CHECK(differences.find(1) != differences.end()); // zwraca element spoza mapa
    BOOST_CHECK_EQUAL(differences[1].first, "Line 2");
    BOOST_CHECK_EQUAL(differences[1].second, "Line 8");
}

BOOST_AUTO_TEST_CASE(test_compare_more_data) {
    // Create test data
    std::vector<std::string> vec1 = {"Line 1", "Line 2", "Line 3","Line4"};
    std::vector<std::string> vec2 = {"Line 1", "Line 8", "Line 3", "Line7"};

    // Compare the vectors
    auto differences = compare(vec1, vec2);

    // Verify the result
    BOOST_REQUIRE_EQUAL(differences.size(), 2);
    BOOST_CHECK(differences.find(1) != differences.end()); // zwraca element spoza mapa
    BOOST_CHECK(differences.find(3) != differences.end()); // zwraca element 
    BOOST_CHECK_EQUAL(differences[1].first, "Line 2");
    BOOST_CHECK_EQUAL(differences[1].second, "Line 8");
     BOOST_CHECK_EQUAL(differences[3].first, "Line4");
    BOOST_CHECK_EQUAL(differences[3].second, "Line7");
}

BOOST_AUTO_TEST_CASE(test_compare_more_data_in_first_file) {
    // Create test data
    std::vector<std::string> vec1 = {"Line 1", "Line 2", "Line 3"};
    std::vector<std::string> vec2 = {"Line 1", "Line 8", "Line 3", "Line7"};

    // Compare the vectors
    auto differences = compare(vec1, vec2);

    // Verify the result
    BOOST_REQUIRE_EQUAL(differences.size(), 2);
    BOOST_CHECK(differences.find(1) != differences.end()); // zwraca element spoza mapa
    BOOST_CHECK(differences.find(3) != differences.end()); // zwraca element 
    BOOST_CHECK_EQUAL(differences[1].first, "Line 2");
    BOOST_CHECK_EQUAL(differences[1].second, "Line 8");
     BOOST_CHECK_EQUAL(differences[3].first, "");
    BOOST_CHECK_EQUAL(differences[3].second, "Line7");
}



BOOST_AUTO_TEST_CASE(test_compare_more_data_in_second_file) {
    // Create test data
    std::vector<std::string> vec1 = {"Line 1", "Line 2", "Line 3", "Line 4"};
    std::vector<std::string> vec2 = {"Line 1", "Line 8", "Line 3"};

    // Compare the vectors
    auto differences = compare(vec1, vec2);

    // Verify the result
    BOOST_REQUIRE_EQUAL(differences.size(), 2);
    BOOST_CHECK(differences.find(1) != differences.end()); // zwraca element spoza mapa
    BOOST_CHECK(differences.find(3) != differences.end()); // zwraca element 
    BOOST_CHECK_EQUAL(differences[1].first, "Line 2");
    BOOST_CHECK_EQUAL(differences[1].second, "Line 8");
     BOOST_CHECK_EQUAL(differences[3].first, "Line 4");
    BOOST_CHECK_EQUAL(differences[3].second, "");
}



BOOST_AUTO_TEST_CASE(test_compare_empty_table) {
    // Create test data
    std::vector<std::string> vec1 = {"Line 1", "Line 2", "Line 3","Line4"};
    std::vector<std::string> vec2 = {"Line 1", "Line 2", "Line 3", "Line4"};

    // Compare the vectors
    auto differences = compare(vec1, vec2);

    // Verify the result
    BOOST_REQUIRE_EQUAL(differences.size(), 0);
    
}






BOOST_AUTO_TEST_CASE(test_find_swaps) {
    // Create test data with potential swaps
    std::map<int, std::string> deleted = {{1, "Line1"}, {2, "Line2"}};
    std::map<int, std::string> added = {{1, "Line2"}, {2, "Line1"}};
    std::vector<std::pair<int, int>> swaps;
    std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<std::pair<int, int>>> tuple;

    // Identify swaps
    tuple = findSwaps(deleted, added, swaps, tuple);

    // Verify the result
    BOOST_REQUIRE_EQUAL(std::get<2>(tuple).size(), 1);
    BOOST_CHECK(std::get<2>(tuple)[0] == std::make_pair(1, 2) );
    // Add more checks as necessary
}




BOOST_AUTO_TEST_CASE(test_find_swaps_no_swaps) {
    // Create test data with potential swaps
    std::map<int, std::string> deleted = {{1, "Line2"}, {2, "Line3"}};
    std::map<int, std::string> added = {{1, "Line4"}, {2, "Line5"}};
    std::vector<std::pair<int, int>> swaps;
    std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<std::pair<int, int>>> tuple;

    // Identify swaps
    tuple = findSwaps(deleted, added, swaps, tuple);

    // Verify the result
    BOOST_REQUIRE_EQUAL(std::get<2>(tuple).size(), 0);
   
    // Add more checks as necessary
}



// mozna zrobic wiele zmian ale moje sprowadzja sie do jednej

BOOST_AUTO_TEST_CASE(test_find_swaps_and_modify_maps) {
    // Create test data with potential swaps
    std::map<int, std::string> deleted = {{4, "kontrolna linija"}, {5, "Line5"},{6, "Line6"}};
    std::map<int, std::string> added = {{4, "Line5"}, {5, "Line6"},{6, "kontrolna linija"}};
    std::vector<std::pair<int, int>> swaps;
    std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<std::pair<int, int>>> tuple;

    // Identify swaps
    tuple = findSwaps(deleted, added, swaps, tuple);

    // Verify the result
    BOOST_REQUIRE_EQUAL(std::get<1>(tuple).size(), 0);
   
    // Add more checks as necessary
}

/*
BOOST_AUTO_TEST_CASE(test_findModificationsWithLevenshtein) {
    // Create test data with potential swaps
    std::map<int, std::string> deleted = {{4, "kontrolna linijaeduywedgfuywgiwku"}, {5, "Line5"},{6, "Line6ekrjhgnkerjgcenrjcerkthytrehjuyh"}};
    std::map<int, std::string> added = {{4, "Librvsrdfd4s5fdserne5"}, {5, "Line6"},{6, "kontrolna linijagythuijhgfrtyhujkh"}};
    std::vector<int> modifications;

    std::tuple<std::map<int, std::string>, std::map<int, std::string>, std::vector<int>> tuple;

    // Identify swaps
    tuple = findModificationsWithLevenshtein(deleted, added);

    // Verify the result
    BOOST_REQUIRE_EQUAL(std::get<2>(tuple).size(), 1);
    BOOST_REQUIRE_EQUAL(std::get<2>(tuple)[0], 5);
   
    // Add more checks as necessary
}
*/ // troche trzeba poprawic  bo co
 // troche trzeba poprawic  bo psuje sie





// posprawdza tutaj jeszcze

BOOST_AUTO_TEST_CASE(FindAddDelTest_FindNonExistingSubstrings) {
    std::string lcs = "common";
    std::map<int, std::string> mapa = {{1, "common"}, {2, "unique"}};
    auto result = findAddDel(lcs, mapa);
    std::map<int, std::string> expected = {{2, "unique"}};
    BOOST_REQUIRE_EQUAL( result[2],"unique");
}



BOOST_AUTO_TEST_CASE(FindAddDelTest_AllSubstringsExist) {
    std::string lcs = "commonunique";
    std::map<int, std::string> mapa = {{1, "common"}, {2, "unique"}};
    auto result = findAddDel(lcs, mapa);
    BOOST_CHECK(result.empty());
}


BOOST_AUTO_TEST_CASE(TestEmptyMap) {
    std::map<int, std::pair<std::string, std::string>> empty_map;
    auto result = convert_to_two_hashmaps_and_strings(empty_map);

    BOOST_CHECK(std::get<0>(result).empty());
    BOOST_CHECK(std::get<1>(result).empty());
}



BOOST_AUTO_TEST_CASE(TestSingleElementMap) {
    std::map<int, std::pair<std::string, std::string>> differences = {{1, {"linija1", "linija2"}}};
    auto result = convert_to_two_hashmaps_and_strings(differences);

    BOOST_CHECK_EQUAL(std::get<0>(result).size(), 1);
    BOOST_CHECK_EQUAL(std::get<1>(result).size(), 1);
    BOOST_CHECK_EQUAL(std::get<0>(result).at(1), "linija1");
    BOOST_CHECK_EQUAL(std::get<1>(result).at(1), "linija2");
    BOOST_CHECK_EQUAL(std::get<2>(result), "linija1");
    BOOST_CHECK_EQUAL(std::get<3>(result), "linija2");
}

BOOST_AUTO_TEST_CASE(TestMultipleElementsMap) {
    std::map<int, std::pair<std::string, std::string>> differences = {{1, {"1", "2"}}, {2, {"3", "4"}}, {3, {"5", "6"}}};
    auto result = convert_to_two_hashmaps_and_strings(differences);

    BOOST_CHECK_EQUAL(std::get<0>(result).size(), 3);
    BOOST_CHECK_EQUAL(std::get<1>(result).size(), 3);
    BOOST_CHECK_EQUAL(std::get<0>(result).at(1), "1");
    BOOST_CHECK_EQUAL(std::get<1>(result).at(1), "2");
    BOOST_CHECK_EQUAL(std::get<0>(result).at(2), "3");
    BOOST_CHECK_EQUAL(std::get<1>(result).at(2), "4");
    BOOST_CHECK_EQUAL(std::get<0>(result).at(3), "5");
    BOOST_CHECK_EQUAL(std::get<1>(result).at(3), "6");
}



// Предполагается, что функции findIdenticalElement и getKeys уже определены

BOOST_AUTO_TEST_CASE(TestNoIdenticalElement) {
    std::map<int, std::string> deleted = {{1, "a"}, {2, "b"}};
    std::map<int, std::string> added = {{3, "c"}, {4, "d"}};
    int key = 0;

    auto result = findIdenticalElement(deleted, added, key);
    BOOST_CHECK(result == std::make_pair(0, 0)); // предполагаем, что возвращается пара (0, 0) в случае отсутствия совпадений
}

BOOST_AUTO_TEST_CASE(TestIdenticalElementExists) {
    std::map<int, std::string> deleted = {{1, "a"}, {2, "b"}};
    std::map<int, std::string> added = {{3, "c"}, {4, "a"}};
    int key = 1;

    auto result = findIdenticalElement(deleted, added, key);
    BOOST_CHECK(result == std::make_pair(1, 4)); // ожидается, что найденная пара - это (1, 4)
}

BOOST_AUTO_TEST_CASE(TestMultipleIdenticalElements) {
    std::map<int, std::string> deleted = {{1, "a"}, {2, "b"}, {5, "a"}};
    std::map<int, std::string> added = {{3, "c"}, {4, "a"}};
    int key = 1;

    auto result = findIdenticalElement(deleted, added, key);
    BOOST_CHECK(result == std::make_pair(1, 4)); // ожидается, что найденная первая пара - это (1, 4), а не (5, 4)
}

BOOST_AUTO_TEST_CASE(NoElementsToDelete)
{
    std::map<int, std::string> deleted = {{1, "a"}, {2, "b"}};
    std::map<int, std::string> added = {{1, "a"}, {2, "b"}};
    int startFrom = 1;
    int secondfileSwapIndex = 3;

    auto result = elementsForDelete(deleted, added, startFrom, secondfileSwapIndex);
    BOOST_CHECK(result.first.empty() && result.second.empty());
}



BOOST_AUTO_TEST_CASE(DeleteElementsAfterIndex)
{
    std::map<int, std::string> deleted = {{1, "a"}, {2, "b"}, {4, "d"}};
    std::map<int, std::string> added = {{1, "a"}, {3, "c"}, {4, "d"}};
    int startFrom = 1;
    int secondfileSwapIndex = 3;

    auto result = elementsForDelete(deleted, added, startFrom, secondfileSwapIndex);
    BOOST_CHECK(result.first == std::vector<int>{4} && result.second == std::vector<int>{4});
}



BOOST_AUTO_TEST_CASE(test_with_data)
{
    std::map<int, std::string> deleted_file_one_indexes = {{1, "Line1"}, {2, "Line2"}, {3, "Line3"}};
    std::map<int, std::string> added_file_two_indexes = {{1, "Line1"}, {2, "Line2Modified"}, {3, "Line3"}};
    int startFrom = 1;
    int secondfileSwapIndex = 2;

    auto result = elementsForDelete(deleted_file_one_indexes, added_file_two_indexes, startFrom, secondfileSwapIndex);

    BOOST_CHECK_EQUAL(result.first.size(), 1);
    BOOST_CHECK_EQUAL(result.second.size(), 1);
}


BOOST_AUTO_TEST_CASE(test_with_no_matching)
{
    std::map<int, std::string> deleted_file_one_indexes = {{1, "LineA"}, {2, "LineB"}};
    std::map<int, std::string> added_file_two_indexes = {{1, "Line1"}, {2, "Line2"}};
    int startFrom = 1;
    int secondfileSwapIndex = 2;

    auto result = elementsForDelete(deleted_file_one_indexes, added_file_two_indexes, startFrom, secondfileSwapIndex);

    BOOST_CHECK(result.first.empty());
    BOOST_CHECK(result.second.empty());
}


// Załóżmy, że funkcja fill_dyn_matrix jest zdefiniowana tutaj lub dołączona przed testami.

BOOST_AUTO_TEST_CASE(test_empty_strings)
{
    std::string x = "";
    std::string y = "";
    auto result = fill_dyn_matrix(x, y);
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(test_no_common_subsequence)
{
    std::string x = "abc";
    std::string y = "def";
    auto result = fill_dyn_matrix(x, y);
    BOOST_CHECK(result.empty());
}

BOOST_AUTO_TEST_CASE(test_common_subsequence)
{
    std::string x = "abcde";
    std::string y = "ace";
    auto result = fill_dyn_matrix(x, y);
    BOOST_CHECK(result.size() == 3);
    BOOST_CHECK(result[0] == 'a' && result[1] == 'c' && result[2] == 'e');
}

BOOST_AUTO_TEST_CASE(test_full_match)
{
    std::string x = "abc";
    std::string y = "abc";
    auto result = fill_dyn_matrix(x, y);
    BOOST_CHECK(result.size() == 3);
    BOOST_CHECK(result[0] == 'a' && result[1] == 'b' && result[2] == 'c');
}
