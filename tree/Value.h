#pragma once
#include "Node.h"

class Value : public Node {
public:
    explicit Value(int value);
    [[nodiscard]] int calculate() const override;
    [[nodiscard]] int getValue() const override;
private:
    int value;
};
