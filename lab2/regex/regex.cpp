#include "regex.hpp"
#include "ast.hpp"
#include "nfa_dfa.hpp"

int Regex::compile(std::string_view cregex) {
    Parser parser(cregex);
    Ast ast(parser.parse_expr());

    if (parser.check_and_print_error()) 
        return REGCOMP_ERR;

    if (!ast.prepare())
        return REGCOMP_ERR;

    std::vector<nF

    return REGCOMP_SUCCESS; 
}
