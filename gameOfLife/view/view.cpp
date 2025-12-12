#include "View.h"
#include <iostream>

void View::printUniverse(const Universe& universe) const {
    const auto& grid = universe.getGrid();
    for (const auto& row : grid) {
        for (bool cell : row)
            std::cout << (cell ? 'O' : '.') << ' ';
        std::cout << '\n';
    }
}

void View::printMessage(const std::string& message) const {
    std::cout << message << '\n';
}

void View::printHelp() const {
    std::cout << "Available commands:\n"
              << "  tick          - Advance the simulation by one step\n"
              << "  print         - Display the current state of the universe\n"
              << "  load <file>   - Load universe from a file\n"
              << "  save <file>   - Save current universe to a file\n"
              << "  help          - Show this help message\n"
              << "  exit          - Quit the program\n";
}
