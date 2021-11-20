#include <filesystem>

#include <boost/lexical_cast.hpp>

#include "Config.h"

using namespace std;

Config::Config(int argc, char *argv[]) {
    if (argc < 3) {
        throw std::invalid_argument("Invalid number of arguments!");
    }

    inputFilePath = argv[1];
    outputFilePath = argv[2];
    blockSize = argc > 3 ? boost::lexical_cast<unsigned long long int>(argv[3]) : DEFAULT_BLOCK_SIZE;
    cout << "Blocksize: " << blockSize << " bytes" << endl;

    fileSize = filesystem::file_size(inputFilePath);
    cout << "Filesize: " << fileSize << " bytes" << endl;

    numOfBlocks = fileSize / blockSize;
    if (fileSize % blockSize != 0) numOfBlocks++;
}

const std::string &Config::getInputFilePath() const {
    return inputFilePath;
}

const std::string &Config::getOutputFilePath() const {
    return outputFilePath;
}

unsigned long long Config::getBlockSize() const {
    return blockSize;
}

unsigned int Config::getNumOfBlocks() const {
    return numOfBlocks;
}
