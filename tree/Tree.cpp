#include "Tree.h"
#include "Op.h"
#include "Value.h"
#include <iostream>

Tree::Tree() : root(nullptr) {}
Tree::Tree(Node* root) : root(root) {}
Tree::~Tree() { delete root; }

int Tree::calculate() const {
    if (!root) throw std::runtime_error("Пустое дерево");
    return root->calculate();
}

static void printTree(Node* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; ++i) std::cout << "  ";
    if (Value* val = dynamic_cast<Value*>(node)) {
        std::cout << "Value: " << val->getValue() << std::endl;
    } else if (Op* op = dynamic_cast<Op*>(node)) {
        switch (op->getType()) {
            case Op::Plus: std::cout << "Op: +" << std::endl; break;
            case Op::Minus: std::cout << "Op: -" << std::endl; break;
            case Op::Multiply: std::cout << "Op: *" << std::endl; break;
            case Op::Divide: std::cout << "Op: /" << std::endl; break;
        }
        printTree(op->left, level + 1);
        printTree(op->right, level + 1);
    }
}

void Tree::print() const {
    printTree(root, 0);
}
