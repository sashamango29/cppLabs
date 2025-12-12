#include "GameController.h"
#include <fstream>
#include <iostream>
#include <sstream>

GameController::GameController(int rows, int cols)
    : model(rows, cols)
{
    registerCommand("tick", std::make_shared<TickCommand>());
    registerCommand("print", std::make_shared<PrintCommand>());
    registerCommand("load", std::make_shared<LoadCommand>());
    registerCommand("save", std::make_shared<SaveCommand>());
    registerCommand("help", std::make_shared<HelpCommand>());
}

void GameController::registerCommand(const std::string& name, std::shared_ptr<Command> command) {
    commands[name] = std::move(command);
}

void GameController::run() {
    std::string input;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, input);
        if (input == "exit") break;

        std::istringstream iss(input);
        std::string commandName, params;
        iss >> commandName;
        std::getline(iss, params);
        params.erase(0, params.find_first_not_of(" "));

        auto it = commands.find(commandName);
        if (it != commands.end()) {
            it->second->execute(*this, params);
        } else {
            view.printMessage("Unknown command. Type 'help' for a list of commands.");
        }
    }
}


void GameController::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Error opening file for reading.");

    int rows, cols;
    file >> rows >> cols;

    Universe newUniverse(rows, cols);
    int x, y;
    while (file >> x >> y) {
        newUniverse.setCell(x, y, true);
    }

    model = std::move(newUniverse);
}

void GameController::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open())
        throw std::runtime_error("Error opening file for writing.");

    const auto& grid = model.getGrid();
    int rows = static_cast<int>(grid.size());
    int cols = rows ? static_cast<int>(grid[0].size()) : 0;

    file << rows << ' ' << cols << '\n';
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (grid[i][j])
                file << i << ' ' << j << '\n';
}
