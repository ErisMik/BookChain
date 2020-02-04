#include "utils.hpp"
#include <iomanip>
#include <sstream>

namespace bookchain::utils {

namespace {
const std::string identifier = "Bookchain!";
}

uint64_t identifierHash() {
    size_t hash = std::hash<std::string> {}(identifier);
    return uint64_t(hash);
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
    std::string dataTrucated(data.c_str());
    return hexifystring(dataTrucated);
}

}  // namespace bookchain::utils
