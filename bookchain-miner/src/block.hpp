#pragma once
#include <string>

struct Block {
    char prevHash [1];
    char seedHash [1];
    int64_t blockHeight;
    int64_t nonce;
    char data [1];
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
