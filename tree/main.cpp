#include <iostream>
#include "Parser.h"

int main() {
    std::string input;
    std::cout << "Введите арифметическое выражение: ";
    std::getline(std::cin, input);

    Parser parser(input);

    try {
        Tree tree = parser.parse();
        std::cout << "Дерево разбора:" << std::endl;
        tree.print();
        std::cout << "Результат вычисления: " << tree.calculate() << std::endl;
    } catch (const std::runtime_error& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }
    return 0;
}

