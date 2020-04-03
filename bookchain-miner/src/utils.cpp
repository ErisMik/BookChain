#include "utils.hpp"
#include <iomanip>
#include <limits>
#include <random>
#include <sstream>

namespace bookchain::utils {

namespace {
constexpr char identifier[] = "Bookchain!";
}  //namespace

uint64_t identifierHash() {
    // size_t hash = std::hash<std::string> {}(&identifier[0]);
    static std::random_device rd;
    static std::uniform_int_distribution<uint64_t> dist(std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
    static const uint64_t identifier = dist(rd);

    return identifier;
}

std::string hexifystring(const std::string& data) {
    std::stringstream ss;
    ss << std::hex;

    for (auto& hexChar : data) {
        constexpr unsigned int upperBitmask = 0xff;
        ss << std::setw(2) << std::setfill('0') << (upperBitmask & static_cast<unsigned int>(hexChar));
    }

    return ss.str();
}

std::string hexifystringTruncated(const std::string& data) {
    std::string dataTrucated(data.c_str());  // NOLINT(readability-redundant-string-cstr)
    return hexifystring(dataTrucated);
}

}  // namespace bookchain::utils
