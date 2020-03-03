#pragma once

#include "job.hpp"
#include "peers.hpp"
#include "queue.hpp"
#include <string>

namespace bookchain {
namespace http {

void startNodeServer(const sharedTSQueue<Peer>& peerQueue, const sharedTSQueue<Job>& jobQueue);

}  // namespace http
}  // namespace bookchain
