#include "Op.h"
#include <stdexcept>

Op::Op(Type type) : type(type), left(nullptr), right(nullptr) {}

Op::Type Op::getType() const {
    return type;
}

int Op::calculate() const {
    if (!left || !right) throw std::runtime_error("Ошибка: неполная операция");
    int l = left->calculate();
    int r = right->calculate();
    switch (type) {
        case Plus: return l + r;
        case Minus: return l - r;
        case Multiply: return l * r;
        case Divide:
            if (r == 0) throw std::runtime_error("Деление на ноль");
            return l / r;
    }
    throw std::runtime_error("Неизвестный оператор");
}

int Op::getValue() const {
    return calculate();
}

Op::~Op() {
    delete left;
    delete right;
}
