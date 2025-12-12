#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "../model/Universe.h"
#include "../view/View.h"
#include "Command.h"

class GameController {
public:
    GameController(int rows, int cols);

    void registerCommand(const std::string& name, std::shared_ptr<Command> command);
    void run();
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename) const;

    Universe& getModel() { return model; }
    View& getView() { return view; }

private:
    Universe model;
    View view;
    std::unordered_map<std::string, std::shared_ptr<Command>> commands;
};


