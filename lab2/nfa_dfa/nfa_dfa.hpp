#pragma once

#include "ast.hpp"

typedef struct Adjacency_list {
    std::variant<std::pair<char, int>, std::pair<std::string, int>> transition;
    Adjacency_list* next = nullptr;

    Adjacency_list() {}
    
    // EPSILON | SYMBOL 
    Adjacency_list(char symbol, int state_num) {
        transition = std::make_pair(symbol, state_num);
    }
    // GROUP
    Adjacency_list(std::string group_name, int state_num) {
        transition = std::make_pair(group_name, state_num);
    }
} Adjacency_list;

typedef struct Nfa {
    int state_count = 0;
    std::vector<Adjacency_list*> transitions;

    Nfa() {}

    ~Nfa() {
        Adjacency_list* transition_tmp;

        for (Adjacency_list* transition: transitions) {
            while (transition != nullptr) {
                transition_tmp = transition->next;
                delete transition;
                transition = transition_tmp;
            }
        }
    }        
} Nfa;

void print_nnfa(std::vector<Nfa*>& nnfa, std::vector<std::string>& group_names);
void nnfa_init(std::vector<Nfa*>& nnfa, Node* ast_node, int nnfa_num, std::vector<std::string>& group_names);

typedef struct Dfa {
    int state_count = 0;
    std::vector<Adjacency_list*> transitions;
} Dfa;

Dfa nfa_to_dfa(Nfa& nfa);
