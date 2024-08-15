#include "regex.hpp"

int main() {
    Regex regex;
    std::string cregex;
    std::cin >> cregex;
    regex.compile(cregex); 
    return 0;
}
