#pragma once

#include <iostream>
#include <string_view>
#include <unordered_set>

class Regex {
    private:
        //std::unordered_set<char> char_metasymbols;
    public:
        //Regex() {
        //    char_metasymbols = { '|', '?', '{', '}' };
        //}
        void compile(std::string_view cregex);
};
