#pragma once

#include <iostream>
#include <memory>
#include <fstream>
#include <mutex>

#include "Config.h"

class Writer {
public:
    explicit Writer(const std::shared_ptr<Config> &config);

    void writeBlock(unsigned int offset, const std::string &hash);

private:
    std::ofstream outputStream;

    std::mutex writerMutex;
};
