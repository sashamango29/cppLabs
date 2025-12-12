#pragma once

class Node {
public:
    virtual ~Node() {}
    [[nodiscard]] virtual int calculate() const = 0;
    [[nodiscard]] virtual int getValue() const = 0;
};
