#include "CommandParser.h"
#include <stdexcept>
#include <string>

std::string CommandParser::getCSVFilePath() const {
    return CSVFilePath;
}

int CommandParser::getNumSkipLines() const {
    return NumSkipLines;
}

void CommandParser::parseOptions(int argc, const char **argv) {
    if (argc < 2) {
        throw std::invalid_argument("Missing CSV file argument");
    }

    CSVFilePath += argv[1];

    if (argc >= 3) {
        NumSkipLines = std::stoi(argv[2]);
        if (NumSkipLines < 0)
            throw std::invalid_argument("Negative number of skip lines");
    }
}

