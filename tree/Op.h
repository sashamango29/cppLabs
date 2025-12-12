#pragma once
#include "Node.h"

class Op : public Node {
public:
    enum Type { Plus, Minus, Multiply, Divide };
    explicit Op(Type type);
    [[nodiscard]] Type getType() const;
    Node* left;
    Node* right;
    [[nodiscard]] int calculate() const override;
    [[nodiscard]] int getValue() const override;
    ~Op() override;
private:
    Type type;
};
