#pragma once

#include "peers.hpp"
#include "queue.hpp"
#include <string>

namespace bookchain {
namespace http {

void startNodeServer(sharedTSQueue<Peer>& peerQueue, sharedTSQueue<std::string>& dataQueue);

}  // namespace http
}  // namespace bookchain
