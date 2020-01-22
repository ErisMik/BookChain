#include "block.hpp"
#include "crypto.hpp"
#include <cstring>
#include <iostream>
#include <string>

namespace bookchain {

Bloock::Bloock() {
    this->_block = {};
}

Bloock::Bloock(std::string prevHash, std::string seedHash, int64_t blockHeight) {
    this->_block = {};
    memcpy(this->_block.prevHash, prevHash.c_str(), hashLength);
    memcpy(this->_block.seedHash, seedHash.c_str(), hashLength);
    this->_block.blockHeight = blockHeight;
    this->_block.nonce = 0;
}

Bloock::Bloock(const Block& block) {
    this->_block = {};
    this->_block = block;
}

Block Bloock::block() {
    return this->_block;
}

std::string Bloock::blockHash() {
    return hash(&this->_block, sizeof(this->_block));
}

std::string Bloock::prevHash() {
    return {this->_block.prevHash, hashLength};
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

std::string Bloock::signature() {
    return this->_block.signature;
}

void Bloock::sign(std::string privateKey) {
    // TODO: Eric Mikulin, 2020-01-13
}

std::string Bloock::data() {
    return this->_block.data;
}

void Bloock::writeData(std::string newData) {
    strcpy(this->_block.data, newData.c_str());
}

}  // namespace bookchain
