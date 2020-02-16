#pragma once

#include "queue.hpp"
#include <string>

namespace bookchain {

void minerMainLoop(const sharedTSQueue<std::string>& dataQueue);

}  // namespace bookchain
