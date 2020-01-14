#pragma once
#include <string>

constexpr size_t kilobyte = 1 * 1024;

struct Block {
    char prevHash [20];
    char seedHash [20];
    int64_t blockHeight;
    int64_t nonce;
    char data [10 * kilobyte];
};

class Bloock {
public:
    Bloock(std::string prevHash, std::string seedHash, int64_t blockHeight);

    std::string blockHash();

    std::string prevHash();
    std::string seedHash();
    int64_t blockHeight();

    int64_t nonce();
    void setNonce(int64_t newNonce);

    std::string data();

private:
    Block _block;
    std::string _blockHash;
    size_t _dataLength;
};
