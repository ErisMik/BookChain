#pragma once
#include <string>

constexpr size_t megabyte = 1 * 1024 * 1024;

struct Block {
    char prevHash [20];
    char seedHash [20];
    int64_t blockHeight;
    int64_t nonce;

    char signature [20];
    char data [megabyte];
};

class Bloock {
public:
    Bloock(std::string prevHash, std::string seedHash, int64_t blockHeight);
    Bloock(Block block);

    Block block();
    std::string blockHash();

    std::string prevHash();
    std::string seedHash();
    int64_t blockHeight();

    int64_t nonce();
    void setNonce(int64_t newNonce);

    std::string signature();
    void sign(std::string privateKey);

    std::string data();
    void writeData(std::string newData);

private:
    Block _block;
    std::string _blockHash;
};
