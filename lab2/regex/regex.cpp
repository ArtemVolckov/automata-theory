#include "regex.hpp"
#include "ast.hpp"

void Regex::compile(std::string_view cregex) {
    Ast ast;
    Parser parser(cregex);
    parser.parse_expr(&ast);
}
