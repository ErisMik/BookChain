#include "block.hpp"
#include <cstring>
#include <iostream>
#include <openssl/sha.h>
#include <string>

Bloock::Bloock(std::string prevHash, std::string seedHash, int64_t blockHeight) {
    this->_block = {};
    strcpy(this->_block.prevHash, prevHash.c_str());
    strcpy(this->_block.seedHash, seedHash.c_str());
    this->_block.blockHeight = blockHeight;
    this->_block.nonce = 0;
    strcpy(this->_block.data, "i");
}

void print_bytes(const void *object, size_t size)
{
  // This is for C++; in C just drop the static_cast<>() and assign.
  const unsigned char * const bytes = static_cast<const unsigned char *>(object);
  size_t i;

  printf("[ ");
  for(i = 0; i < size; i++)
  {
    printf("%02x ", bytes[i]);
  }
  printf("]\n");
}

std::string Bloock::blockHash() {
    size_t hashLength = 20;
    unsigned char hash[hashLength];
    Block testBlock = this->_block;
    SHA1(reinterpret_cast<unsigned char*>(&testBlock), sizeof(this->_block), hash);

    print_bytes(&testBlock, sizeof(testBlock));

    std::string hashString(hash, hash + sizeof(hash) / sizeof(hash[0]));
    std::cout << hashString << std::endl;
    return "";
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
