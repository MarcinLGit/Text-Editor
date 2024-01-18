#define BOOST_TEST_MODULE ComparationTests
#include <boost/test/included/unit_test.hpp>
#include <fstream>
#include "../src/lib/lcs.h" 
#include "../src/lib/logic4.h"
#include <iostream>
#include <utility>

template<typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
    return os << "(" << p.first << ", " << p.second << ")";
}




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




BOOST_AUTO_TEST_CASE(TestNoIdenticalElement) {
    std::map<int, std::string> deleted = {{1, "a"}, {2, "b"}};
    std::map<int, std::string> added = {{3, "c"}, {4, "d"}};
    int key = 0;

    auto result = findIdenticalElement(deleted, added, key);
    BOOST_CHECK(result == std::make_pair(0, 0));
}

BOOST_AUTO_TEST_CASE(TestIdenticalElementExists) {
    std::map<int, std::string> deleted = {{1, "a"}, {2, "b"}};
    std::map<int, std::string> added = {{3, "c"}, {4, "a"}};
    int key = 1;

    auto result = findIdenticalElement(deleted, added, key);
    BOOST_CHECK(result == std::make_pair(1, 4)); 
}

BOOST_AUTO_TEST_CASE(TestMultipleIdenticalElements) {
    std::map<int, std::string> deleted = {{1, "a"}, {2, "b"}, {5, "a"}};
    std::map<int, std::string> added = {{3, "c"}, {4, "a"}};
    int key = 1;

    auto result = findIdenticalElement(deleted, added, key);
    BOOST_CHECK(result == std::make_pair(1, 4)); 
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



BOOST_AUTO_TEST_CASE(test_no_common_subsequence_procent)
{
    std::string x = "abc";
    std::string y = "def";
    double result = lcsPercentage(x, y);
    BOOST_CHECK_EQUAL(result, 0.0);
}


BOOST_AUTO_TEST_CASE(test_common_subsequence_procent)
{
    std::string x = "abcde";
    std::string y = "ace";
    double result = lcsPercentage(x, y);
    BOOST_CHECK_CLOSE(result, 60.0, 0.01); // 'ace' is 60% of 'abcde'
}


BOOST_AUTO_TEST_CASE(test_full_match_procent)
{
    std::string x = "abc";
    std::string y = "abc";
    double result = lcsPercentage(x,
y);
BOOST_CHECK_EQUAL(result, 100.0); // Full match should return 100%
}

BOOST_AUTO_TEST_CASE(test_partial_match_procent)
{
std::string x = "abcdef";
std::string y = "abc";
double result = lcsPercentage(x, y);
BOOST_CHECK_CLOSE(result, 50.0, 0.01); // 'abc' is 50% of 'abcdef'
}

BOOST_AUTO_TEST_CASE(test_different_length_strings_proces)
{
std::string x = "abcd";
std::string y = "bc";
double result = lcsPercentage(x, y);
BOOST_CHECK_CLOSE(result, 50.0, 0.01); // 'bc' is 50% of 'abcd'
}




std::map<int, std::string> CreateMap(const std::initializer_list<std::pair<const int, std::string>>& list) {
    return std::map<int, std::string>(list);
}

BOOST_AUTO_TEST_CASE(NoModifications) {
    auto deleted = CreateMap({{1, "line dfvcgsdfv"}, {2, "line2"}});
    auto added = CreateMap({{1, "line1"}, {2, "linefdvgsg"}});
    auto result = findModificationsWithLevenshtein(deleted, added);
    BOOST_CHECK_EQUAL(std::get<2>(result).size(),0);
}

BOOST_AUTO_TEST_CASE(SomeModifications) {
    auto deleted = CreateMap({{1, "linedfvsg"}, {2, "lineline3"}});
    auto added = CreateMap({{1, "linelvhui"}, {2, "lineline4"}});
    auto result = findModificationsWithLevenshtein(deleted, added);
    BOOST_CHECK_EQUAL(std::get<2>(result).size(), 1);
    BOOST_CHECK_EQUAL(std::get<2>(result)[0], 2);
}

BOOST_AUTO_TEST_CASE(AllModifications) {
    auto deleted = CreateMap({{1, "linijka1"}, {2, "linijka3"}});
    auto added = CreateMap({{1, "linibka1"}, {2, "linijka4"}});
    auto result = findModificationsWithLevenshtein(deleted, added);
    BOOST_CHECK_EQUAL(std::get<2>(result).size(), 2);
}



BOOST_AUTO_TEST_CASE(NoDifferencesInMain) {
    std::vector<std::string> file1 = {"line1", "line2"};
    std::vector<std::string> file2 = {"line1", "line2"};
    auto result = mainFunction(file1, file2);
    BOOST_CHECK(std::get<0>(result).empty()); 
    BOOST_CHECK(std::get<1>(result).empty()); 
    BOOST_CHECK(std::get<2>(result).empty()); 
    BOOST_CHECK(std::get<3>(result).empty()); 
}



BOOST_AUTO_TEST_CASE(FileDifferencesTestInMain1) {
    std::vector<std::string> file1 = {"linija 1", "linija 2", "kontrolna linija", "linija 3", "linija 4", "linija 6", ""};
    std::vector<std::string> file2 = {"linija 1", "linija 2", "linija 4", "kontrolna linija", "linija 5", "linija 6", ""};
    
    auto result = mainFunction(file1, file2);

    // Assuming mainFunction returns a tuple of maps and vectors as per your code structure
    // Check the added lines
    BOOST_CHECK_EQUAL(std::get<0>(result).size(), 1);
    BOOST_CHECK_EQUAL(std::get<0>(result)[4], "linija 5");

    // Check the deleted lines
    BOOST_CHECK_EQUAL(std::get<1>(result).size(), 1);
    BOOST_CHECK_EQUAL(std::get<1>(result)[3], "linija 3");

    // Check the swapped elements
    BOOST_CHECK_EQUAL(std::get<2>(result).size(), 1);
    BOOST_CHECK_EQUAL(std::get<2>(result)[0].first, 4); 
    BOOST_CHECK_EQUAL(std::get<2>(result)[0].second, 2); 

    // Check for no modifications
    BOOST_CHECK(std::get<3>(result).empty()); 
}