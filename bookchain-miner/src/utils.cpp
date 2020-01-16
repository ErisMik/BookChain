#include "utils.hpp"
#include <iomanip>
#include <sstream>

namespace bookchain {
namespace utils {

std::string hexifystring(std::string data) {
    std::stringstream ss;
    ss << std::hex;

    for (auto& hexChar : data) {
        ss << std::setw(2) << std::setfill('0') << (0xff & static_cast<unsigned int>(hexChar));
    }

    return ss.str();
}

} // namespace utils
} // namespace bookchain
