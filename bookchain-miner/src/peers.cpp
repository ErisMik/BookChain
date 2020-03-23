#include "peers.hpp"

#include <mutex>

namespace bookchain {

namespace {
// TODO(Eric Mikulin): This needs to not be a global static variable
std::vector<Peer> nodePeersList;
}  // namespace

std::mutex peersListMutex;

Peer::Peer() :
    _active(false), _hostname(""), _version(""), _identifier(0) {
}

Peer::Peer(std::string hostname, std::string version, uint64_t identifier) :
    _active(true), _hostname(std::move(hostname)), _version(std::move(version)), _identifier(identifier) {
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

std::string Peer::hostname() const {
    return this->_hostname;
}

std::string Peer::version() const {
    return this->_version;
}

uint64_t Peer::identifier() const {
    return this->_identifier;
}

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

// TODO(Eric Mikulin): Handle adding duplicate peers
void PeersList::addPeer(const Peer& peer) {
    std::lock_guard<std::mutex> guard(peersListMutex);
    bool unique = true;

    for (auto& otherPeer : nodePeersList) {
        if (peer.identifier() == otherPeer.identifier()) {
            unique = false;
            break;
        }
    }

    if (unique) {
        nodePeersList.push_back(peer);
    }
}

}  // namespace bookchain
