#include "mainpeers.hpp"

#include <thread>
#include <iostream>

namespace bookchain {

void discoverInitialPeers(PeersList& peersList) {
	constexpr char peerHints[] = "192.168.1.1";

	// TODO(Eric Mikulin)
	// Starting with peer hints search until another node is found.
	// Once found, download peers peerslist and add to our peerslist.
	// Then link to peer.
}

void syncBlocksWithPeers(PeersList& peersList) {
}

void syncPeersWithPeers(PeersList& peersList) {
}

void handleNewPeers(PeersList& peersList, const sharedTSQueue<Peer>& peerQueue) {
        while (!peerQueue->empty()) {
            Peer peer = peerQueue->pop();
            peer.makeActive();
            std::cout << "GOT PEER WITH IP " << peer.ipAddress() << std::endl;
            peersList.addPeer(peer);
        }
}

void peerMainLoop(const sharedTSQueue<Peer>& peerQueue) {
    std::cout << "Launching peer thread" << std::endl;

    PeersList peersList;
    discoverInitialPeers(peersList);

    while (true) {
	discoverInitialPeers(peersList);
	syncBlocksWithPeers(peersList);
	syncPeersWithPeers(peersList);
	handleNewPeers(peersList, peerQueue);

        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }

    std::cout << "Peer thread stopped" << std::endl;
}

}  // namespace bookchain
