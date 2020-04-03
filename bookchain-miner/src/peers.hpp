#pragma once

#include <string>
#include <vector>

namespace bookchain {

class Peer {
public:
    Peer();
    explicit Peer(std::string hostname, std::string version, uint64_t identifier);

    bool active();
    void makeInactive();
    void makeActive();

    std::string hostname() const;
    std::string version() const;
    uint64_t identifier() const;

private:
    bool _active;
    std::string _hostname;
    std::string _version;
    uint64_t _identifier;
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
