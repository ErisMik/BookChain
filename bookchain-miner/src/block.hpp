#pragma once
#include <string>

struct Block {
    std::string prevHash;
    std::string seedHash;
    int64_t blockHeight;
    int64_t nonce;
    std::string data;
};

class Bloock {
public:
    Bloock(std::string prevHash, std::string seedHash, int64_t blockHeight);

    std::string prevHash();
    std::string seedHash();
    int64_t blockHeight();

    int64_t nonce();
    void setNonce(int64_t newNonce);

    std::string data();

private:
    Block _block;
    std::string _blockHash;
};
