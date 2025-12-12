#pragma once
#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "Sound.h"
#include "Factory.h"
#include "Converters.h"

class SNDProcessor {
public:
    SNDProcessor(const std::vector<std::string>& inputFiles,
                   const std::string& outputFile,
                   const std::vector<std::vector<std::string>>& instructions);

    void convert();

private:
    std::vector<std::unique_ptr<TWavReader>> inputs;
    std::unique_ptr<TWav> output;
    std::vector<std::vector<std::string>> instructions;

    void copyInitialFile(TWavFormat& format, const std::string& strFileNum);
};
