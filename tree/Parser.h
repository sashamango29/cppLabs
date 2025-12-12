#pragma once
#include <string>
#include "Tree.h"

class Parser {
public:
    explicit Parser(const std::string& text);
    Tree parse();
private:
    const std::string text;
    size_t pos;
    Node* S();
    Node* M();
    Node* P();
    void skipSpaces();
    bool match(char c);
    static bool isDigit(char c);
    int readInt();
};
