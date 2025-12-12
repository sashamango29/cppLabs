#pragma once

#include <vector>
#include <string>
#include <memory>
#include "CFGParser.h"

struct ParsedArgs {
    std::string configFile;
    std::string outputFile;
    std::vector<std::string> inputFiles;
    std::vector<std::vector<std::string>> instructions;
};

class TCMDParser {
public:
    TCMDParser(int argc, char* argv[]);
    ~TCMDParser() = default;

    [[nodiscard]] ParsedArgs getParsedArgs() const {
        return args;
    }

private:
    ParsedArgs args;
};
