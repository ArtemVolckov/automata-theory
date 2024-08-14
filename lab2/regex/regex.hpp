#pragma once

#include <string_view>
#include "ast.hpp"

class Regex {
    private:
        void regex_parse(std::string_view regex);
    public:
        void compile(std::string_view regex);
};
