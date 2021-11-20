#pragma once

#include "Reader.h"
#include "Writer.h"
#include "ThreadPool.h"

class Signature {
public:
    Signature(std::shared_ptr<Config> config, std::shared_ptr<Reader> reader,
              std::shared_ptr<Writer> writer, std::unique_ptr<ThreadPool>);

    void threadManager();

private:

    static std::string getHash(const std::string &buffer);

    std::shared_ptr<Config> config;
    std::shared_ptr<Reader> reader;
    std::shared_ptr<Writer> writer;
    std::unique_ptr<ThreadPool> threadPool;

    unsigned int const HASH_SIZE = 10;
};

