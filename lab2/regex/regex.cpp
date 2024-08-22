#include "regex.hpp"
#include "ast.hpp"
#include "nfa_dfa.hpp"

int Regex::compile(std::string_view cregex) {
    Parser parser(cregex);
    Ast ast(parser.parse_expr());

    if (parser.check_and_print_error()) 
        return REGCOMP_ERR;
    std::vector<std::string> group_names;

    if (!ast.prepare(group_names))
        return REGCOMP_ERR;

    std::vector<Nfa*> nnfa;
    Nfa nfa;
    nnfa.push_back(&nfa);
    nnfa_init(nnfa, ast.root, 0);
    nnfa_prepare(nnfa);
    std::cout << std::endl << "NFA COUNT = " << nnfa.size() << std::endl;

    print_nnfa(nnfa);

    std::vector<Dfa*> ndfa = nfa_to_dfa(nnfa);
    std::cout << "DFA COUNT = " << ndfa.size() << std::endl;

    print_ndfa(ndfa);

    std::vector<Dfa*> min_ndfa = minimize_dfa(ndfa);
    std::cout << "MIN DFA COUNT = " << min_ndfa.size() << std::endl;

    print_ndfa(min_ndfa);

    for (int i = 1; i < nnfa.size(); ++i)
        delete nnfa.at(i);
    for (int i = 0; i < ndfa.size(); ++i)
        delete ndfa.at(i);
    for (int i = 0; i < min_ndfa.size(); ++i)
        delete min_ndfa.at(i);

    return REGCOMP_SUCCESS; 
}
