#pragma once

#include "job.hpp"
#include "peers.hpp"
#include "queue.hpp"

namespace bookchain {

void peerMainLoop(const sharedTSQueue<Peer>& peerQueue, const sharedTSQueue<Job>& jobQueue);

}  // namespace bookchain
