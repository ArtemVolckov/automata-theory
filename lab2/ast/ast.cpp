#include "ast.hpp"

bool Parser::check_and_print_error() {
    if (is_error) {
        std::cerr << err_msg << std::endl;
        std::cerr << "Parser error: Compilation failed" << std::endl;
        return true;
    }
    else if (position != cregex.length()) {
        std::cerr << "Expression parsing error" << std::endl;
        std::cerr << "Parser error: Compilation failed" << std::endl;
        return true;
    }
    return false;
}

void Parser::report(std::string_view err_msg) {
    if (!is_error) {
        is_error = true;
        this->err_msg = err_msg;
    }
}

Node* Parser::parse_symbol() {
    int old_position = position;
    char symbol;

    if (match_and_consume("%")) {
        if (!get_symbol(&symbol))
            position = old_position;
        else {
            if (match_and_consume("%"))
                return new Node(NodeType::SYMBOL, symbol);
            else
                position = old_position;
        }
    }
    if (match("<"))
        return nullptr;
    if (match("|"))
        return nullptr;

    if (match("(")) {
        report("Empty '()'");
        return nullptr; 
    }
    if (match("?")) {
        report("Expected an expression before '?'");
        return nullptr;
    }
    if (match("...")) {
        report("Expected an expression before '...'");
        return nullptr;
    }
    if (match(")")) {
        return nullptr;
    }
    if (match("{")) {
        report("Expected an expression before '{'");
        return nullptr;
    }
    if (match("}")) {
        report("'}' without '{'");
        return nullptr;
    }
    if (match(">")) {
        report("'>' without '<'");
        return nullptr;
    }

    if (!get_symbol(&symbol))
        return nullptr;
    return new Node(NodeType::SYMBOL, symbol);
}

Node* Parser::parse_groupped_expr() {
    if (!match_and_consume("("))
        return nullptr;

    Node* new_node = parse_expr();

    if (!match_and_consume(")")) {
        report("Expected )");
        return new_node;
    }
    return new_node;
}

Node* Parser::parse_named_group() {
    std::string group_name;

    if (!match_and_consume("(<"))
        return nullptr;
    group_name = parse_until_char_or_end('>');
    
    if (group_name.empty()) { 
        report("Expected a group name inside '<>'");
        return nullptr;
    }
    if (!match_and_consume(">")) {
       report("Expected '>'");
       return nullptr;
    }
    Node* new_node = parse_expr();

    if (!match_and_consume(")")) {
        report("Expected ')'");
        return nullptr;
    }
    return new Node(NodeType::GROUP, group_name, new_node);
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
    return nullptr;
}

Node* Parser::parse_repeat() {
    Node* new_node = parse_atom();
    Node* node_to_return;

    if (new_node == nullptr)
        return nullptr;
    for (;;) {
        if (match_and_consume("?")) {
            std::vector<int> range = {0, 1};
            node_to_return = new Node(NodeType::REPEAT, range, new_node);
            new_node = node_to_return;
            continue;
        }
        if (match_and_consume("...")) {
            std::vector<int> range = {0, INT_MAX};
            node_to_return = new Node(NodeType::REPEAT, range, new_node);
            new_node = node_to_return;
            continue;
        }
        if (match_and_consume("{")) {
            int num;
            std::string num_str = parse_until_char_or_end('}');

            if (num_str.empty()) {
                report("Expected a number inside '{}'");
                return new_node;
            }
            if (!match_and_consume("}")) {
                report("Expected '}'");
                return new_node;
            }
            try {
                num = std::stoi(num_str);

                for (char symbol: num_str) {
                    if (symbol < 48 || symbol > 57) {
                        report("A number inside '{}' was expected");
                        return new_node;
                    }
                }
            }
            catch (const std::invalid_argument& e) {
                report("A number inside '{}' was expected");
                return new_node;
            }
            catch (const std::out_of_range& e) {
                report("The number inside '{}' is out of range");
                return new_node;
            }
            if (num == INT_MAX) {
                report("The number of repetitions cannot be infinite");
                return new_node;
            }
            std::vector<int> range = {num, num};
            node_to_return = new Node(NodeType::REPEAT, range, new_node);
            new_node = node_to_return;
            continue;
        }
        return new_node;
    }
}

Node* Parser::parse_concat() {
    Node* first_node = parse_repeat();

    if (first_node == nullptr)
        return nullptr;
    std::vector<Node*> childrens;
    childrens.push_back(first_node);

    Node* new_node = parse_repeat();

    if (new_node == nullptr)
        return first_node; 

    while (new_node != nullptr) {
        childrens.push_back(new_node);
        new_node = parse_repeat();
    }
    return new Node(childrens, NodeType::CONCAT);
}

Node* Parser::parse_or() {
    Node* first_node = parse_concat();
    Node* new_node;

    if (first_node == nullptr) 
        return nullptr;
    std::vector<Node*> childrens;
    childrens.push_back(first_node);

    int old_position = position;

    if (!match_and_consume("|"))
        return first_node;
    position = old_position;

    while (match_and_consume("|")) {
        if (position == cregex.length()) {
            report("Expected an expression to the right of '|'");
            return new Node(NodeType::OR, childrens);
        }
        new_node = parse_concat();
        
        if (new_node != nullptr)
            childrens.push_back(new_node);
    }
    return new Node(NodeType::OR, childrens);
}

Node* Parser::parse_expr() {
    Node* root = parse_or();
    return root;
}

void Ast::collect_groups(std::vector<std::pair<std::string, Node*>>& groups, Node* node) {
    if (node == nullptr)
        return;
    if (node->type == NodeType::GROUP) {
        std::string group_name = std::get<std::string>(node->data);
        
        if (!node->childrens.empty())
            groups.push_back(std::make_pair(group_name, node->childrens.front()));
        else 
            groups.push_back(std::make_pair(group_name, nullptr));
    }
    for (Node* children: node->childrens)
       collect_groups(groups, children); 
}

bool Ast::prepare() {
    if (root == nullptr) {
        return true;
    }
    std::vector<std::pair<std::string, Node*>> groups;
    collect_groups(groups, root);
    
    // checking if all group names are unique
    std::set<std::string> unique_strings;
    
    for (const auto& pair : groups) {
        if (!unique_strings.insert(pair.first).second) {
            std::cerr << "Duplicate names were found for the groups" << std::endl; 
            std::cerr << "Compilation failed" << std::endl;
            return false;
        }
    }
    return true;
}
