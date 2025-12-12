#pragma once
#include <string>

class GameController;

class Command {
public:
    virtual ~Command() = default;
    virtual void execute(GameController& controller, const std::string& params = "") = 0;
};

class TickCommand : public Command {
public:
    void execute(GameController& controller, const std::string&) override;
};

class PrintCommand : public Command {
public:
    void execute(GameController& controller, const std::string&) override;
};

class LoadCommand : public Command {
public:
    void execute(GameController& controller, const std::string& params) override;
};

class SaveCommand : public Command {
public:
    void execute(GameController& controller, const std::string& params) override;
};

class HelpCommand : public Command {
public:
    void execute(GameController& controller, const std::string&) override;
};

