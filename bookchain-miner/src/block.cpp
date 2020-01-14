#include "block.hpp"

Bloock::Bloock(std::string prevHash, std::string seedHash, int64_t height) :
    _prevHash(std::move(prevHash)),
    _seedHash(std::move(seedHash)),
    _height(height),
    _nonce(0),
    _data("") {
}

std::string Bloock::prevHash() {
    return this->_prevHash;
}

std::string Bloock::seedHash() {
    return this->_seedHash;
}

int64_t Bloock::height() {
    return this->_height;
}

int64_t Bloock::nonce() {
    return this->_nonce;
}

void Bloock::setNonce(int64_t newNonce) {
    this->_nonce = newNonce;
}

std::string Bloock::data() {
    return this->_data;
}
