#pragma once

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <string_view>

enum NodeType {
    OR,
    CONCAT,
    REPEAT,
    GROUP,
    GROUP_REFERENCE,
    SYMBOL
};

typedef struct Node {
    NodeType type;
    void* data;
    std::vector<Node*> childrens;
} Node;

typedef struct Ast {
    Node* root = nullptr;
} Ast;

class Parser {
    private:
        std::string cregex;
        std::string err_msg = "";
        int position = 0;

        bool match(std::string_view str) {
            int offset = cregex.find(str, position);
            
            if (offset != std::string::npos)
                return true;
            else 
                return false;
        }
        bool match_and_consume(std::string_view str) {
            if (match(str)) {
                position += str.size();
                return true;
            }
            return false;
        }
        std::string parse_until(std::string_view str) {

        }

        Node* parse_or();
        Node* parse_concat();
        Node* parse_repeat();
        Node* parse_atom();
        Node* parse_named_group();
        Node* parse_groupped_expr();
        Node* parse_symbol();
        Node* parse_group_ref();

        void report(std::string_view err_msg);
        void print_report_and_abort();

    public:
        Parser(std::string_view cregex) : cregex(cregex) {}
        void parse_expr(Ast* ast);
};
