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

    group_names.clear();
    std::vector<Nfa*> nnfa;
    Nfa nfa;
    nnfa.push_back(&nfa);
    nnfa_init(nnfa, ast.root, 0, group_names);

#if 0
    if (group_names.size() != (nnfa.size() - 1)) {
        std::cerr << "Redefining the group due to the use of repetitions: '{}', '...'" << std::endl;
        std::cerr << "Compilation failed" << std::endl;

        for (int i = 1; i < nnfa.size(); ++i)
            delete nnfa.at(i);

        return REGCOMP_ERR;
    }
#endif 

    print_nnfa(nnfa, group_names);

    for (int i = 1; i < nnfa.size(); ++i)
        delete nnfa.at(i);

    return REGCOMP_SUCCESS; 
}
