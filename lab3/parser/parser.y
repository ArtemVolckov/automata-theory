%{
#include <iostream>
#include <string>
#include "../ast/ast.hpp"

Ast ast;

struct Value {
    int int_val;
    std::string str_val;
    // pair.fist = variable name; pair.second = variable.value
    std::vector<std::pair<std::variant<std::string, char>, std::variant<int, bool, std::string, char>>> variables;
    bool is_elipsis, is_int_val, is_bool_val, is_str_val, is_variable, is_vector;
    std::pair<std::variant<int, bool, std::string>, std::variant<int, bool, std::string, char>> logical_op_variables;
    std::string logical_op;
    Node* new_node;
    std::vector<Node*> statements;
    std::vector<std::vector<Node*>> statements_list;
};

#define YYSTYPE Value

int yylex();
void yyerror(std::string err_msg);
%}

%token INTEGER_LITERAL STRING_LITERAL BOOL_LITERAL NAME
%token ASSIGN TO ELIPSIS TYPE ARITHMETIC_OP LOGICAL_OP
%token VECTOR PUSH_POP_FRONT_BACK
%token DO UNTIL 
%token IF THEN ELSE 
%token FUNCTION RETURN

%right '=' ASSIGN
%left ARITHMETIC_OP
%left LOGICAL_OP

%nonassoc '(' ')'
%nonassoc '[' ']'

%%
program:
    | function_declarations
    ;

function_declarations:
    function_declarations function_declaration '\n' {
        ast.functions.push_back($2.new_node);
    }
    function_declarations function_declaration {
        ast.functions.push_back($2.new_node);
    }
    | function_declaration '\n' {
        ast.functions.push_back($1.new_node);
    }
    | function_declaration {
        ast.functions.push_back($1.new_node);
    }
    | '\n'
    ;

function_declaration:
    FUNCTION TYPE NAME '(' parameter_list ')' '\n' statements {
        $$.new_node = new Node(NodeType::FUNCTION_DECLARATION, $2.str_val, $3.str_val, $5.variables, $8.statements, $5.is_elipsis);
    }
    ;

parameter_list:
    parameter_list ',' ELIPSIS {
        for (auto pair: $1.variables)
            $$.variables.push_back(pair);
        $$.is_elipsis = true;
    }
    | parameter_list ',' parameter {
        for (auto pair: $1.variables)
            $$.variables.push_back(pair);
        $$.variables.push_back($3.variables.back());
    }
    | parameter {
        $$.variables.push_back($1.variables.back());   
    }
    |
    ;

parameter:
    NAME '=' INTEGER_LITERAL {
        $$.variables.push_back(std::make_pair($1.str_val, $3.int_val));
    }
    | NAME '=' BOOL_LITERAL {
        bool bool_val = false;

        if ($3.str_val == "true")
            bool_val = true;    
        $$.variables.push_back(std::make_pair($1.str_val, bool_val));
    }
    | NAME '=' STRING_LITERAL {
        $$.variables.push_back(std::make_pair($1.str_val, $3.str_val));
    } 
    | NAME {
        $$.variables.push_back(std::make_pair($1.str_val, '\0'));
    }
    ;

statements:
    statements statement {
        for (Node* new_node: $1.statements)
            $$.statements.push_back(new_node);
        $$.statements.push_back($2.new_node);    
    }
    | statement {
        $$.statements.push_back($1.new_node);
    }
    ;

statement:
    TYPE variables_list '\n' {
        $$.new_node = new Node(NodeType::VARIABLES_INIT, $1.str_val, $2.variables);
    }
    | VECTOR TYPE vector_variables_list '\n' {
        $$.new_node = new Node($2.str_val, $3.variables, NodeType::VECTOR_INIT);
    }
    | NAME ASSIGN expression '\n' {
        $$.new_node = new Node(NodeType::ASSIGN, $1.str_val, $3.is_int_val, $3.is_bool_val, $3.is_str_val, $3.is_variable, $3.is_vector, $3.int_val, $3.str_val);
    }
    | NAME PUSH_POP_FRONT_BACK expression '\n' {
        $$.new_node = new Node(NodeType::PUSH_POP_FRONT_BACK, $1.str_val, $2.str_val, $3.is_int_val, $3.is_bool_val, $3.is_str_val, $3.is_variable, $3.is_vector, $3.int_val, $3.str_val);
    } 
    | NAME TO TYPE '\n' {
        $$.new_node = new Node($1.str_val, NodeType::NAME_TO_TYPE, $3.str_val);
    } 
    | NAME TO NAME '\n' {
        $$.new_node = new Node(NodeType::NAME_TO_NAME, $1.str_val, $3.str_val);
    }
    | IF bool_expression THEN statements else_list {
        $$.new_node = new Node(NodeType::IF, $2.logical_op_variables, $2.logical_op, $4.statements, $5.statements_list); 
    }
    | DO statements UNTIL bool_expression '\n' {
        $$.new_node = new Node(NodeType::DO, $2.statements, $4.logical_op_variables, $4.logical_op); 
    }
    | NAME '(' func_call_parameter_list ')' '\n' {
        $$.new_node = new Node($1.str_val, NodeType::FUNCTION_CALL, $3.variables);
    }
    | RETURN expression '\n' {
        $$.new_node = new Node(NodeType::RETURN, $2.is_int_val, $2.is_bool_val, $2.is_str_val, $2.is_variable, $2.is_vector, $2.int_val, $2.str_val);
    }
    ;

func_call_parameter_list:
    func_call_parameter_list ',' func_call_parameter {
        for (auto pair: $1.variables)
            $$.variables.push_back(pair);
        $$.variables.push_back($3.variables.back());
    }
    | func_call_parameter {
        $$.variables.push_back($1.variables.back());   
    }
    |
    ;

func_call_parameter:
    NAME '=' INTEGER_LITERAL {
        $$.variables.push_back(std::make_pair($1.str_val, $3.int_val));
    }
    | NAME '=' BOOL_LITERAL {
        bool bool_val = false;

        if ($3.str_val == "true")
            bool_val = true;    
        $$.variables.push_back(std::make_pair($1.str_val, bool_val));
    }
    | NAME '=' STRING_LITERAL {
        $$.variables.push_back(std::make_pair($1.str_val, $3.str_val));
    } 
    | INTEGER_LITERAL {
        $$.variables.push_back(std::make_pair('\0', $1.int_val));
    }
    | BOOL_LITERAL {
        bool bool_val = false;

        if ($1.str_val == "true")
            bool_val = true;
        $$.variables.push_back(std::make_pair('\0', bool_val));
    }
    | STRING_LITERAL {
        $$.variables.push_back(std::make_pair('\0', $1.str_val));
    }
    ;
 
else_list:
    else_list ELSE statements {
        for (auto statements: $1.statements_list)
            $$.statements_list.push_back(statements);
        $$.statements_list.push_back($3.statements);

    }
    | ELSE statements {
        $$.statements_list.push_back($2.statements);
    }
    | {

    }
    ;

variables_list:
    variables_list ',' variable {
        for (auto pair: $1.variables)
            $$.variables.push_back(pair);
        $$.variables.push_back($3.variables.back());
    }
    | variable {
        $$.variables.push_back($1.variables.back());   
    }
    ;

variable:
    NAME ASSIGN INTEGER_LITERAL {
        $$.variables.push_back(std::make_pair($1.str_val, $3.int_val));
    }
    | NAME ASSIGN BOOL_LITERAL {
        bool bool_val = false;

        if ($3.str_val == "true")
            bool_val = true;
        $$.variables.push_back(std::make_pair($1.str_val, bool_val));
    }
    | NAME ASSIGN STRING_LITERAL {
        $$.variables.push_back(std::make_pair($1.str_val, $2.str_val));
    }
    | NAME {
        $$.variables.push_back(std::make_pair($1.str_val, '\0'));
    }
    ;

vector_variables_list:
    vector_variables_list ',' vector_variable {
        for (auto pair: $1.variables)
            $$.variables.push_back(pair);
        $$.variables.push_back($3.variables.back());
    }
    | vector_variable {
        $$.variables.push_back($1.variables.back());
    }
    ;

vector_variable:
    NAME {
        $$.variables.push_back(std::make_pair($1.str_val, '\0'));
    }
    ;

bool_expression:
    BOOL_LITERAL {
        bool bool_val = false;

        if ($1.str_val == "true")
            bool_val = true;
        $$.logical_op_variables = std::make_pair(bool_val, '\0');
    }
    | expression LOGICAL_OP expression {
        if ($1.is_int_val && $3.is_int_val) {
            $$.logical_op_variables = std::make_pair($1.int_val, $3.int_val);
            $$.logical_op = $2.str_val;
        }
        else if ($1.is_bool_val && $3.is_bool_val) {
            bool first_bool_val = false;
            bool second_bool_val = false;

            if ($1.str_val == "true")
                first_bool_val = true;
            if ($3.str_val == "true")
                second_bool_val = true;
            $$.logical_op_variables = std::make_pair(first_bool_val, second_bool_val);
            $$.logical_op = $2.str_val;
        }
        else if ($1.is_str_val && $3.is_str_val) {
            $$.logical_op_variables = std::make_pair($1.str_val, $3.str_val);
            $$.logical_op = $2.str_val;
        }
        else {
            yyerror("Trying to execute logical operation using different types");
            return 1;
        }
    }
    | expression '=' expression {
        if ($1.is_int_val && $3.is_int_val) {
            $$.logical_op_variables = std::make_pair($1.int_val, $3.int_val);
            $$.logical_op = "=";
        }
        else if ($1.is_bool_val && $3.is_bool_val) {
            bool first_bool_val = false;
            bool second_bool_val = false;

            if ($1.str_val == "true")
                first_bool_val = true;
            if ($3.str_val == "true")
                second_bool_val = true;
            $$.logical_op_variables = std::make_pair(first_bool_val, second_bool_val);
            $$.logical_op = "=";
        }
        else if ($1.is_str_val && $3.is_str_val) {
            $$.logical_op_variables = std::make_pair($1.str_val, $3.str_val);
            $$.logical_op = "=";
        }
        else {
            yyerror("Trying to execute logical operation using different types");
            return 1;
        }
    }
    ;

expression:
    | expression ARITHMETIC_OP expression {
        if ($1.is_int_val && $3.is_int_val) {
            $$.is_int_val = true;
            
            if ($2.str_val == "+")
                $$.int_val = $1.int_val + $3.int_val;
            else 
                $$.int_val = $1.int_val - $3.int_val;
        } 
        else if ($1.is_bool_val && $3.is_bool_val) {
            if ($1.str_val == "true" || $3.str_val == "true") {
                if ($2.str_val == "+")
                    $$.str_val = "true";
                else 
                    $$.str_val = "false";
            }
            else {
                if ($2.str_val == "+")
                    $$.str_val = "false";
                else 
                    $$.str_val = "true";
            }
            $$.is_bool_val = true;
        }
        else if ($1.is_str_val && $3.is_str_val) {
            if ($2.str_val == "+") 
                $$.str_val = $1.str_val + $3.str_val;
            else {
                std::string result = $1.str_val;
                size_t pos = result.find($3.str_val);

                if (pos != std::string::npos)
                    result.erase(pos, $3.str_val.length());
                $$.str_val = result;    
            }
            $$.is_str_val = true; 
        }
        else {
            yyerror("Trying to execute arithmetic operation using different types");
            return 1;
        }
    }
    NAME '[' INTEGER_LITERAL ']' {
        if ($3.int_val < 0) {
            yyerror("Trying to access an element of a vector with a negative index");
            return 1;
        }
        $$.is_vector = true;
        $$.int_val = $3.int_val;
        $$.str_val = $1.str_val;
    }
    | INTEGER_LITERAL {
        $$.is_int_val = true;
        $$.int_val = $1.int_val;
    }
    | BOOL_LITERAL {
        $$.is_bool_val = true;
        $$.str_val = $1.str_val;
    }
    | STRING_LITERAL {
        $$.is_str_val = true;
        $$.str_val = $1.str_val;
    }
    | NAME {
        $$.is_variable = true;
        $$.str_val = $1.str_val;
    } 
    ;
%%

void yyerror(std::string err_msg) {
    std::cerr << err_msg << std::endl;
}

int main() {
    if (yyparse() == 0) {
        std::cout << "Parsing completed successfully.";

        if (is_error) {
            std::cerr << reporter.err_msg << std::endl;
            return 1;
        }
    }
    else {
        std::cerr << "Parsing failed." << std::endl;
        return 1;
    }
    return 0;
}
