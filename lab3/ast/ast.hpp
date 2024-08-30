#pragma once

#include <iostream>
#include <vector>
#include <variant>
#include <string>
#include <unordered_set>

typedef struct Reporter {
    std::string err_msg;
    void report(std::string err_msg);
} Reporter;

#ifndef GLOBAL_VARIABLES
#define GLOBAL_VARIABLES

extern bool is_error;
extern Reporter reporter;

#endif

const char WALL = '#';   
const char EXIT = '$';  
const char EMPTY = '0'; 
                         
enum class NodeType {
    FUNCTION_DECLARATION,
    FUNCTION_CALL,
    VARIABLES_INIT,
    VECTOR_INIT,
    ASSIGN,
    PUSH_POP_FRONT_BACK,    
    NAME_TO_NAME,
    NAME_TO_TYPE,
    IF,
    DO,
    RETURN,
    MOVE,
    ROTATE,
    ACTION
};

typedef struct Node {
    NodeType node_type;
    std::string name;
    std::string type;
    std::vector<std::pair<std::variant<std::string, char>, std::variant<int, bool, std::string, char>>> variables;
    bool is_elipsis;
    std::pair<std::variant<int, bool, std::string>, std::variant<int, bool, std::string, char>> logical_op_variables;
    std::string logical_op;
    std::vector<Node*> childrens;
    std::vector<std::vector<Node*>> statements_list;
    bool is_int_val, is_bool_val, is_str_val, is_variable, is_vector; 
    int int_val; 
    std::string str_val;
    std::string push_pop_front_back;
    std::string name_from, name_to;
    //std::vector<std::vector

    // FUNCTION_DECLARATION
    Node(NodeType node_type, std::string type, std::string name, std::vector<std::pair<std::variant<std::string, char>, std::variant<int, bool, std::string, char>>> variables, std::vector<Node*> statements, bool is_elipsis) {
       this->node_type = node_type;
       this->name = name;
       this->type = type;
       this->variables = variables;

       if (statements.size() == 0) 
           reporter.report("Error: function definition with no statements");
       this->childrens = statements; 
       this->is_elipsis = is_elipsis;
    }
    // FUNCTION_CALL
    Node(std::string func_name, NodeType node_type, std::vector<std::pair<std::variant<std::string, char>, std::variant<int, bool, std::string, char>>> variables) {
        this->node_type = node_type;
        this->name = func_name;
        this->variables == variables;    
    }
    // VARIABLES_INIT
    Node(NodeType node_type, std::string type, std::vector<std::pair<std::variant<std::string, char>, std::variant<int, bool, std::string, char>>> variables) {
        this->node_type = node_type;
        this->type = type;
        this->variables = variables;
    }
    // VECTOR_INIT
    Node(std::string type, std::vector<std::pair<std::variant<std::string, char>, std::variant<int, bool, std::string, char>>> variables, NodeType node_type) {
        this->node_type = node_type;
        this->type = type;
        this->variables = variables;
    }
    // ASSIGN
    Node(NodeType node_type, std::string name, bool is_int_val, bool is_bool_val, bool is_str_val, bool is_variable, bool is_vector, int int_val, std::string str_val) {
        this->node_type = node_type;
        this->name = name;
        
        if (is_int_val == true) {
            this->is_int_val = true;
            this->int_val = int_val;
        }
        else if (is_bool_val == true) {
            this->is_bool_val = true;
            this->str_val = str_val;
        }
        else if (is_str_val == true) {
            this->is_str_val = true;
            this->str_val = str_val;
        }
        else if (is_vector == true) {
            this->is_vector = true;
            this->int_val = int_val;
            this->str_val = str_val;
        }
    }
    // PUSH_POP_FRONT_BACK
    Node(NodeType node_type, std::string name, std::string push_pop_front_back, bool is_int_val, bool is_bool_val, bool is_str_val, bool is_variable, bool is_vector, int int_val, std::string str_val) {
        this->node_type = node_type;
        this->name = name;
        this->push_pop_front_back = push_pop_front_back;

        if (is_int_val == true) {
            this->is_int_val = true;
            this->int_val = int_val;
        }
        else if (is_bool_val == true) {
            this->is_bool_val = true;
            this->str_val = str_val;
        }
        else if (is_str_val == true) {
            this->is_str_val = true;
            this->str_val = str_val;
        }
        else if (is_vector == true) {
            this->is_vector = true;
            this->int_val = int_val;
            this->str_val = str_val;
        }
    }
    // NAME_TO_TYPE
    Node(std::string name_from, NodeType node_type, std::string type) {
        this->node_type = node_type;
        this->name_from = name_from;
        this->type = type;
    }
    // NAME_TO_NAME
    Node(NodeType node_type, std::string name_from, std::string name_to) {
        this->node_type = node_type;
        this->name_from = name_from;
        this->name_to = name_to;
    }
    // IF
    Node(NodeType node_type, std::pair<std::variant<int, bool, std::string>, std::variant<int, bool, std::string, char>> logical_op_variables, std::string logical_op, std::vector<Node*> statements, std::vector<std::vector<Node*>> statements_list) {
        this->node_type = node_type;
        this->logical_op_variables = logical_op_variables;
        this->logical_op = logical_op;
        this->statements_list.push_back(statements);

        for (auto tmp_statements: statements_list)
            this->statements_list.push_back(tmp_statements);
    }
    // DO
    Node(NodeType node_type, std::vector<Node*> statements, std::pair<std::variant<int, bool, std::string>, std::variant<int, bool, std::string, char>> logical_op_variables, std::string logical_op) {
        this->node_type = node_type;
        this->childrens = statements;
        this->logical_op_variables = logical_op_variables;
        this->logical_op = logical_op;
    } 
    // RETURN
    Node(NodeType node_type, bool is_int_val, bool is_bool_val, bool is_str_val, bool is_is_variable, bool is_vector, int int_val, std::string str_val) {
        this->node_type = node_type;
        
        if (is_int_val == true) {
            this->is_int_val = true;
            this->int_val = int_val;
        }
        else if (is_bool_val == true) {
            this->is_bool_val = true;
            this->str_val = str_val;
        }
        else if (is_str_val == true) {
            this->is_str_val = true;
            this->str_val = str_val;
        }
        else if (is_vector == true) {
            this->is_vector = true;
            this->int_val = int_val;
            this->str_val = str_val;
        }
    }
    // MOVE
    Node(NodeType node_type, std::string str_val, int tmp) {
        this->node_type = node_type;
        this->str_val = str_val;
    }
    // ROTATE
    Node(NodeType node_type, std::string str_val, bool tmp) {
        this->node_type = node_type;
        this->str_val = str_val;
    }
    // ACTION
    Node(NodeType node_type, std::string str_val, char tmp) {
        this->node_type = node_type;
        this->str_val = str_val;
    }

    ~Node() {
        for (Node* child: this->childrens)
            delete child;
    }
} Node;

class Ast {
    public:
        std::vector<Node*> functions;
        std::vector<std::vector<std::pair<std::variant<std::string, char>, std::variant<int, bool, std::string, char>>>> variables_list;
        std::vector<std::pair<std::string, std::vector<int>>> int_vectors_list; 
        std::vector<std::pair<std::string, std::vector<bool>>> bool_vectors_list; 
        std::vector<std::pair<std::string, std::vector<std::string>>> string_vectors_list; 
        void ast_prepare();
        void ast_return(Node* return_node, int idx);
        void func_exec(Node* node, int idx);
        void ast_exec();
        std::vector<std::vector<char>> field;
        int stateX;
        int stateY;
        std::string direction = "up";
        bool is_valid_move(int x, int y);
        
        ~Ast() {
            for (Node* child: functions)
                delete child;
        }
};
