#pragma once
#include <string>
#include "../model/Universe.h"

class View {
public:
    void printUniverse(const Universe& universe) const;
    void printMessage(const std::string& message) const;
    void printHelp() const;
};
