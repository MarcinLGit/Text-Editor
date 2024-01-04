#include <iostream>
#include <string>

int main() {
    std::string haystack = "Primer stroki";
    std::string needle = "stroki";

    //  find
    if (haystack.find(needle) != std::string::npos) {
        std::cout << "Stroka '" << needle << "' podstroka '" << haystack << "'." << std::endl;
    } else {
        std::cout << "Stroka '" << needle << "' nie podstroka '" << haystack << "'." << std::endl;
    }

    return 0;
}
