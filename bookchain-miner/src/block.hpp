#pragma once

#include <string>

namespace bookchain {

constexpr size_t hashLength = 20;
constexpr size_t hashBufferLength = hashLength + 1;  // Saving room for the null byte
constexpr size_t blockDataLength = 1 * 1024 * 1024;  // 1 megabyte

struct Block {
    char prevHash[hashBufferLength];
    char seedHash[hashBufferLength];
    int64_t blockHeight;
    int64_t nonce;

    char signature[hashBufferLength];
    char data[blockDataLength];
};

class Bloock {
public:
    Bloock();
    Bloock(const std::string& prevHash, const std::string& seedHash, int64_t blockHeight);
    explicit Bloock(const Block& block);

    Block block();
    std::string blockHash();

    std::string prevHash();
    std::string seedHash();
    int64_t blockHeight();

    int64_t nonce();
    void setNonce(int64_t newNonce);

    std::string signature();
    void sign(const std::string& privateKey);

    std::string data();
    void writeData(const std::string& newData);

private:
    Block _block;
    char _blockHash[hashBufferLength];
};

}  // namespace bookchain
