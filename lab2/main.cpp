#include <iostream>
#include "regex.hpp"

int main() {
    Regex regex;
    RegexData regex_data;
    std::string cregex;
    std::string string_to_match;
    bool is_match;
    std::cout << "Enter a regular expression:" << std::endl;
    std::cin >> cregex;

    try {
        regex.compile(cregex);

        while (1) {
            std::cout << "Enter string to match:" << std::endl;

            if (!(std::cin >> string_to_match)) 
                break; 
            is_match = regex.match(string_to_match, regex_data);
            
            if (is_match) { 
                std::cout << "match (" << regex_data.get_matched_string() << ")" << std::endl;
                std::cout << "Named groups:" << std::endl;

                for (const auto pair: regex_data)
                    std::cout << pair.first << " (" << pair.second << ")" << std::endl;
            }
            else 
                std::cout << "nomatch" << std::endl; 
        }
    }
    catch(...) {
        return 1;
    }
    return 0;
}
