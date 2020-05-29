#include "block.hpp"
#include "crypto.hpp"
#include <cstring>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

namespace bookchain {

Bloock::Bloock() :
    _block({}), _blockHash("") {
}

Bloock::Bloock(const std::string& prevHash, const std::string& seedHash, int64_t blockHeight) :
    Bloock() {
    memcpy(&this->_block.prevHash[0], prevHash.c_str(), hashLength);
    memcpy(&this->_block.seedHash[0], seedHash.c_str(), hashLength);
    this->_block.blockHeight = blockHeight;
    this->_block.nonce = 0;
}

Bloock::Bloock(const Block& block) :
    Bloock() {
    this->_block = block;
}

std::string Bloock::toJsonString(Bloock bloock) {
    nlohmann::json bloockJson;

    bloockJson["prevHash"] = bloock.block().prevHash;
    bloockJson["seedHash"] = bloock.block().seedHash;
    bloockJson["blockHeight"] = bloock.block().blockHeight;
    bloockJson["nonce"] = bloock.block().nonce;
    bloockJson["signature"] = bloock.block().signature;
    bloockJson["data"] = bloock.block().data;

    return bloockJson.dump();
}

Bloock Bloock::fromJsonString(std::string& bloockJsonString) {
    auto bloockJson = nlohmann::json::parse(bloockJsonString);

    Block block = {};
    strncpy(&block.prevHash[0], bloockJson["prevHash"].get<std::string>().c_str(), hashBufferLength);
    strncpy(&block.seedHash[0], bloockJson["seedHash"].get<std::string>().c_str(), hashBufferLength);
    block.blockHeight = bloockJson["blockHeight"];
    block.nonce = bloockJson["nonce"];
    strncpy(&block.signature[0], bloockJson["signature"].get<std::string>().c_str(), hashBufferLength);
    strncpy(&block.data[0], bloockJson["data"].get<std::string>().c_str(), blockDataLength);

    return Bloock(block);
}

Block Bloock::block() {
    return this->_block;
}

std::string Bloock::blockHash() {
    return hash(&this->_block, sizeof(this->_block));
}

std::string Bloock::prevHash() {
    return {&this->_block.prevHash[0], hashLength};
}

std::string Bloock::seedHash() {
    return {&this->_block.seedHash[0], hashLength};
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
    return {&this->_block.signature[0], hashLength};
}

void Bloock::sign(const std::string& /*privateKey*/) {
    // TODO(Eric Mikulin): 2020-01-13
}

std::string Bloock::data() {
    return {&this->_block.data[0], blockDataLength};
}

void Bloock::writeData(const std::string& newData) {
    strncpy(&this->_block.data[0], newData.c_str(), blockDataLength);
}

}  // namespace bookchain
