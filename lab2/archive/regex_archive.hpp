#pragma once

#include <iostream>
#include <string_view>
#include <unordered_set>
#include "ast.hpp"

class Regex {
    private:
        std::unordered_set<char> char_metasymbols;

        void parse_expr(std::string_view cregex);

        void parser_error(std::string_view err_msg);

    public:
        Regex() {
            char_metasymbols = { '|', '?', '{', '}' };
        }
        void compile(std::string_view cregex);
};
