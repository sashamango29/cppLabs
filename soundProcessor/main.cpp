#include "src/CMDParser.h"
#include "src/SNDProcessor.h"

int main(int argc, char* argv[]) {
    try {
        TCMDParser parser(argc, argv);
        ParsedArgs args = parser.getParsedArgs();

        SNDProcessor processor(args.inputFiles, args.outputFile, args.instructions);
        processor.convert();
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
