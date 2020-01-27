#include "crypto.hpp"
#include <openssl/sha.h>

namespace bookchain {

std::string hash(void* data, size_t dataLength) {
    constexpr size_t hashLength = 20;
    unsigned char hash[hashLength];  // NOLINT(cppcoreguidelines-avoid-c-arrays, hicpp-avoid-c-arrays, modernize-avoid-c-arrays)

    SHA1(reinterpret_cast<unsigned char*>(data), dataLength, &hash[0]);  // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    return std::string(&hash[0], &hash[0] + sizeof(hash) / sizeof(hash[0]));  // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)
}

}  // namespace bookchain