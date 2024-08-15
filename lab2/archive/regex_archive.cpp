#include "regex.hpp"

void Regex::parser_error(std::string_view err_msg) {
    std::cerr << "Parser error: " << err_msg << std::endl;
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
                if ((start_pos - 1) != 0) {
                    int counter = 2;

                    for (;;) {
                        // checking for char metasymbol
                        if (this->char_metasymbols.find(cregex[start_pos - counter]) != this->char_metasymbols.end()) {
                            if ((start_pos - counter) != 0) {
                                if (cregex[start_pos - counter - 1] != '%') {
                                    // TODO
                                    is_open_bracket_left = false;
                                    break;
                                }
                                // end handle
                                found_metasymbol = true;
                                counter += 2; 
                            } 
                            else {
                                this->parser_error("Metasymbol without other symbols");
                                break;
                            }
                        }
                        // checking for Kleene closure  
                        // first dot
                        else if (cregex[start_pos - counter] == '.') {
                            if ((start_pos - counter) != 0) {
                                if (cregex[start_pos - counter - 1] != '.') {
                                    // TODO
                                    is_open_bracket_left = false;
                                    break;
                                }
                                // second dot
                                else {
                                    if ((start_pos - counter - 1) != 0) {
                                        if (cregex[start_pos - counter - 2] != '.') {
                                            // TODO
                                            is_open_bracket_left = false;
                                            break;
                                        }
                                        // third dot
                                        else {
                                            if ((start_pos - counter - 2) != 0) {
                                                // check if "..%...%(.."
                                                if (cregex[start_pos - counter - 3] != '%') {
                                                    // TODO
                                                    is_open_bracket_left = false;
                                                    break; 
                                                }
                                                // end handle
                                                found_metasymbol = true;
                                                counter += 4;
                                            }
                                            else {
                                                this->parser_error("'...' with no symbols");
                                                break;
                                            }
                                        }        
                                    }
                                    else {
                                        // TODO
                                        is_open_bracket_left = false;
                                        break;
                                    }
                                }
                            }
                            else {
                                // TODO
                                is_open_bracket_left = false;
                                break;
                            }
                        }
                        // checking for %
                        else if (cregex[start_pos - counter] == '%') {
                            if (double_screen == true) {
                                this->parser_error("No symbols to screen");
                                break;
                            }
                            // TODO
                            // end handle
                            double_screen = true;
                            counter++; 
                        }
                        // no metasymbol | %
                        else {
                            if (!found_metasymbol) {
                                is_open_bracket_left = false;
                                break;
                            }
                            // TODO
                            else {
                                is_open_bracket_left = true;
                                break;
                            }
                        }
                        // next loop
                        if ((start_pos - counter + 1) != 0) {
                            if (double_screen && !found_metasymbol) {
                                is_open_bracket_left = false;
                                break;
                            }
                            // TODO
                            continue;
                        }
                        // exit
                        else {
                            if (double_screen && !found_metasymbol) {
                                this->parser_error("No symbols to screen");
                                break;
                            }
                            // TODO
                            is_open_bracket_left = true;
                            break;
                        }
                    }
                }
                // left side screening
                else {
                    is_open_bracket_left = false;
                }
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
        if (start_pos != cregex.size()) {
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
