#pragma once

#include <string>

class CommandParser {
private:
    std::string CSVFilePath = "../CSVTest/";
    int NumSkipLines = 0;

public:
    CommandParser() = default;

    void parseOptions(int argc, const char **argv);

    [[nodiscard]] std::string getCSVFilePath() const;

    [[nodiscard]] int getNumSkipLines() const;

};