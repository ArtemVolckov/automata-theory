#pragma once

#include "ast.hpp"

typedef struct Adjacency_list {
    std::variant<std::pair<char, int>, std::pair<std::string, int>> transition;
    Adjacency_list* next = nullptr;
    
    // SYMBOL 
    Adjacency_list(char symbol, int state_num) {
        transition = std::make_pair(symbol, state_num);
    }
} Adjacency_list;

class Nfa {
    private:
        int state_count = 0;
        std::vector<Adjacency_list*> transitions;

        Nfa() {}

        void make_nfa(Nfa& nfa, Node* node);

    public:
        Nfa(Ast& ast) {
            Nfa nfa;
            make_nfa(nfa, ast.root);

            if (nfa == nullptr) 
                this->state_count = 0;
            else {
                this->state_count = nfa->state_count;
                this->transitions = nfa->transitions;
                nfa->transitions.clear();
                delete nfa;
            }
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
};

class Dfa {
    int state_count = 0;
    std::vector<Adjacency_list*> transitions;
};
