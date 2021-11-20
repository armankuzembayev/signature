#pragma once

#include <iostream>

class Config {
public:
    Config(int argc, char *argv[]);

    [[nodiscard]] const std::string &getInputFilePath() const;

    [[nodiscard]] const std::string &getOutputFilePath() const;

    [[nodiscard]] unsigned long long getBlockSize() const;

    [[nodiscard]] unsigned int getNumOfBlocks() const;

private:
    std::string inputFilePath;
    std::string outputFilePath;
    unsigned long long blockSize;
    unsigned long long fileSize;
    unsigned int numOfBlocks;

    const unsigned int DEFAULT_BLOCK_SIZE = 1024 * 1024;
};
