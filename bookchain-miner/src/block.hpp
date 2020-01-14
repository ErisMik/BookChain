#pragma once
#include <string>

class Bloock {
public:
    Bloock(std::string prevHash, std::string seedHash, int64_t height);

    std::string prevHash();
    std::string seedHash();
    int64_t height();

    int64_t nonce();
    void setNonce(int64_t newNonce);

    std::string data();

private:
    std::string _prevHash;
    std::string _seedHash;
    int64_t _height;

    int64_t _nonce;
    std::string _data;
};
