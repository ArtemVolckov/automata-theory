#include "nfa_dfa.hpp"

void nnfa_init(std::vector<Nfa*>& nnfa, Node* ast_node, int nnfa_num) {
    // Regex for empty lines
    if (ast_node == nullptr)
        return;
    // SYMBOL
    if (ast_node->type == NodeType::SYMBOL) {
        Nfa* current_nfa = nnfa.at(nnfa_num);
        current_nfa->state_count++;

        // if the last operation was '...'
        if (current_nfa->state_count == current_nfa->transitions.size()) {
            Adjacency_list* transition = current_nfa->transitions.back();
            transition->next = new Adjacency_list(std::get<char>(ast_node->data), current_nfa->state_count);
            return;
        }
        Adjacency_list* transition = new Adjacency_list(std::get<char>(ast_node->data), current_nfa->state_count);
        current_nfa->transitions.push_back(transition); 
    }
    // CONCAT
    else if (ast_node->type == NodeType::CONCAT) {
        Nfa* current_nfa = nnfa.at(nnfa_num);
        int tmp_state_count;

        for (Node* children: ast_node->childrens) {
            if (children->type == NodeType::REPEAT) {
                tmp_state_count = current_nfa->state_count;
            }
            nnfa_init(nnfa, children, nnfa_num);

            if (children->type == NodeType::REPEAT) 
                current_nfa->final_states.erase(tmp_state_count);
            current_nfa->final_states.erase(current_nfa->state_count);
        }
        current_nfa->final_states.insert(current_nfa->state_count);
    }
    // OR
    else if (ast_node->type == NodeType::OR) {
        Nfa* current_nfa = nnfa.at(nnfa_num);
        std::vector<int> start_state_counts;
        std::vector<int> end_state_counts;
        std::vector<bool> is_start_transitions_end_states;
        bool is_start_transition = false;
        Adjacency_list* start_transition;
        current_nfa->final_states.erase(current_nfa->state_count);

        // if the last operation was not '...' 
        if (current_nfa->state_count != current_nfa->transitions.size())
            is_start_transition = true; 
        
        if (!is_start_transition) { 
            start_transition = new Adjacency_list();
            current_nfa->transitions.push_back(start_transition);
        }
        else 
            start_transition = current_nfa->transitions.back(); 
        
        for (Node* children: ast_node->childrens) {
            current_nfa->state_count++;
            start_state_counts.push_back(current_nfa->state_count); 
            nnfa_init(nnfa, children, nnfa_num);
            
            end_state_counts.push_back(current_nfa->state_count);
            current_nfa->final_states.erase(current_nfa->state_count);

            if (current_nfa->state_count == current_nfa->transitions.size()) { 
                Adjacency_list* end_transition = new Adjacency_list();
                current_nfa->transitions.push_back(end_transition);
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
        current_nfa->state_count++;
        int counter = 0;

        for (int count: end_state_counts) {
            if (!is_start_transitions_end_states.at(counter))
                current_nfa->transitions.at(count)->transition = std::make_pair('\0', current_nfa->state_count);
            else
                current_nfa->transitions.at(count)->next = new Adjacency_list('\0', current_nfa->state_count);
            counter++;
        }         
    }
    // REPEAT
    else if (ast_node->type == NodeType::REPEAT) {
        Nfa* current_nfa = nnfa.at(nnfa_num);
        std::vector<int> range = std::get<std::vector<int>>(ast_node->data);

        // '{}' 
        if (range.at(0) == range.at(1)) {
            Nfa* current_nfa = nnfa.at(nnfa_num);

            for (int i = 0; i < range.at(0); ++i) {
                current_nfa->final_states.erase(current_nfa->state_count);
                nnfa_init(nnfa, ast_node->childrens.at(0), nnfa_num);
            }
            current_nfa->final_states.insert(current_nfa->state_count);
        }
        // '?'
        else if (range.at(1) == 1) {
            int tmp_state_count = current_nfa->state_count;
            nnfa_init(nnfa, ast_node->childrens.at(0), nnfa_num);
            Adjacency_list* start_transition = current_nfa->transitions.at(tmp_state_count);
            Adjacency_list* tmp_start_transition;
            current_nfa->final_states.insert(tmp_state_count);

            do {
                tmp_start_transition = start_transition;

                if (std::holds_alternative<std::pair<char, int>>(start_transition->transition)) {
                    std::pair<char, int> transition = std::get<std::pair<char, int>>(start_transition->transition) ;
                
                    if (transition.first == '\0' && transition.second == current_nfa->state_count) {
                        return;
                    }
                }
                start_transition = start_transition->next;    
            } while (start_transition != nullptr);

            tmp_start_transition->next = new Adjacency_list('\0', current_nfa->state_count);
        }
        // '...'
        else {
            int tmp_state_count = current_nfa->state_count;
            nnfa_init(nnfa, ast_node->childrens.at(0), nnfa_num);
            Adjacency_list* start_transition = current_nfa->transitions.at(tmp_state_count);
            Adjacency_list* tmp_start_transition;
            bool is_start_transition = false;
            current_nfa->final_states.insert(tmp_state_count);

            do {
                tmp_start_transition = start_transition;

                if (std::holds_alternative<std::pair<char, int>>(start_transition->transition)) {
                    std::pair<char, int> transition = std::get<std::pair<char, int>>(start_transition->transition) ;
                
                    if (transition.first == '\0' && transition.second == current_nfa->state_count) {
                        is_start_transition = true;
                        break;
                    }
                }
                start_transition = start_transition->next;    
            } while (start_transition != nullptr);

            if (!is_start_transition) 
                tmp_start_transition->next = new Adjacency_list('\0', current_nfa->state_count);

            if (current_nfa->state_count != current_nfa->transitions.size()) 
                return;

            else {
                Adjacency_list* end_transition = new Adjacency_list('\0', tmp_state_count);
                current_nfa->transitions.push_back(end_transition);
            }
        }
    }
    // GROUP
    else if (ast_node->type == NodeType::GROUP) {
        Nfa* current_nfa = nnfa.at(nnfa_num);
        current_nfa->state_count++;
        current_nfa->final_states.insert(current_nfa->state_count);

        // if the last operation was not '...'
        if (current_nfa->state_count != current_nfa->transitions.size()) {
            Adjacency_list* transition = new Adjacency_list(std::get<std::string>(ast_node->data), current_nfa->state_count);
            current_nfa->transitions.push_back(transition); 
        }
        else 
            current_nfa->transitions.back()->next = new Adjacency_list(std::get<std::string>(ast_node->data), current_nfa->state_count);

        for (Nfa* tmp_nfa: nnfa) {
            if (std::get<std::string>(ast_node->data) == tmp_nfa->name)
                return;
        }
        Nfa* group_nfa = new Nfa(std::get<std::string>(ast_node->data));
        nnfa.push_back(group_nfa);
        nnfa_init(nnfa, ast_node->childrens.at(0), (nnfa.size() - 1));
    }
}

void nnfa_prepare(std::vector<Nfa*>& nnfa) {
    for (Nfa* nfa: nnfa)
        nfa->final_states.insert(nfa->state_count);
}

void print_nnfa(const std::vector<Nfa*>& nnfa) {
    int counter;

    for (Nfa* nfa: nnfa) {
        counter = 0;
        std::cout << std::endl;

        if (nfa->name == "") 
            std::cout << "Main automata" << std::endl;
        else 
            std::cout << "\"" << nfa->name << "\"" << " automata" << std::endl;    

        for (Adjacency_list* transition: nfa->transitions) {
            while (transition != nullptr) {
                if (std::holds_alternative<std::pair<char, int>>(transition->transition)) {
                    std::cout << counter << " -> " << std::get<std::pair<char, int>>(transition->transition).second;
                    
                    if (std::get<std::pair<char, int>>(transition->transition).first != '\0')
                        std::cout << " '" << std::get<std::pair<char, int>>(transition->transition).first << "'" << std::endl;
                    else 
                        std::cout << " epsilon" << std::endl;
                }
                else {
                    std::cout << counter << " -> " << std::get<std::pair<std::string, int>>(transition->transition).second;
                    std::cout << " \"" << std::get<std::pair<std::string, int>>(transition->transition).first << "\"" << std::endl;    
                }
                transition = transition->next;
            }
            counter++;
        }
        std::cout << "Final states:";

        for (int final_state: nfa->final_states)
            std::cout << " " << final_state; 
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::set<int> epsilon_closure(const Nfa& nfa, int state) {
    std::set<int> closure = {state};
    std::queue<int> queue;
    queue.push(state);

    while (!queue.empty()) {
        int current = queue.front();
        queue.pop();

        if (current >= nfa.transitions.size()) 
            break;
        Adjacency_list* transition = nfa.transitions.at(current);

        while (transition != nullptr) {
            if (std::holds_alternative<std::pair<char, int>>(transition->transition)) {
                std::pair pair = std::get<std::pair<char, int>>(transition->transition);
                
                if (pair.first == '\0' && (closure.find(pair.second) == closure.end())) {
                    closure.insert(pair.second);
                    queue.push(pair.second);
                }
            }
            transition = transition->next;
        }
    }
    return closure;
}

std::vector<Dfa*> nfa_to_dfa(std::vector<Nfa*>& nnfa) {
    using KeyType = std::variant<char, std::string>;

    std::vector<Dfa*> ndfa;
    std::set<int> initial_state; 

    for (Nfa* nfa: nnfa) {
        std::queue<std::set<int>> unmarked_states;
        std::map<std::set<int>, int> dfa_states;
        initial_state = epsilon_closure(*nfa, 0);
        unmarked_states.push(initial_state);
        Dfa* dfa;
        
        if (nfa->name == "")
            dfa = new Dfa;
        else
            dfa = new Dfa(nfa->name);
        ndfa.push_back(dfa);
        dfa_states[initial_state] = 0;
        dfa->state_count = 1;

        for (int state : initial_state) {
            if (nfa->final_states.find(state) != nfa->final_states.end())
                dfa->final_states.insert(0);
        }
        while (!unmarked_states.empty()) {
            std::set<int> current_state = unmarked_states.front();
            unmarked_states.pop();

            std::map<KeyType, std::set<int>> moves;

            for (int state : current_state) {
                if (state >= nfa->transitions.size()) 
                    continue;
                Adjacency_list* transition = nfa->transitions.at(state);

                while (transition != nullptr) {
                    if (std::holds_alternative<std::pair<char, int>>(transition->transition)) {
                        std::pair pair = std::get<std::pair<char, int>>(transition->transition);
                    
                        if (pair.first != '\0') {
                            std::set<int> next_state = epsilon_closure(*nfa, pair.second);
                            moves[pair.first].insert(next_state.begin(), next_state.end());
                        }
                    }
                    else {
                        std::pair pair = std::get<std::pair<std::string, int>>(transition->transition);
                        std::set<int> next_state = epsilon_closure(*nfa, pair.second);
                        moves[pair.first].insert(next_state.begin(), next_state.end());
                    }
                    transition = transition->next;
                }
            }
            for (const auto& move : moves) {
                if (dfa_states.find(move.second) == dfa_states.end()) {
                    dfa_states[move.second] = dfa->state_count;
                    dfa->state_count++;
                    unmarked_states.push(move.second);
                }
                int from_state = dfa_states[current_state];
                int to_state = dfa_states[move.second];

                if (from_state >= dfa->transitions.size()) {
                    dfa->transitions.resize(from_state + 1, nullptr);
                }
                Adjacency_list* new_transition;

                if (std::holds_alternative<char>(move.first))
                    new_transition = new Adjacency_list(std::get<char>(move.first), to_state);
                else
                    new_transition = new Adjacency_list(std::get<std::string>(move.first), to_state);

                new_transition->next = dfa->transitions[from_state];
                dfa->transitions[from_state] = new_transition;

                for (int state: move.second) {
                    if (nfa->final_states.find(state) != nfa->final_states.end())
                        dfa->final_states.insert(to_state);
                }
            }
        }
    }
    return ndfa;
}

void print_ndfa(const std::vector<Dfa*>& ndfa) {
    int counter;

    for (Dfa* dfa: ndfa) {
        counter = 0;
        std::cout << std::endl;

        if (dfa->name == "") 
            std::cout << "Main automata" << std::endl;
        else 
            std::cout << "\"" << dfa->name << "\"" << " automata" << std::endl;    

        for (Adjacency_list* transition: dfa->transitions) {
            while (transition != nullptr) {
                if (std::holds_alternative<std::pair<char, int>>(transition->transition)) {
                    std::cout << counter << " -> " << std::get<std::pair<char, int>>(transition->transition).second;
                    std::cout << " '" << std::get<std::pair<char, int>>(transition->transition).first << "'" << std::endl;
                }
                else {
                    std::cout << counter << " -> " << std::get<std::pair<std::string, int>>(transition->transition).second;
                    std::cout << " \"" << std::get<std::pair<std::string, int>>(transition->transition).first << "\"" << std::endl;    
                }
                transition = transition->next;
            }
            counter++;
        }
        std::cout << "Final states:";

        for (int final_state: dfa->final_states)
            std::cout << " " << final_state; 
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

int get_transition(const Dfa& dfa, int state, std::variant<std::string, char> symbol) {
    if (state >= dfa.transitions.size())
        return -1;
    Adjacency_list* current_transition = dfa.transitions.at(state);

    while (current_transition != nullptr) {
        if (std::holds_alternative<std::pair<char, int>>(current_transition->transition)) {
            std::pair pair = std::get<std::pair<char, int>>(current_transition->transition);
           
            if (std::holds_alternative<char>(symbol)) { 
                if (pair.first == std::get<char>(symbol))
                    return pair.second;
            }
        }
        else { 
            std::pair pair = std::get<std::pair<std::string, int>>(current_transition->transition);
           
            if (std::holds_alternative<std::string>(symbol)) {
                if (pair.first == std::get<std::string>(symbol))
                    return pair.second;
            }
        }
        current_transition = current_transition->next;
    }
    return -1;             
}


std::vector<Dfa*> minimize_dfa(std::vector<Dfa*>& ndfa) {
    std::vector<Dfa*> min_ndfa;

    for (const Dfa* dfa: ndfa) {
        std::unordered_set<std::variant<std::string, char>> alphabet;
        std::vector<std::set<int>> partition;

        for (Adjacency_list* current_transition: dfa->transitions) {
            while (current_transition) {
                if (std::holds_alternative<std::pair<char, int>>(current_transition->transition)) 
                    alphabet.insert(std::get<std::pair<char, int>>(current_transition->transition).first);
                else
                    alphabet.insert(std::get<std::pair<std::string, int>>(current_transition->transition).first);
                current_transition = current_transition->next;
            }
        }
        std::set<int> accepting, non_accepting;

        for (int i = 0; i < dfa->state_count; ++i) {
            if (dfa->final_states.count(i))
                accepting.insert(i);
            else 
                non_accepting.insert(i);
        }
        if (!non_accepting.empty()) partition.push_back(non_accepting);
        if (!accepting.empty()) partition.push_back(accepting);
        bool is_splited = false;
        
        for (;;) { 
            for (int i = 0; i < partition.size(); ++i) {
                std::set<int> group_states = partition.at(i);

                for (std::variant<std::string, char> symbol: alphabet) { 
                    for (int current_state: group_states) {
                        int next_state = get_transition(*dfa, current_state, symbol);

                        if (next_state != -1) {
                            int next_set;

                            for (next_set = 0; next_set < partition.size(); ++next_set) {
                                if (partition.at(next_set).count(next_state) > 0) 
                                    break;
                            }
                            std::set<int> group_states_tmp;
                            group_states_tmp.insert(current_state);

                            for (int state_tmp: group_states) {
                                int next_state_tmp = get_transition(*dfa, state_tmp, symbol);

                                if (next_state_tmp != -1) {
                                    int next_set_tmp;

                                    for (next_set_tmp = 0; next_set_tmp < partition.size(); ++next_set_tmp) {
                                        if (partition.at(next_set_tmp).count(next_state_tmp) > 0) 
                                            break;
                                    }
                                    if (next_set_tmp == next_set)
                                        group_states_tmp.insert(state_tmp);
                                }
                            }
                            if (group_states_tmp.size() != group_states.size()) {
                                // removing duplicates
                                for (int state: group_states_tmp)
                                    partition.at(i).erase(state);
                                partition.push_back(group_states_tmp);
                                is_splited = true;
                                break;
                            }
                            else {
                                break;    
                            }
                        } 
                    }
                    if (is_splited)
                        break;
                }
                if (is_splited)
                    break;
            }
            if (!is_splited)
                break;
            is_splited = false;
        }
        // Creating a new minimized DFA
        Dfa* min_dfa;
        
        if (dfa->name == "")
            min_dfa = new Dfa;
        else
            min_dfa = new Dfa(dfa->name);
        min_ndfa.push_back(min_dfa);

        // Looking for the initial state
        bool is_find = false;
        int set_num;

        for (set_num = 0; set_num < partition.size(); ++set_num) {
            for (int state: partition.at(set_num)) {
                if (state == 0) {
                    is_find = true;
                    break;
                }
            }
            if (is_find)
                break;
        }
        is_find = false;
        // first group -> start group
        std::set<int> set_tmp = partition.at(set_num);
        partition.erase(partition.begin() + set_num);
        partition.insert(partition.begin(), set_tmp);

        for (int i = 0; i < partition.size(); ++i) {
            for (int state: partition.at(i)) {
                if (dfa->final_states.count(state)) {
                    min_dfa->final_states.insert(i);
                    break;
                }
            }
        }
        //min_dfa->transitions.resize(partition.size(), nullptr); 
        int new_transitions_counter = 0;

        for (int i = 0; i < partition.size(); ++i) {
            int state = *partition.at(i).begin();

            if (state >= dfa->transitions.size()) {
                if (i != (partition.size() - 1))
                    min_dfa->transitions.push_back(nullptr);
                continue;
            }
            Adjacency_list* tmp_transition = dfa->transitions.at(state);

            if (tmp_transition == nullptr) {
                min_dfa->transitions.push_back(nullptr);
                continue;
            }
            int set_num_tmp;

            for (set_num_tmp = 0; set_num_tmp < partition.size(); ++set_num_tmp) {
                for (int state_tmp : partition.at(set_num_tmp)) {
                    if (std::holds_alternative<std::pair<char, int>>(tmp_transition->transition)) {
                        std::pair<char, int> pair = std::get<std::pair<char, int>>(tmp_transition->transition);
                        
                        if (state_tmp == pair.second) {
                            is_find = true;
                            break;
                        }
                    }
                    else {
                        std::pair<std::string, int> pair = std::get<std::pair<std::string, int>>(tmp_transition->transition);
                        
                        if (state_tmp == pair.second) {
                            is_find = true;
                            break;
                        }
                    }
                }
                if (is_find)
                    break;
            }
            is_find = false;
            Adjacency_list* new_transition;

            if (std::holds_alternative<std::pair<char, int>>(tmp_transition->transition)) {
                std::pair<char, int> pair = std::get<std::pair<char, int>>(tmp_transition->transition);
                new_transition = new Adjacency_list(pair.first, set_num_tmp);
            }
            else {
                std::pair<std::string, int> pair = std::get<std::pair<std::string, int>>(tmp_transition->transition);
                new_transition = new Adjacency_list(pair.first, set_num_tmp);
            }
            min_dfa->transitions.push_back(new_transition);

            while (tmp_transition->next != nullptr) {
                tmp_transition = tmp_transition->next;

                for (set_num_tmp = 0; set_num_tmp < partition.size(); ++set_num_tmp) {
                    for (int state_tmp : partition.at(set_num_tmp)) {
                        if (std::holds_alternative<std::pair<char, int>>(tmp_transition->transition)) {
                            std::pair<char, int> pair = std::get<std::pair<char, int>>(tmp_transition->transition);
                            
                            if (state_tmp == pair.second) {
                                is_find = true;
                                break;
                            }
                        }
                        else {
                            std::pair<std::string, int> pair = std::get<std::pair<std::string, int>>(tmp_transition->transition);
                            
                            if (state_tmp == pair.second) {
                                is_find = true;
                                break;
                            }
                        }
                    }
                    if (is_find)
                        break;
                }
                is_find = false;

                if (std::holds_alternative<std::pair<char, int>>(tmp_transition->transition)) {
                    std::pair<char, int> pair = std::get<std::pair<char, int>>(tmp_transition->transition);
                    new_transition->next = new Adjacency_list(pair.first, set_num_tmp);
                }
                else {
                    std::pair<std::string, int> pair = std::get<std::pair<std::string, int>>(tmp_transition->transition);
                    new_transition->next = new Adjacency_list(pair.first, set_num_tmp);
                }
                new_transition = new_transition->next; 
            }
            new_transitions_counter++;
        }
        // including the start state
        min_dfa->state_count = partition.size();
    }
    return min_ndfa;
}
