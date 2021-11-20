#include "Reader.h"

using namespace std;

Reader::Reader(const shared_ptr<Config> &config) {

    auto &inputFilePath = config->getInputFilePath();
    blockSize = config->getBlockSize();

    inputStream.open(inputFilePath, ifstream::binary);

    if (!inputStream) {
        throw runtime_error("Could not open file: " + inputFilePath);
    }
}

unsigned int Reader::readBlock(unsigned int offset, char* buf) {
    lock_guard guard(readerMutex);

    inputStream.seekg(offset);
    inputStream.read(buf, blockSize);

    if (inputStream.bad()) {
        throw runtime_error("Could not read data");
    }
    return inputStream.gcount();
}

Reader::~Reader() {
    inputStream.close();
}
