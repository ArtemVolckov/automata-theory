#pragma once

#include <string_view>

#define REGCOMP_ERR -1
#define REGCOMP_SUCCESS 0

class Regex {
    private:
    public:
        int compile(std::string_view cregex);
};
