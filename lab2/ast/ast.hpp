#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <variant>
#include <utility>
#include <string>
#include <string_view>
#include <climits>

enum class NodeType {
    OR,
    CONCAT,
    REPEAT,
    GROUP,
    SYMBOL
};

typedef struct Node {
    NodeType type;
    std::variant<std::vector<int>, std::string, char> data;
    std::vector<Node*> childrens;
    
    // SYMBOL
    Node(NodeType type, char symbol) {
        this->type = type;
        data = symbol;
    }

    // GROUP
    Node(NodeType type, std::string name, Node* new_node) {
        this->type = type;
        data = name;
        childrens.push_back(new_node);
    }

    // REPEAT
    Node(NodeType type, std::vector<int> range, Node* new_node) {
        this->type = type;
        data = range;
        childrens.push_back(new_node);
    }

    // CONCAT 
    Node(std::vector<Node*> childrens, NodeType type) {
        this->type = type;
        this->childrens = childrens;
    } 

    // OR
    Node(NodeType type, std::vector<Node*> childrens) {
        this->type = type;
        this->childrens = childrens;
    }

    ~Node() {
        for (Node* children: childrens)
            delete children;
    }
} Node;

typedef struct Ast {
    Node* root;

    Ast(Node* root) {
        this->root = root;
    }

    ~Ast() {
        delete root;
    }
    
    // Simplifying the tree and checking errors with groups
    bool prepare(std::vector<std::string>& group_names);
    // Tree traversal with the search for groups and replacing them with their children
    void collect_groups(std::vector<std::string>& group_names, Node* node);
} Ast;

class Parser {
    private:
        bool is_error = false;
        std::string err_msg;
        std::string cregex;
        int position = 0;

        bool get_symbol(char* symbol) {
            if (position == cregex.length())
                return false;
            *symbol = cregex.at(position);
            position++;
            return true;
        }

        bool match(std::string_view substr) {
            return (cregex.substr(position, substr.length()) == substr);
        }
        bool match_and_consume(std::string_view substr) {
            if (match(substr)) {
                position += substr.length();
                return true;
            }
            return false;
        }
        std::string parse_until_char_or_end(char symbol) {
            int pos = cregex.find(symbol, position);
            int old_position = position;

            if (pos != std::string::npos) {
                position = pos;
                return cregex.substr(old_position, position - old_position);
            }
            position = cregex.length();
            return cregex.substr(old_position); 
        }
        Node* parse_or();
        Node* parse_concat();
        Node* parse_repeat();
        Node* parse_atom();
        Node* parse_named_group();
        Node* parse_groupped_expr();
        Node* parse_symbol();

        void report(std::string_view err_msg);

    public:
        Parser(std::string_view cregex) : cregex(cregex) {}
        Node* parse_expr();
        bool check_and_print_error();
};
