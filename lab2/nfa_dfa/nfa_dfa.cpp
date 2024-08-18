#include "nfa_dfa.hpp"

Nfa* Nfa::make_nfa(Node* node) {
    if (node == nullptr)
        return nullptr; 

    if (node->type == NodeType::SYMBOL) {
        return new Nfa(std::get<char>(node->data));
    }
    if (node->type == NodeType::GROUP) {

    }
    if (node->type == NodeType::CONCAT) {

    }
    if (node->type == NodeType::OR) {

    }
    if (node->type == NodeType::REPEAT) {

    }
    return nullptr;  
}
