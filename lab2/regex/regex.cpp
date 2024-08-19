#include "regex.hpp"
#include "ast.hpp"
#include "nfa_dfa.hpp"

int Regex::compile(std::string_view cregex) {
    Parser parser(cregex);
    Ast ast(parser.parse_expr());

    if (parser.check_and_print_error()) 
        return REGCOMP_ERR;
    int groups_count = 0;

    if (!ast.prepare(groups_count))
        return REGCOMP_ERR;

    std::vector<Nfa*> nnfa;
    Nfa nfa;
    nnfa.push_back(&nfa);
    nnfa_init(nnfa, ast.root);

    if (groups_count != (nnfa.size() - 1)) {
        std::cerr << "Redefining the group due to the use of repetitions: '{}', '...'" << std::endl;
        std::cerr << "Compilation failed" << std::endl;
        return REGCOMP_ERR;
    }
    print_nfa(nnfa.at(0));
    return REGCOMP_SUCCESS; 
}
