#define BOOST_TEST_MODULE Testy
#include <boost/test/included/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_addition) {
    int result = 1 + 1;
    BOOST_TEST(result == 2);
}
