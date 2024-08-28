typedef enum NodeType {
    FUNCTION_DECLARATION,
    FUNCTION_CALL
} NodeType;

typedef struct Node {
    NodeType type;
} Node;

typedef struct Ast {
    int counter;
    Node** functions;
} Ast;
