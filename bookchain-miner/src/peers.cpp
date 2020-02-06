#include "peers.hpp"

#include <mutex>

namespace bookchain {

namespace {
// TODO(Eric Mikulin): This needs to not be a global static variable
std::vector<Peer> nodePeersList;
}  // namespace

std::mutex peersListMutex;

Peer::Peer(std::string ipAddress) :
    _active(false), _ipAddress(std::move(ipAddress)) {
}

bool Peer::active() {
    return this->_active;
}

void Peer::makeInactive() {
    this->_active = false;
}

void Peer::makeActive() {
    this->_active = true;
}

std::string Peer::ipAddress() {
    return this->_ipAddress;
}

// TODO(Eric Mikulin): THIS NEEDS TO BE MADE THREADSAFE

std::vector<Peer> PeersListView::activePeers() {
    std::lock_guard<std::mutex> guard(peersListMutex);
    std::vector<Peer> activePeers;
    for (auto& peer : nodePeersList) {
        if (peer.active()) {
            activePeers.push_back(peer);
        }
    }
    return activePeers;
}

void PeersList::addPeer(const Peer& peer) {
    std::lock_guard<std::mutex> guard(peersListMutex);
    nodePeersList.push_back(peer);
}

}  // namespace bookchain
