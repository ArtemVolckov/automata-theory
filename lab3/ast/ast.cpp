#include "ast.hpp"

bool is_error = false;
Reporter reporter;

void Reporter::report(std::string err_msg) {
    if (is_error == false) {
        this->err_msg = err_msg;
        is_error = true;
    }
}

bool search_app_call(Node* node) {
    if (node->node_type != NodeType::IF) {
        for (Node* children: node->childrens) {
            if (children->node_type == NodeType::FUNCTION_CALL) {
                if (children->name == "application") {
                    return true;
                }
            }
            if (search_app_call(children) == true)
                return true; 
        }
    }
    else {
        for (std::vector<Node*> childrens: node->statements_list) {
            for (Node* children: childrens) {
                if (children->node_type == NodeType::FUNCTION_CALL) {
                    if (children->name == "application") {
                        return true;
                    }
                }
                if (search_app_call(children) == true)
                    return true; 
            }
        }
    }
    return false;
}

void Ast::ast_prepare() {
    if (this->functions.size() == 0) {
        reporter.report("Error: Missing application function");
        return;
    }
    std::unordered_set<std::string> names;

    for (Node* function_node: this->functions) {
        auto result = names.insert(function_node->name);

        if (!result.second) {
            reporter.report("Error: Multiple function definition");
            return;
        }
    }
    Node* app_node = nullptr;

    for (Node* function_node: this->functions) {
        if (function_node->name == "application") {
            app_node = function_node;
            break;
        }
    }
    if (app_node == nullptr) {
        reporter.report("Error: Missing application function");
        return;
    }
    for (Node* function_node: this->functions) {
        if (search_app_call(function_node) == true) {
            reporter.report("Error: Calling application function");
            return;
        }
    }
}

void Ast::ast_return(Node* return_node, int idx) {
    std::string name = this->functions.at(idx)->name;

    if (return_node->is_int_val == true) {
        if (this->functions.at(idx)->type != "integer") {
            reporter.report("Incorrect return value");
            return;
        }
        std::cout << name << " return value: ";
        std::cout << return_node->int_val << std::endl;
    }
    else if (return_node->is_bool_val) {
        if (this->functions.at(idx)->type != "boolean") {
            reporter.report("Incorrect return value");
            return;
        }
        std::cout << name << " return value: ";
        std::cout << return_node->str_val << std::endl;
    }
    else if (return_node->is_str_val) {
        if (this->functions.at(idx)->type != "string") {
            reporter.report("Incorrect return value");
            return;
        }
        std::cout << name << " return value: ";
        std::cout << return_node->str_val << std::endl;
    }
    return;
}

std::string bool_to_string(bool val) {
    return val ? "true" : "false";
}

bool Ast::is_valid_move(int x, int y) {
    if (x < 0 || x >= this->field[0].size() || y < 0 || y >= this->field.size()) {
        return false; 
    }
    return field[y][x] != WALL;
}

void Ast::func_exec(Node* node, int idx) {
    if (node->node_type == NodeType::FUNCTION_CALL) {
        bool is_call = false;

        for (int i = 0; i < this->functions.size(); ++i) {
            Node* function_node = this->functions.at(i);

            if (function_node->name == node->name) {
                is_call = true;

                if ((node->variables.size() != function_node->variables.size()) && function_node->is_elipsis == false) {
                    reporter.report("Calling a function with wrong parameter count");
                    return;
                }
                this->func_exec(function_node, i);
            }
        }
        if (is_call == false) {
            reporter.report("Calling a function that has not been declared");
            return;
        }
    }
    else if (node->node_type == NodeType::VARIABLES_INIT) {
        for (const auto& pair2 : node->variables) {
            for (const auto& pair1 : this->functions.at(idx)->variables) {
                if (pair1.first == pair2.first) {
                    reporter.report("Error: Duplicate first element found"); 
                    return;
                }
            }
            this->functions.at(idx)->variables.push_back(pair2);
        }        
    }
    else if (node->node_type == NodeType::VECTOR_INIT) {
        if (node->type == "integer") {
            for (int i = 0; i < node->variables.size(); ++i) {
                std::vector<int> a;
                this->int_vectors_list.at(idx) = std::make_pair(std::get<std::string>(node->variables.at(i).first), a);
            }
        }
        else if (node->type == "boolean") {
            for (int i = 0; i < node->variables.size(); ++i) {
                std::vector<bool> a;
                this->bool_vectors_list.at(idx) = std::make_pair(std::get<std::string>(node->variables.at(i).first), a);
            }
        }
        else if (node->type == "string") {
            for (int i = 0; i < node->variables.size(); ++i) {
                std::vector<std::string> a;
                this->string_vectors_list.at(idx) = std::make_pair(std::get<std::string>(node->variables.at(i).first), a);
            }
        }
        //this->vectors_list.at(idx).
    }
    else if (node->node_type == NodeType::ASSIGN) {
        bool is_find = false;

        for (auto& pair : this->variables_list.at(idx)) {
            if (std::get<std::string>(pair.first) == node->name) {
                if (node->is_int_val && std::holds_alternative<int>(pair.second)) {
                    pair.second = node->int_val;
                    is_find = true;
                    break;
                }
                if (node->is_bool_val && std::holds_alternative<bool>(pair.second)) {
                    if (node->str_val == "true") 
                        pair.second = true;
                    else
                        pair.second = false;
                    is_find = true;
                    break;
                }
                if (node->is_str_val && std::holds_alternative<std::string>(pair.second)) {
                    pair.second = node->str_val;
                    is_find = true;
                    break;
                }
                reporter.report("Error: an attempt to assign a value of a different type to a variable");
                return;
            }
        }
        if (!is_find) {
            reporter.report("Error: an attempt to access an undeclared variable"); 
            return;
        }
    }
    else if (node->node_type == NodeType::NAME_TO_NAME) {
        int type = - 1;

        for (auto& pair : this->variables_list.at(idx)) {
            if (std::get<std::string>(pair.first) == node->name_to) {
                if (std::holds_alternative<int>(pair.second)) 
                   type = 0;
                else if (std::holds_alternative<bool>(pair.second)) 
                    type = 1;
                else if (std::holds_alternative<std::string>(pair.second)) 
                    type = 2;
            }
        }
        if (type == -1) {
            reporter.report("Error: an attempt to access an undeclared variable");
            return;
        }
        bool is_find = false;

        for (auto& pair : this->variables_list.at(idx)) {
            if (std::get<std::string>(pair.first) == node->name_from) {
                is_find = true;
                
                if (std::holds_alternative<int>(pair.second)) {
                    if (type == 0) 
                        break;
                    if (type == 1) {
                        int val = std::get<int>(pair.second);

                        if (val != 0) 
                            pair.second = true;
                        else
                            pair.second = false;
                    }
                    if (type == 2) {
                        int val = std::get<int>(pair.second);
                        std::string str = std::to_string(val);
                        pair.second = str; 
                    }
                }
                else if (std::holds_alternative<bool>(pair.second)) {
                    if (type == 0) {
                        bool val = std::get<bool>(pair.second);
                        
                        if (val) 
                            pair.second = 1;
                        else 
                            pair.second = 0;
                    }
                    if (type == 1)
                        break;
                    if (type == 2) {
                        bool val = std::get<bool>(pair.second);
                        pair.second = bool_to_string(val);
                    }
                }
                else if (std::holds_alternative<std::string>(pair.second)) {
                    if (type == 0) {
                        std::string str = std::get<std::string>(pair.second);
                        pair.second = stoi(str);
                    }
                    if (type == 1) {
                        std::string str = std::get<std::string>(pair.second);
                        
                        if (str.length() > 0) 
                            pair.second = true;
                        else
                            pair.second = false;
                    }
                    if (type == 2) 
                        break;
                }
            }
        }
        if (!is_find) {
            reporter.report("Error: an attempt to access an undeclared variable");
            return;
        }
    }
    else if (node->node_type == NodeType::NAME_TO_TYPE) {
        bool is_find = false;

        for (auto& pair : this->variables_list.at(idx)) {
            if (std::get<std::string>(pair.first) == node->name_from) {
                is_find = true;   
                 
                if (std::holds_alternative<int>(pair.second)) {
                    if (node->type == "integer") 
                        break;
                    if (node->type == "boolean") {
                        int val = std::get<int>(pair.second);

                        if (val != 0) 
                            pair.second = true;
                        else
                            pair.second = false;
                    }
                    if (node->type == "string") {
                        int val = std::get<int>(pair.second);
                        std::string str = std::to_string(val);
                        pair.second = str; 
                    }
                }
                else if (std::holds_alternative<bool>(pair.second)) {
                    if (node->type == "integer") {
                        bool val = std::get<bool>(pair.second);
                        
                        if (val) 
                            pair.second = 1;
                        else 
                            pair.second = 0;
                    }
                    if (node->type == "boolean")
                        break;
                    if (node->type == "string") {
                        bool val = std::get<bool>(pair.second);
                        pair.second = bool_to_string(val);
                    }
                }
                else if (std::holds_alternative<std::string>(pair.second)) {
                    if (node->type == "integer") {
                        std::string str = std::get<std::string>(pair.second);
                        pair.second = stoi(str);
                    }
                    if (node->type == "boolean") {
                        std::string str = std::get<std::string>(pair.second);
                        
                        if (str.length() > 0) 
                            pair.second = true;
                        else
                            pair.second = false;
                    }
                    if (node->type == "string") 
                        break;
                }   
            }
        }
        if (!is_find) {
            reporter.report("Error: an attempt to access an undeclared variable");
            return;
        }
    }
    else if (node->node_type == NodeType::IF) {
        std::pair pair = node->logical_op_variables;
        bool is_correct = false;

        if (std::holds_alternative<int>(pair.first) && std::holds_alternative<int>(pair.second)) {
            int val1 = std::get<int>(pair.first), val2 = std::get<int>(pair.second);

            if (node->logical_op == "=") {
                if (val1 == val2)
                   is_correct = true; 
            }
            else if (node->logical_op == "<") {
                if (val1 < val2) 
                    is_correct = true;
            }
            else if (node->logical_op == ">") {
                if (val1 > val2) 
                    is_correct = true;
            }
            else if (node->logical_op == "<>") {
                if (val1 != val2)
                    is_correct = true;
            }
        }
        if (std::holds_alternative<bool>(pair.first) && std::holds_alternative<bool>(pair.second)) {
            bool val1 = std::get<bool>(pair.first), val2 = std::get<bool>(pair.second);
            
            if (node->logical_op == "=") {
                if (val1 == val2)
                    is_correct = true;
            }
            else if (node->logical_op == "<") {
                if (val1 == false && val2 == true)
                    is_correct = true;
            }
            else if (node->logical_op == ">") {
                if (val1 == true && val2 == false);
            }
            else if (node->logical_op == "<>") {
                if (val1 != val2)
                    is_correct = true;
            }
        }
        if (std::holds_alternative<std::string>(pair.first) && std::holds_alternative<std::string>(pair.second)) {
            std::string val1 = std::get<std::string>(pair.first), val2 = std::get<std::string>(pair.second);
            
            if (node->logical_op == "=") {
                if (val1 == val2)
                    is_correct = true;
            }
            else if (node->logical_op == "<") {
                if (val1 < val2)
                    is_correct = true;
            }
            else if (node->logical_op == ">") {
                if (val1 > val2)
                    is_correct = true;
            }
            else if (node->logical_op == "<>") {
                if (val1 != val2)
                    is_correct = true;
            }
        }
        else {
            reporter.report("Error: different types of data in a logical statement");
            return;
        }
        if (is_correct) {
            for (Node* child: node->statements_list.at(0))
                this->func_exec(child, idx); 
        }
        else {
            for (int i = 1; i < node->statements_list.size(); ++i) {
                for (Node* child: node->statements_list.at(i))
                    this->func_exec(child, idx);
            }
        }
    }
    else if (node->node_type == NodeType::DO) {
        for (;;) {
            for (Node* child: node->childrens)
                this->func_exec(child, idx);
            std::pair pair = node->logical_op_variables;
            bool is_correct = false;

            if (std::holds_alternative<int>(pair.first) && std::holds_alternative<int>(pair.second)) {
                int val1 = std::get<int>(pair.first), val2 = std::get<int>(pair.second);

                if (node->logical_op == "=") {
                    if (val1 == val2)
                       is_correct = true; 
                }
                else if (node->logical_op == "<") {
                    if (val1 < val2) 
                        is_correct = true;
                }
                else if (node->logical_op == ">") {
                    if (val1 > val2) 
                        is_correct = true;
                }
                else if (node->logical_op == "<>") {
                    if (val1 != val2)
                        is_correct = true;
                }
            }
            if (std::holds_alternative<bool>(pair.first) && std::holds_alternative<bool>(pair.second)) {
                bool val1 = std::get<bool>(pair.first), val2 = std::get<bool>(pair.second);
                
                if (node->logical_op == "=") {
                    if (val1 == val2)
                        is_correct = true;
                }
                else if (node->logical_op == "<") {
                    if (val1 == false && val2 == true)
                        is_correct = true;
                }
                else if (node->logical_op == ">") {
                    if (val1 == true && val2 == false);
                }
                else if (node->logical_op == "<>") {
                    if (val1 != val2)
                        is_correct = true;
                }
            }
            if (std::holds_alternative<std::string>(pair.first) && std::holds_alternative<std::string>(pair.second)) {
                std::string val1 = std::get<std::string>(pair.first), val2 = std::get<std::string>(pair.second);
                
                if (node->logical_op == "=") {
                    if (val1 == val2)
                        is_correct = true;
                }
                else if (node->logical_op == "<") {
                    if (val1 < val2)
                        is_correct = true;
                }
                else if (node->logical_op == ">") {
                    if (val1 > val2)
                        is_correct = true;
                }
                else if (node->logical_op == "<>") {
                    if (val1 != val2)
                        is_correct = true;
                }
            }
            else {
                reporter.report("Error: different types of data in a logical statement");
                return;
            }
            if (!is_correct)
                break;
        }
        return;
    }
    else if (node->node_type == NodeType::RETURN) {
        this->ast_return(node, idx);
    }
    else if (node->node_type == NodeType::MOVE) {
        std::string direction = node->str_val;
        int x = this->stateX, y = this->stateY;

        if (direction == "forward") {
            if (this->direction == "up") {
                y--;
            }
            else if (this->direction == "down") {
                y++;
            }
            else if (this->direction == "left") {
                x--;
            }
            else if (this->direction == "right") {
                x++; 
            }
        }
        else if (direction == "back") {
            if (this->direction == "up") {
                y++;
            }
            else if (this->direction == "down") {
                y--;
            }
            else if (this->direction == "left") {
                x++;
            }
            else if (this->direction == "right") {
                x--;
            }
        }
        else if (direction == "left") {
            if (this->direction == "up") {
                x--;
            }
            else if (this->direction == "down") {
                x++;
            }
            else if (this->direction == "left") {
                y++;
            }
            else if (this->direction == "right") {
                y--;
            }
        }
        else if (direction == "right") {
            if (this->direction == "up") {
                x++;
            }
            else if (this->direction == "down") {
                x--;
            }
            else if (this->direction == "left") {
                y--;
            }
            else if (this->direction == "right") {
                y++;
            }
        }
        if (this->is_valid_move(x, y)) {
            this->stateX = x; 
            this->stateY = y;

            if (this->field[y][x] == EXIT) {
                std::cout << "You are escaped!" << std::endl;
            }
        } 
        else {
            std::cout << "Movement is impossible: collision with an obstacle!" << std::endl;
        }
    }
    else if (node->node_type == NodeType::ROTATE) {
        std::string direction = node->str_val;

        if (direction == "rotate_left") {
            if (this->direction == "up")
                this->direction = "left";
            else if (this->direction == "down")
                this->direction = "right";
            else if (this->direction == "left")
                this->direction = "down";
            else if (this->direction == "right")
                this->direction = "up";
        }
        else if (direction == "rotate_right") {
            if (this->direction == "up")
                this->direction = "right";
            else if (this->direction == "down")
                this->direction = "left";
            else if (this->direction == "left")
                this->direction = "up";
            else if (this->direction == "right")
                this->direction = "down";
        }
    }
    for (Node* child: node->childrens)
        this->func_exec(child, idx);
}

void Ast::ast_exec() {
    int counter = 0;

    for (Node* function_node: this->functions) {
        this->variables_list.push_back(function_node->variables);
        counter++;
    }
    this->int_vectors_list.reserve(counter);
    this->bool_vectors_list.reserve(counter);
    this->string_vectors_list.reserve(counter);
    Node* function_node;
    int i = 0;

    for (; i < this->functions.size(); ++i) {
        function_node = this->functions.at(i);   

        if (function_node->name == "application")
            break;
    }
    this->func_exec(function_node, i);
}
