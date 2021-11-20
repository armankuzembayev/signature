#pragma once

#include <iostream>
#include <fstream>
#include <memory>
#include <mutex>

#include "Config.h"

class Reader {
public:

    explicit Reader(const std::shared_ptr<Config> &config);

    unsigned int readBlock(unsigned int offset, char *buf);

    ~Reader();

private:
    std::ifstream inputStream;
    unsigned int blockSize;

    std::mutex readerMutex;
};
