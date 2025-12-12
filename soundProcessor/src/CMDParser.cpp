#include "CMDParser.h"
#include <stdexcept>
#include <iostream>

TCMDParser::TCMDParser(int argc, char* argv[]) {
    if (argc < 5)
        throw std::runtime_error("Usage: ./soundProcessor -c <config.txt> <output.wav> <input1.wav> [<input2.wav> …]");

    if (std::string(argv[1]) != "-c")
        throw std::runtime_error("Expected '-c' as the second argument.");

    args.configFile = argv[2];
    args.outputFile = argv[3];

    for (int i = 4; i < argc; ++i) {
        args.inputFiles.push_back(argv[i]);
    }

    if (args.inputFiles.empty())
        throw std::runtime_error("No valid input files provided");

    TCFGParser cfgParser;
    args.instructions = cfgParser.parseConfig(args.configFile);

    if (args.instructions.empty())
        throw std::runtime_error("Config file is empty");
}
