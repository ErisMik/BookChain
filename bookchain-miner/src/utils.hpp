#pragma once
#include <string>

namespace bookchain {
namespace utils {

uint64_t identifierHash();
std::string hexifystring(const std::string& data);
std::string hexifystringTruncated(const std::string& data);

}  // namespace utils
}  // namespace bookchain
