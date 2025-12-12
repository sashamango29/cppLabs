#include "Command.h"
#include "../controller/GameController.h"
#include <iostream>

void TickCommand::execute(GameController& controller, const std::string&) {
    controller.getModel().tick();
    controller.getView().printUniverse(controller.getModel());
}

void PrintCommand::execute(GameController& controller, const std::string&) {
    controller.getView().printUniverse(controller.getModel());
}

void LoadCommand::execute(GameController& controller, const std::string& params) {
    try {
        controller.loadFromFile(params);
        controller.getView().printMessage("Universe loaded from " + params);
    } catch (const std::exception& e) {
        controller.getView().printMessage(e.what());
    }
}

void SaveCommand::execute(GameController& controller, const std::string& params) {
    try {
        controller.saveToFile(params);
        controller.getView().printMessage("Universe saved to " + params);
    } catch (const std::exception& e) {
        controller.getView().printMessage(e.what());
    }
}

void HelpCommand::execute(GameController& controller, const std::string&) {
    controller.getView().printHelp();
}
