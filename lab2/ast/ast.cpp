#include "ast.hpp"

void Parser::report(std::string_view err_msg) {
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
    bool match = match_and_consume("(");
    std::string expr;

    if (!match)
        return nullptr;

    expr = parse_until_char_or_end(')');

    if (expr.empty())
        report("Expected expression inside brackets");
    if (!match_and_consume(")"))
        report("Expected ')'");
    
    int old_position = position;
    std::string old_cregex = cregex;
    position = 0;
    cregex = expr;
    
    Node* new_node = parse_expr();

    position = old_position;
    cregex = old_cregex;
    return new_node;
}

Node* Parser::parse_named_group() {
    bool match = match_and_consume("(<");
    std::string group_name, expr;

    if (!match)
        return nullptr;
    group_name = parse_until_char_or_end('>');
    
    if (group_name.empty()) 
        report("Expected group name");
    if (!match_and_consume(">"))
       report("Expected '>'");

    expr = parse_until_char_or_end(')');

    if (expr.empty())
        report("Expected expression inside group");
    if (!match_and_consume(")"))
        report("Expected ')'");

    int old_position = position;
    std::string old_cregex = cregex;
    position = 0;
    cregex = expr;

    Node* new_node = new Node(NodeType::GROUP, group_name, parse_expr());
    
    position = old_position;
    cregex = old_cregex;
    return new_node;
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

Node* Parser::parse_expr() {
    Node* root = parse_or();

    if (root == nullptr) {
        if (cregex.size() != 0) 
            report("Parse expr error");
    }
    else if (root != nullptr && position != cregex.size())
        report("Parse expr error");
    return root;
}
