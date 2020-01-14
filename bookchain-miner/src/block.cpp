#include "block.hpp"

Bloock::Bloock(std::string prevHash, std::string seedHash, int64_t blockHeight) {
    this->_block.prevHash = prevHash;
    this->_block.seedHash = seedHash;
    this->_block.blockHeight = blockHeight;
    this->_block.nonce = 0;
}

std::string Bloock::prevHash() {
    return this->_block.prevHash;
}

std::string Bloock::seedHash() {
    return this->_block.seedHash;
}

int64_t Bloock::blockHeight() {
    return this->_block.blockHeight;
}

int64_t Bloock::nonce() {
    return this->_block.nonce;
}

void Bloock::setNonce(int64_t newNonce) {
    this->_block.nonce = newNonce;
}

std::string Bloock::data() {
    return this->_block.data;
}
