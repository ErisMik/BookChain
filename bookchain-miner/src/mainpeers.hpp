#pragma once

#include "peers.hpp"
#include "queue.hpp"

namespace bookchain {

void peerMainLoop(const bookchain::sharedTSQueue<bookchain::Peer>& peerQueue);

}  // namespace bookchain
