#pragma once

#include "peers.hpp"
#include "queue.hpp"
#include <string>

namespace bookchain {
namespace http {

void startNodeServer(const sharedTSQueue<Peer>& peerQueue, const sharedTSQueue<std::string>& dataQueue);

}  // namespace http
}  // namespace bookchain
