#include <vector>

enum class NodeType {
    FUNCTION_DECLARATION,
    FUNCTION_CALL
};

typedef struct Node {
    NodeType type;
} Node;

class Ast {
    std::vector<Node*> functions;
};
