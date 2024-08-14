#pragma once

enum NodeType {
    REPEAT,
    GROUP,
    GROUP_REFERENCE,
    CONCAT,
    OR
};

typedef struct Node {
    NodeType type;
    void* data;
    Node* childrens;
} Node;

class Ast {
    Node* root;
};
