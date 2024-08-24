#include <iostream>
#include <limits>
#include "regex.hpp"

int main() {
    Regex regex;
    RegexData regex_data;
    std::string cregex;
    std::string string_to_check;
    bool is_match = false, is_end = false;
    int variant;

    std::cout << "Menu:" << std::endl;
    std::cout << "0.Exit" << std::endl;
    std::cout << "1.Compile" << std::endl;
    std::cout << "2.Match without compile" << std::endl;
    std::cout << "3.Match with compile" << std::endl;
    std::cout << "4.Search without compile" << std::endl;
    std::cout << "5.Search with compile" << std::endl;
    std::cout << "6.Inverse regex" << std::endl;
    std::cout << "7.Complement regex" << std::endl;
    std::cout << "8.Print DFA" << std::endl;
    std::cout << "9.Print menu" << std::endl;

    while (1) {
        std::cin >> variant;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Wrong input: try again" << std::endl;
            continue;
        }
        if (variant < 0 || variant > 9) {
            std::cout << "'"<< variant << "' is out of range: try again" << std::endl;
            continue;
        }
        try {
            switch (variant) {
                case 0:
                    is_end = true;
                    break;
                case 1:
                    std::cout << "Enter a regular expression:" << std::endl;
                    std::cin >> cregex;
                    regex.compile(cregex);
                    std::cout << "Successful compilation" << std::endl;
                    break;
                case 2:
                    std::cout << "Enter string to match:" << std::endl;
                    std::cin >> string_to_check;
                    
                    if (regex.match(string_to_check, regex_data)) { 
                        std::cout << "match (" << regex_data.get_matched_string() << ")" << std::endl;
                        std::cout << "Named groups:" << std::endl;

                        for (const auto pair: regex_data)
                            std::cout << pair.first << " (" << pair.second << ")" << std::endl;
                    }
                    else 
                        std::cout << "nomatch" << std::endl; 
                    break;
                case 3:
                    std::cout << "Enter a regular expression:" << std::endl;
                    std::cin >> cregex;
                     
                    std::cout << "Enter string to match:" << std::endl;
                    std::cin >> string_to_check;
                    
                    if (regex.match(cregex, string_to_check, regex_data)) { 
                        std::cout << "match (" << regex_data.get_matched_string() << ")" << std::endl;
                        std::cout << "Named groups:" << std::endl;

                        for (const auto pair: regex_data)
                            std::cout << pair.first << " (" << pair.second << ")" << std::endl;
                    }
                    else 
                        std::cout << "nomatch" << std::endl; 
                    break;
                case 4:
                    std::cout << "Enter string to search:" << std::endl;
                    std::cin >> string_to_check;
                    
                    if (regex.search(string_to_check, regex_data)) { 
                        std::cout << "match (" << regex_data.get_matched_string() << ")" << std::endl;
                        std::cout << "Named groups:" << std::endl;

                        for (const auto pair: regex_data)
                            std::cout << pair.first << " (" << pair.second << ")" << std::endl;
                    }
                    else 
                        std::cout << "nomatch" << std::endl; 
                    break;
                case 5:
                    std::cout << "Enter a regular expression:" << std::endl;
                    std::cin >> cregex;
                    
                    std::cout << "Enter string to search:" << std::endl;
                    std::cin >> string_to_check;
                    
                    if (regex.search(cregex, string_to_check, regex_data)) { 
                        std::cout << "match (" << regex_data.get_matched_string() << ")" << std::endl;
                        std::cout << "Named groups:" << std::endl;

                        for (const auto pair: regex_data)
                            std::cout << pair.first << " (" << pair.second << ")" << std::endl;
                    }
                    else 
                        std::cout << "nomatch" << std::endl; 
                    break;
                case 6:
                    regex.inverse_regex();
                    std::cout << "Successful inversion" << std::endl;
                    break;
                case 7:
                    regex.complement_regex();
                    std::cout << "Successful complement" << std::endl;
                    break;
                case 8:
                    regex.print_dfa();
                    break;
                case 9:
                    std::cout << std::endl;
                    std::cout << "Menu:" << std::endl;
                    std::cout << "0.Exit" << std::endl;
                    std::cout << "1.Compile" << std::endl;
                    std::cout << "2.Match without compile" << std::endl;
                    std::cout << "3.Match with compile" << std::endl;
                    std::cout << "4.Search without compile" << std::endl;
                    std::cout << "5.Search with compile" << std::endl;
                    std::cout << "6.Inverse regex" << std::endl;
                    std::cout << "7.Complement regex" << std::endl;
                    std::cout << "8.Print DFA" << std::endl;
                    std::cout << "9.Print menu" << std::endl;
            }
            if (is_end) 
                break;
        }
        catch(...) {
            continue;
        }
    }
    return 0;
}
