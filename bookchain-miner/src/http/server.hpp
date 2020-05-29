#pragma once

#include "job.hpp"
#include "peers.hpp"
#include "queue.hpp"
#include <string>

namespace bookchain {
namespace http {

constexpr int defaultServerPort = 8000;

void startNodeServer(int serverPort, const sharedTSQueue<Peer>& peerQueue, const sharedTSQueue<Job>& jobQueue);

}  // namespace http
}  // namespace bookchain
