#include "utils.hpp"
#include <iomanip>
#include <sstream>

namespace bookchain::utils {

std::string hexifystring(const std::string& data) {
    std::stringstream ss;
    ss << std::hex;

    for (auto& hexChar : data) {
        constexpr unsigned int upperBitmask = 0xff;
        ss << std::setw(2) << std::setfill('0') << (upperBitmask & static_cast<unsigned int>(hexChar));
    }

    return ss.str();
}

}  // namespace bookchain::utils
