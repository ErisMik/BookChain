#pragma once

#include <string>
#include <vector>

namespace bookchain {

class Peer {
public:
    Peer(std::string ipAddress);

    bool active();
    void makeInactive();
    void makeActive();

    std::string ipAddress();

private:
    bool _active;
    std::string _ipAddress;
};

class PeersList {
    void addPeer(const Peer& peer);
    std::vector<Peer> activePeers();

private:
    std::vector<Peer> _peersList;
};

}  // namespace bookchain
