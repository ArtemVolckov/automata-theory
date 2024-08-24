#include "regex.hpp"
#include "ast.hpp"
#include "nfa_dfa.hpp"

struct Regex::MinNdfaImpl {
    std::vector<Dfa*> min_ndfa;

    MinNdfaImpl(std::vector<Dfa*>& min_ndfa) {
        this->min_ndfa = min_ndfa;
    }

    ~MinNdfaImpl() {
        for (int i = 0; i < min_ndfa.size(); ++i)
            delete min_ndfa.at(i);
    }
};

Regex::~Regex() {
    delete pMinNdfaImpl;
}

void Regex::compile(std::string_view cregex) {
    Parser parser(cregex);
    Ast ast(parser.parse_expr());
    std::vector<std::string> group_names;

    try {
        if (parser.is_error)
            throw std::invalid_argument(parser.err_msg);
        if (parser.position != cregex.length())
            throw std::invalid_argument("Expression parsing error");
        if (!ast.prepare(group_names))
            throw std::invalid_argument("Duplicate names were found for the groups"); 
    }
    catch (const std::invalid_argument& e) {
        std::cerr << e.what() << std::endl;
        std::cerr << "Parser error: Compilation failed" << std::endl;
        throw;
    } 
    std::vector<Nfa*> nnfa;
    Nfa nfa;
    nnfa.push_back(&nfa);
    nnfa_init(nnfa, ast.root, 0);
    nnfa_prepare(nnfa);

    std::vector<Dfa*> ndfa = nfa_to_dfa(nnfa);

    std::vector<Dfa*> min_ndfa = minimize_dfa(ndfa);

#if 0
    std::cout << std::endl << "NFA COUNT = " << nnfa.size() << std::endl;
    print_nnfa(nnfa);

    std::cout << "DFA COUNT = " << ndfa.size() << std::endl;
    print_ndfa(ndfa);

    std::cout << "MIN DFA COUNT = " << min_ndfa.size() << std::endl;
    print_ndfa(min_ndfa);
#endif

    for (int i = 1; i < nnfa.size(); ++i)
        delete nnfa.at(i);
    for (int i = 0; i < ndfa.size(); ++i)
        delete ndfa.at(i);

    delete this->pMinNdfaImpl; 
    this->pMinNdfaImpl = new MinNdfaImpl(min_ndfa);

    is_compiled = true;
}

bool Regex::group_match(int group_dfa_num, std::string_view string_to_check, int& position, RegexData& data) {
    Dfa* group_dfa = pMinNdfaImpl->min_ndfa.at(group_dfa_num);
    bool is_find = false;
    int current_state = 0;
    int position_save = position;

    for (;position < string_to_check.length(); ++position) {
        char symbol = string_to_check.at(position);

        if (current_state >= group_dfa->transitions.size()) {
            if (group_dfa->final_states.count(current_state) > 0) {
                for (int i = 0; i < data.captured_groups.size(); ++i) {
                    if (data.captured_groups.at(i).first == group_dfa->name) {
                        data.captured_groups.at(i).second = string_to_check.substr(position_save, position);
                        return true;
                    }
                }
                std::pair<std::string, std::string> pair(group_dfa->name, string_to_check.substr(position_save, position));
                data.captured_groups.push_back(pair);
                return true;
            }
            else {
                return false;
            }
        }
        Adjacency_list* current_transition = group_dfa->transitions.at(current_state);

        while (current_transition) {
            if (std::holds_alternative<std::pair<char, int>>(current_transition->transition)) {
                std::pair<char, int> pair = std::get<std::pair<char, int>>(current_transition->transition);
                
                if (pair.first == symbol) {
                    current_state = pair.second;
                    is_find = true;
                    break;
                }
            }
            else {
                std::pair<std::string, int> pair = std::get<std::pair<std::string, int>>(current_transition->transition);
                int group_dfa_num;

                for (group_dfa_num = 0; group_dfa_num < pMinNdfaImpl->min_ndfa.size(); ++group_dfa_num) {
                    if (pMinNdfaImpl->min_ndfa.at(group_dfa_num)->name == pair.first) 
                        break;
                }
                if (!group_match(group_dfa_num, string_to_check, position, data)) 
                    return false;
                position--;
                current_state = pair.second;
                is_find = true;
                break;
            }        
            current_transition = current_transition->next;
        }
        if (is_find) {
            is_find = false;
            continue;
        }
        if (group_dfa->final_states.count(current_state) > 0) {
            for (int i = 0; i < data.captured_groups.size(); ++i) {
                if (data.captured_groups.at(i).first == group_dfa->name) {
                    data.captured_groups.at(i).second = string_to_check.substr(position_save, position);
                    return true;
                }
            }
            std::pair<std::string, std::string> pair(group_dfa->name, string_to_check.substr(position_save, position));
            data.captured_groups.push_back(pair);
            return true;
        }
        return false;
    }
    if (group_dfa->final_states.count(current_state) > 0) {
        for (int i = 0; i < data.captured_groups.size(); ++i) {
            if (data.captured_groups.at(i).first == group_dfa->name) {
                data.captured_groups.at(i).second = string_to_check.substr(position_save, position);
                return true;
            }
        }
        std::pair<std::string, std::string> pair(group_dfa->name, string_to_check.substr(position_save, position));
        data.captured_groups.push_back(pair);
        return true;
    }
    return false;
}

bool Regex::match(std::string_view string_to_match, RegexData& data) {
    if (!is_compiled) {
        std::cerr << "Error: The regular expression is not compiled. Please call the compile() method first." << std::endl;
        throw std::logic_error("Error");
    }
    data.matched_string = "";
    data.captured_groups.clear();
    bool is_find = false;
    int current_state = 0;
    Dfa* min_dfa = pMinNdfaImpl->min_ndfa.at(0);
    
    for (int i = 0; i < string_to_match.length(); ++i) {
        char symbol = string_to_match.at(i);

        if (current_state >= min_dfa->transitions.size()) {
            data.captured_groups.clear();
            return false;
        }
        Adjacency_list* current_transition = min_dfa->transitions.at(current_state);

        while (current_transition) {
            if (std::holds_alternative<std::pair<char, int>>(current_transition->transition)) {
                std::pair<char, int> pair = std::get<std::pair<char, int>>(current_transition->transition);
                
                if (pair.first == symbol) {
                    current_state = pair.second;
                    is_find = true;
                    break;
                }
            }
            else {
                std::pair<std::string, int> pair = std::get<std::pair<std::string, int>>(current_transition->transition);
                int group_dfa_num;

                for (group_dfa_num = 0; group_dfa_num < pMinNdfaImpl->min_ndfa.size(); ++group_dfa_num) {
                    if (pMinNdfaImpl->min_ndfa.at(group_dfa_num)->name == pair.first) 
                        break;
                }
                if (!group_match(group_dfa_num, string_to_match, i, data)) {
                    data.captured_groups.clear();
                    return false;
                }
                i--;
                current_state = pair.second;
                is_find = true;
                break;
            }        
            current_transition = current_transition->next;
        }
        if (is_find) {
            is_find = false;
            continue;
        }
        data.captured_groups.clear();
        return false;
    }
    if (min_dfa->final_states.count(current_state) > 0) {
        data.matched_string = string_to_match;
        return true;
    }
    data.captured_groups.clear();
    return false;
}

bool Regex::match(std::string_view cregex, std::string_view string_to_match, RegexData& data) {
    compile(cregex);

    data.matched_string = "";
    data.captured_groups.clear();
    bool is_find = false;
    int current_state = 0;
    Dfa* min_dfa = pMinNdfaImpl->min_ndfa.at(0);
    
    for (int i = 0; i < string_to_match.length(); ++i) {
        char symbol = string_to_match.at(i);

        if (current_state >= min_dfa->transitions.size()) {
            data.captured_groups.clear();
            return false;
        }
        Adjacency_list* current_transition = min_dfa->transitions.at(current_state);

        while (current_transition) {
            if (std::holds_alternative<std::pair<char, int>>(current_transition->transition)) {
                std::pair<char, int> pair = std::get<std::pair<char, int>>(current_transition->transition);
                
                if (pair.first == symbol) {
                    current_state = pair.second;
                    is_find = true;
                    break;
                }
            }
            else {
                std::pair<std::string, int> pair = std::get<std::pair<std::string, int>>(current_transition->transition);
                int group_dfa_num;

                for (group_dfa_num = 0; group_dfa_num < pMinNdfaImpl->min_ndfa.size(); ++group_dfa_num) {
                    if (pMinNdfaImpl->min_ndfa.at(group_dfa_num)->name == pair.first) 
                        break;
                }
                if (!group_match(group_dfa_num, string_to_match, i, data)) {
                    data.captured_groups.clear();
                    return false;
                }
                i--;
                current_state = pair.second;
                is_find = true;
                break;
            }        
            current_transition = current_transition->next;
        }
        if (is_find) {
            is_find = false;
            continue;
        }
        data.captured_groups.clear();
        return false;
    }
    if (min_dfa->final_states.count(current_state) > 0) {
        data.matched_string = string_to_match;
        return true;
    }
    data.captured_groups.clear();
    return false;
}

bool Regex::search(std::string_view string_to_search, RegexData& data) {
    if (!is_compiled) {
        std::cerr << "Error: The regular expression is not compiled. Please call the compile() method first." << std::endl;
        throw std::logic_error("Error");
    }
    if (match("", data))
        return true;
    for (int i = 0; i <= string_to_search.size(); ++i) {
        if (match(string_to_search.substr(0, i), data))
            return true;
    }
    return false;
}

bool Regex::search(std::string_view cregex, std::string_view string_to_search, RegexData& data) {
    compile(cregex);
    
    if (match("", data))
        return true;
    for (int i = 0; i <= string_to_search.size(); ++i) {
        if (match(string_to_search.substr(0, i), data))
            return true;
    }
    return false;
}
