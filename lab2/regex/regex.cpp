#include "regex.hpp"
#include "ast.hpp"

int Regex::compile(std::string_view cregex) {
    Ast ast;
    Parser parser(cregex);
    ast.root = parser.parse_expr();

    if (parser.check_and_print_error()) {
        return REGCOMP_ERR;
    }
    return REGCOMP_SUCCESS;
}
