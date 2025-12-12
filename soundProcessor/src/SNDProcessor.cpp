#include "SNDProcessor.h"
#include <stdexcept>

SNDProcessor::SNDProcessor(const std::vector<std::string>& inputFiles,
                               const std::string& outputFilePath,
                               const std::vector<std::vector<std::string>>& instr)
    : instructions(instr) {
    output = std::make_unique<TWav>(outputFilePath);

    for (const auto& path : inputFiles) {
        try {
            this->inputs.push_back(std::make_unique<TWavReader>(path));
        } catch (const std::exception& e) {
            std::cerr << "Failed to open input file " << path << ": " << e.what() << std::endl;
        }
    }

    if (this->inputs.empty())
        throw std::runtime_error("No valid input files provided");
}

void SNDProcessor::convert() {
    TConverterFactory factory;
    std::unique_ptr<IConverter> converter;
    TWavFormat format(output.get());

    copyInitialFile(format, instructions[0][1]);

    for (const auto& instr : instructions) {
        if (instr.empty()) continue;

        std::cout << "Processing instruction: " << instr[0] << std::endl;
        converter = factory.MakeConverter(instr[0]);

        if (instr.size() > 3) {
            std::string numStr = instr[1];
            numStr.erase(0, 1);
            size_t fileNum = std::stoull(numStr);
            if (fileNum == 0 || fileNum > inputs.size())
                throw std::runtime_error("Invalid input file number in config");

            format.Open(inputs[fileNum - 1].get());
            std::cout << "Opened input file: " << fileNum << std::endl;
        }

        std::cout << "Converting..." << std::endl;
        converter->Convert(format, const_cast<std::vector<std::string>&>(instr));
        std::cout << "Conversion done." << std::endl;
    }
}

void SNDProcessor::copyInitialFile(TWavFormat& format, const std::string& strFileNum) {
    size_t fileNum = std::stoull(strFileNum.substr(1));
    if (fileNum == 0 || fileNum > inputs.size())
        throw std::runtime_error("Invalid input file number in copyInitialFile()");

    output->copyHeader(*(inputs[fileNum - 1].get()));
    output->writeHeader();
    format.Open(inputs[fileNum - 1].get());

    size_t lastSample = format.getLastSample();
    size_t inPos = inputs[fileNum - 1]->getCurrentPos();
    size_t outPos = output->getCurrentPos();

    for (size_t i = 0; i < lastSample; ++i) {
        int16_t sample = format.getExtraSample();
        format.sendSample(sample);
    }

    inputs[fileNum - 1]->seekg(inPos);
    output->seekp(outPos);
}
