#include "nfa_dfa.hpp"

void nnfa_init(std::vector<Nfa*>& nnfa, Node* ast_node) {
    if (ast_node == nullptr)
        return;

    // SYMBOL 
    if (ast_node->type == NodeType::SYMBOL) {
        Nfa* main_nfa = nnfa.at(0);
        main_nfa->state_count++;

        // if the last operation was '...'
        if (main_nfa->state_count == main_nfa->transitions.size()) {
            Adjacency_list* transition = main_nfa->transitions.back();
            transition->next = new Adjacency_list(std::get<char>(ast_node->data), main_nfa->state_count);
            return;
        }
        Adjacency_list* transition = new Adjacency_list(std::get<char>(ast_node->data), main_nfa->state_count);
        main_nfa->transitions.push_back(transition); 
    }
    // CONCAT
    else if (ast_node->type == NodeType::CONCAT) {
        for (Node* children: ast_node->childrens) {
            nnfa_init(nnfa, children);
        }
    }
    // OR
    else if (ast_node->type == NodeType::OR) {
        Nfa* main_nfa = nnfa.at(0);
        std::vector<int> start_state_counts;
        std::vector<int> end_state_counts;
        std::vector<bool> is_start_transitions_end_states;
        bool is_start_transition = false;
        Adjacency_list* start_transition;

        // if the last operation was not '...' 
        if (main_nfa->state_count != main_nfa->transitions.size())
            is_start_transition = true; 
        
        if (!is_start_transition) { 
            start_transition = new Adjacency_list();
            main_nfa->transitions.push_back(start_transition);
        }
        else 
            start_transition = main_nfa->transitions.back(); 
        
        for (Node* children: ast_node->childrens) {
            main_nfa->state_count++;
            start_state_counts.push_back(main_nfa->state_count); 
            nnfa_init(nnfa, children);
            
            end_state_counts.push_back(main_nfa->state_count);

            if (main_nfa->state_count == main_nfa->transitions.size()) { 
                Adjacency_list* end_transition = new Adjacency_list();
                main_nfa->transitions.push_back(end_transition);
                is_start_transitions_end_states.push_back(false);
            }
            else
                is_start_transitions_end_states.push_back(true);
        }
        if (!is_start_transition)
            start_transition->transition = std::make_pair('\0', start_state_counts.at(0));
        else { 
            start_transition->next = new Adjacency_list('\0', start_state_counts.at(0));
            start_transition = start_transition->next;
        } 
        for (size_t i = 1; i < start_state_counts.size(); ++i) {
            start_transition->next = new Adjacency_list('\0', start_state_counts.at(i));
            start_transition = start_transition->next;
        }
        main_nfa->state_count++;
        int counter = 0;

        for (int count: end_state_counts) {
            if (!is_start_transitions_end_states.at(counter))
                main_nfa->transitions.at(count)->transition = std::make_pair('\0', main_nfa->state_count);
            else
                main_nfa->transitions.at(count)->next = new Adjacency_list('\0', main_nfa->state_count);
            counter++;
        }         
    }
    // REPEAT
    else if (ast_node->type == NodeType::REPEAT) {
        Nfa* main_nfa = nnfa.at(0);
        std::vector<int> range = std::get<std::vector<int>>(ast_node->data);

        // '{}' 
        if (range.at(0) == range.at(1)) {
            for (int i = 0; i < range.at(0); ++i) {
                nnfa_init(nnfa, ast_node->childrens.at(0));
            }
        }
        // '?'
        else if (range.at(1) == 1) {
            int tmp_state_count = main_nfa->state_count;
            nnfa_init(nnfa, ast_node->childrens.at(0));
            Adjacency_list* start_transition = main_nfa->transitions.at(tmp_state_count);
            Adjacency_list* tmp_start_transition;

            do {
                tmp_start_transition = start_transition;

                if (std::holds_alternative<std::pair<char, int>>(start_transition->transition)) {
                    std::pair<char, int> transition = std::get<std::pair<char, int>>(start_transition->transition) ;
                
                    if (transition.first == '\0' && transition.second == main_nfa->state_count) {
                        return;
                    }
                }
                start_transition = start_transition->next;    
            } while (start_transition != nullptr);

            tmp_start_transition->next = new Adjacency_list('\0', main_nfa->state_count);
        }
        // '...'
        else {
            int tmp_state_count = main_nfa->state_count;
            nnfa_init(nnfa, ast_node->childrens.at(0));
            Adjacency_list* start_transition = main_nfa->transitions.at(tmp_state_count);
            Adjacency_list* tmp_start_transition;
            bool is_start_transition = false;

            do {
                tmp_start_transition = start_transition;

                if (std::holds_alternative<std::pair<char, int>>(start_transition->transition)) {
                    std::pair<char, int> transition = std::get<std::pair<char, int>>(start_transition->transition) ;
                
                    if (transition.first == '\0' && transition.second == main_nfa->state_count) {
                        is_start_transition = true;
                        break;
                    }
                }
                start_transition = start_transition->next;    
            } while (start_transition != nullptr);

            if (!is_start_transition) 
                tmp_start_transition->next = new Adjacency_list('\0', main_nfa->state_count);

            if (main_nfa->state_count != main_nfa->transitions.size()) 
                return;

            else {
                Adjacency_list* end_transition = new Adjacency_list('\0', tmp_state_count);
                main_nfa->transitions.push_back(end_transition);
            }
        }
    }
    // GROUP
    else if (ast_node->type == NodeType::GROUP) {
        Nfa* main_nfa = nnfa.at(0);
        main_nfa->state_count++;

        // if the last operation was not '...'
        if (main_nfa->state_count != main_nfa->transitions.size()) {
            Adjacency_list* transition = new Adjacency_list(std::get<std::string>(ast_node->data), main_nfa->state_count);
            main_nfa->transitions.push_back(transition); 
        }
        else 
            main_nfa->transitions.back()->next = new Adjacency_list(std::get<std::string>(ast_node->data), main_nfa->state_count);
        Nfa& group_nfa = new Nfa();
        nnfa.push_back(group_nfa);
        group_nnfa_init(nnfa, (nnfa.size() - 1))
    }
}


void print_nfa(Nfa* nfa) {
    int counter = 0;

    for (Adjacency_list* transition: nfa->transitions) {
        while (transition != nullptr) {
            std::cout << counter << " -> " << std::get<std::pair<char, int>>(transition->transition).second;

            if (std::get<std::pair<char, int>>(transition->transition).first != '\0')
                std::cout << " '" << std::get<std::pair<char, int>>(transition->transition).first << "'" << std::endl;
            else 
                std::cout << " epsilon" << std::endl;
            transition = transition->next;
        }
        std::cout << std::endl;
        counter++;
    }
}
