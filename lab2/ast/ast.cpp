#include "ast.hpp"

void Parser::report(std::string_view err_msg) {
    this->err_msg = err_msg;   
}

void Parser::print_report_and_abort() {
    std::cerr << err_msg << std::endl;
    std::cerr << "Parser error: Compilation failed" << std::endl;
    abort();
}

Node* Parser::parse_group_ref() {
    return nullptr;
}

Node* Parser::parse_symbol() {
    return nullptr;
}

Node* Parser::parse_groupped_expr() {
    return nullptr;
}

Node* Parser::parse_named_group() {
    bool match = match_and_consume("(<");
    std::string group_name;

    if (!match)
        return nullptr;
    return nullptr;
}

Node* Parser::parse_atom() {
    
    return nullptr;
}

Node* Parser::parse_repeat() {
    Node* node = parse_atom();
    return nullptr;
}

Node* Parser::parse_concat() {
    Node* node = parse_repeat();
    while (node != nullptr) {
        node = parse_repeat();
    }
    return nullptr;
}

Node* Parser::parse_or() {
    Node* first = parse_concat();

    while (match("|")) {
        parse_concat();
    }
    return first;
    // Return
}

void Parser::parse_expr(Ast* ast) {
    Node* root = parse_or();

    if (root == nullptr) {
        if (cregex.size() == 0) 
            // Success. Regex for empty lines
            ast->root = root; 
        else 
            print_report_and_abort();
    }
    else if (root != nullptr && position == cregex.size())
        // Succes
        ast->root = root;
    else 
        print_report_and_abort();
}
