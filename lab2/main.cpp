#include <iostream>
#include "regex.hpp"

int main() {
    Regex regex;
    std::string cregex;
    std::cin >> cregex;
    std::cout << regex.compile(cregex) << std::endl; 
    return 0;
}
