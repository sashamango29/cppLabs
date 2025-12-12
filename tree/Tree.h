#pragma once
#include "Node.h"

class Tree {
public:
    Node* root;
    Tree();
    explicit Tree(Node* root);
    ~Tree();
    void print() const;
    [[nodiscard]] int calculate() const;
};
