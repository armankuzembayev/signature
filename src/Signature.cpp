#include <boost/crc.hpp>

#include "Signature.h"

using namespace std;

Signature::Signature(shared_ptr<Config> config, shared_ptr<Reader> reader,
                     shared_ptr<Writer> writer, unique_ptr<ThreadPool> threadPool) {
    this->config = move(config);
    this->reader = move(reader);
    this->writer = move(writer);
    this->threadPool = move(threadPool);
}

void Signature::threadManager() {
    auto blockSize = config->getBlockSize();
    auto numOfBlocks = config->getNumOfBlocks();
    for (int blockIdx = 0; blockIdx < numOfBlocks; blockIdx++) {
        threadPool->submit([this, blockIdx, blockSize]() {
            try {
                auto buffer = make_unique<string>(blockSize, '\n');
                auto read = reader->readBlock(blockIdx * blockSize, buffer->data());
                auto hash = getHash(*buffer);
                writer->writeBlock(blockIdx * HASH_SIZE, hash);
            } catch (const exception &e) {
                cout << e.what() << endl;
            }
        });
    }
}

string Signature::getHash(const string &buffer) {
    boost::crc_32_type hash;
    hash.process_bytes(buffer.data(), buffer.size());
    string output = to_string(hash.checksum());

    return string(10 - output.size(), '0') + output;
}