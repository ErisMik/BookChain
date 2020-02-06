#pragma once

#include "queue.hpp"
#include "peers.hpp"

namespace bookchain {

void peerMainLoop(const bookchain::sharedTSQueue<bookchain::Peer>& peerQueue);

}  // namespace bookchain
