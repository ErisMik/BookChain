#include "peers.hpp"

namespace bookchain {

Peer::Peer(const std::string& ipAddress) :
    _active(false), _ipAddress(ipAddress) {
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

void PeersList::addPeer(const Peer& peer) {
    this->_peersList.push_back(peer);
}

std::vector<Peer> PeersList::activePeers() {
    std::vector<Peer> activePeers;
    for (auto& peer : this->_peersList) {
        if (peer.active()) {
            activePeers.push_back(peer);
        }
    }
    return activePeers;
}

}  // namespace bookchain