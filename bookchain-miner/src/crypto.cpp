#include "crypto.hpp"
#include <openssl/sha.h>

namespace bookchain {

std::string hash(void* data, size_t dataLength) {
    size_t hashLength = 20;
    unsigned char hash[hashLength];

    SHA1(reinterpret_cast<unsigned char*>(data), dataLength, hash);
    return std::string(hash, hash + sizeof(hash) / sizeof(hash[0]));
}

}  // namespace bookchain