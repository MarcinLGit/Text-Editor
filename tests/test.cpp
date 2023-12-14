#define BOOST_TEST_MODULE Testy HashCalculatorTests
#include <boost/test/included/unit_test.hpp>
#include "../src/lib/hash_calculator.h" 




BOOST_AUTO_TEST_CASE(empty_string_hash_calculation) {
    HashCalculator hashCalculator;
    
    std::string emptyString = "";
    BOOST_CHECK_EQUAL(hashCalculator.calculateStringHash(emptyString), "e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855");
}

BOOST_AUTO_TEST_CASE(non_empty_string_hash_calculation) {
    HashCalculator hashCalculator;

    std::string input = "Hello, World!";
    BOOST_CHECK_EQUAL(hashCalculator.calculateStringHash(input), "dffd6021bb2bd5b0af676290809ec3a53191dd81c7f70a4b28688a362182986f");
}


BOOST_AUTO_TEST_CASE(try_read_non_existing_file) {
    HashCalculator hashCalculator;

    std::string nonExistingFile = "losowy.txt";
    BOOST_CHECK_EQUAL(hashCalculator.readFileToString(nonExistingFile), "");
}


