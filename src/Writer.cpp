#include "Writer.h"

using namespace std;

Writer::Writer(const shared_ptr<Config> &config) {
    auto &outputFilePath = config->getOutputFilePath();
    outputStream.open(outputFilePath, std::ios::out | std::ios::trunc);

    if (!outputStream) {
        throw runtime_error("Could not open file: " + outputFilePath);
    }
}

void Writer::writeBlock(unsigned int offset, const string &hash) {
    lock_guard guard(writerMutex);

    outputStream.seekp(offset);
    outputStream << hash;
}