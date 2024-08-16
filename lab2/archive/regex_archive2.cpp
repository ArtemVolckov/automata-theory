#include "regex.hpp"

void Regex::parser_error(std::string_view err_msg) {
    std::cerr << "Parser error: " << err_msg << std::endl << "Compile failed" << std::endl;
}

void Regex::parse_expr(std::string_view cregex) {
    size_t start_pos = cregex.find('(');
    size_t end_pos   = cregex.rfind(')');

    bool is_open_bracket_left  = false, is_open_bracket_right = false;
    bool is_close_bracket_left = false, is_close_bracket_right = false;
    bool double_screen = false, found_metasymbol = false;
    
    // OPEN BRACKET
 
    // if found '(' 
    if (start_pos != std::string_view::npos) {

        // CHECK LEFT SIDE

        // if '(' not at the start
        if (start_pos != 0) {
            // checking for screening
            if (cregex[start_pos - 1] == '%') {
                is_open_bracket_left = false;     
            }
            // if no screening
            else {
                is_open_bracket_left = true;
            }
        }
        // if '(' at the start
        else {
            is_open_bracket_left = true;
        }

        // CHECK RIGHT SIDE
        
        // if '(' not at the end
        if (start_pos != cregex.size() - 1) {
            // checking for screening
            if (cregex[start_pos + 1] == '%') {
                is_open_bracket_right = false;
            }
            // checking for capture group
            if (cregex[start_pos + 1] == '<')
            // if no screening
            else {
                is_open_bracket_right = true;
            }
        }
        // if '(' at the end
        else {
            this->parser_error("'(' without ')'");
        }
    }

    // CLOSE BRACKET
    
    // if found ')' 
    if (end_pos != std::string_view::npos) {

        // CHECK LEFT SIDE
        
        // CHECK RIGHT SIDE
    
    }
}

void Regex::compile(std::string_view cregex) {
    this->parse_expr(cregex);
}
