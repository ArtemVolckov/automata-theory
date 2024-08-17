#include "ast.hpp"

void Parser::report(std::string_view err_msg) {
    std::cerr << err_msg << std::endl;
    std::cerr << "Parser error: Compilation failed" << std::endl; 
    exit(1);  
}

Node* Parser::parse_group_ref() {
    bool match = match_and_consume("<");
    std::string group_name;

    if (!match) 
        return nullptr;
    group_name = parse_until_char_or_end('>');

    if (group_name.empty()) 
        report("Expected group name");
    if (!match_and_consume(">"))
       report("Expected '>'");

    return new Node(NodeType::GROUP_REFERENCE, group_name);
}

Node* Parser::parse_symbol() {
    int old_position = position;
    bool match_check = match_and_consume("%");
    char symbol;

    if (match_check) {
        if (!get_symbol(&symbol))
            position = old_position;
        else {
            if (match_and_consume("%"))
                return new Node(NodeType::SYMBOL, symbol);
            else
                position = old_position;
        }
    }
    if (match("|"))
        return nullptr;
    if (match("?"))
        report("Expected an expression before '?'");
    if (match("..."))
        report("Expected an expression before '...'");
    if (match(")"))
        report("')' without '('");
    if (match("{"))
        report("Expected an expression before '{'");
    if (match("}"))
        report("'}' without '{'");
    if (match("<"))
        return nullptr;
    if (match(">"))
        report("'>' without '<'");
    if (!get_symbol(&symbol))
        return nullptr;
    return new Node(NodeType::SYMBOL, symbol);
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
    Node* new_node = parse_named_group();

    if (new_node != nullptr)
        return new_node;
    new_node = parse_groupped_expr();

    if (new_node != nullptr)
        return new_node;
    new_node = parse_symbol();

    if (new_node != nullptr)
        return new_node;
    new_node = parse_group_ref();
    
    if (new_node != nullptr)
        return new_node;
    return nullptr;
}

Node* Parser::parse_repeat() {
    Node* new_node = parse_atom();

    if (new_node == nullptr)
        return nullptr;
    if (match_and_consume("?")) {
        std::vector<int> range = {0, 1};
        return new Node(NodeType::REPEAT, range, new_node);
    }
    if (match_and_consume("...")) {
        std::vector<int> range = {0, INT_MAX};
        return new Node(NodeType::REPEAT, range, new_node);
    }
    if (match_and_consume("{")) {
        int num;
        std::string num_str = parse_until_char_or_end('}');

        if (num_str.empty())
            report("Expected number");
        if (!match_and_consume("}"))
            report("Expected '}'");
        try {
            num = std::stoi(num_str);
        }
        catch (const std::invalid_argument& e) {
            report("A number inside '{}' was expected");
        }
        catch (const std::out_of_range& e) {
            report("The number inside '{}' is out of range");
        } 
        std::vector<int> range = {num, num};
        return new Node(NodeType::REPEAT, range, new_node);
    }
    return new_node;
}

Node* Parser::parse_concat() {
    Node* new_node = parse_repeat();

    if (new_node == nullptr)
        return nullptr;
    std::vector<Node*> childrens;

    while (new_node != nullptr) {
        childrens.push_back(new_node);
        new_node = parse_repeat();
    }
    return new Node(childrens, NodeType::CONCAT);
}

Node* Parser::parse_or() {
    Node* first = parse_concat();

    if (first == nullptr) 
        return nullptr;
    std::vector<Node*> childrens;
    childrens.push_back(first);

    while (match_and_consume("|")) {
        if (position == cregex.length())
            report("Expected expression to the right of '|'");
        Node* next = parse_concat();
        
        if (next != nullptr)
            childrens.push_back(next);
    }
    return new Node(NodeType::OR, childrens);
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
