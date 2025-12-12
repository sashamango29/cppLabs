#include "Parser.h"
#include "Op.h"
#include "Value.h"
#include <stdexcept>
#include <string>

Parser::Parser(const std::string& text) : text(text), pos(0) {}

Tree Parser::parse() {
    skipSpaces();
    Node* node = S();
    skipSpaces();

    if (pos != text.length()) {
        throw std::runtime_error(std::string("Непредвиденный символ '") + text[pos] + "'");
    }

    return Tree(node);
}

Node* Parser::S() {
    skipSpaces();
    Node* left = M();

    skipSpaces();
    if (match('+')) {
        Op* op = new Op(Op::Plus);
        op->left = left;
        op->right = S();
        return op;
    } else if (match('-')) {
        Op* op = new Op(Op::Minus);
        op->left = left;
        op->right = S();
        return op;
    }
    return left;
}

Node* Parser::M() {
    skipSpaces();
    Node* left = P();

    skipSpaces();
    if (match('*')) {
        Op* op = new Op(Op::Multiply);
        op->left = left;
        op->right = M();
        return op;
    } else if (match('/')) {
        Op* op = new Op(Op::Divide);
        op->left = left;
        op->right = M();
        return op;
    }
    return left;
}

Node* Parser::P() {
    skipSpaces();
    if (pos < text.length() && isDigit(text[pos])) {
        return new Value(readInt());
    } else if (match('(')) {
        Node* expr = S();
        if (!match(')')) {
            throw std::runtime_error("Отсутствует закрывающая скобка");
        }
        return expr;
    }
    throw std::runtime_error(std::string("Непредвиденный символ '") + text[pos] + "'");
}

void Parser::skipSpaces() {
    while (pos < text.length() && text[pos] == ' ') ++pos;
}

bool Parser::match(char c) {
    skipSpaces();
    if (pos < text.length() && text[pos] == c) {
        ++pos;
        skipSpaces();
        return true;
    }
    return false;
}

bool Parser::isDigit(char c) {
    return c >= '0' && c <= '9';
}

int Parser::readInt() {
    skipSpaces();
    int value = 0;
    if (pos >= text.length() || !isDigit(text[pos])) {
        throw std::runtime_error("Ожидалось число");
    }
    while (pos < text.length() && isDigit(text[pos])) {
        value = value * 10 + (text[pos] - '0');
        ++pos;
    }
    skipSpaces();
    return value;
}

