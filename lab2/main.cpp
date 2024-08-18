#include <iostream>
#include "regex.hpp"

int main() {
    Regex regex;
    std::string cregex;
    std::cin >> cregex;

    int return_value = regex.compile(cregex);
    std::cout << "Regcomp return value: " << return_value << std::endl;
    return 0;
}
