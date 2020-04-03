#pragma once

#include <string>

namespace bookchain {
namespace requests {

std::string getRequest(const std::string& url);
std::string postRequest(const std::string& url, const std::string& payload);

}
}