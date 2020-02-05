#pragma once

#include <string>
#include <vector>

namespace bookchain {

class Peer {
public:
    explicit Peer(std::string ipAddress);

    bool active();
    void makeInactive();
    void makeActive();

    std::string ipAddress();

private:
    bool _active;
    std::string _ipAddress;
};

class PeersListView {
public:
    std::vector<Peer> activePeers();
};

class PeersList : public PeersListView {
public:
    void addPeer(const Peer& peer);
};

}  // namespace bookchain
