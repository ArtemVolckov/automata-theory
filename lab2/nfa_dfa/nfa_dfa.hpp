#pragma once

#include <algorithm>
#include <queue>
#include <map>

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
    std::string name;
    int state_count = 0;
    std::vector<Adjacency_list*> transitions;

    // for the main nfa
    Nfa() {}

    // for the group nfa
    Nfa(std::string name) {
        this->name = name; 
    }

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

void print_nnfa(const std::vector<Nfa*>& nnfa);
void nnfa_init(std::vector<Nfa*>& nnfa, Node* ast_node, int nnfa_num);

typedef struct Dfa {
    std::string name;
    int state_count = 0;
    std::vector<Adjacency_list*> transitions;

    // for the main dfa 
    Dfa() {}

    // for the group dfa
    Dfa(std::string name) {
        this->name = name;
    }

    ~Dfa() {
        Adjacency_list* transition_tmp;

        for (Adjacency_list* transition: transitions) {
            while (transition != nullptr) {
                transition_tmp = transition->next;
                delete transition;
                transition = transition_tmp;
            }
        }
    }
} Dfa;

void print_ndfa(const std::vector<Dfa*>& ndfa);
std::set<int> epsilon_closure(const Nfa& nfa, int state);
std::vector<Dfa*> nfa_to_dfa(std::vector<Nfa*>& nnfa);
