#pragma once

#include "block.hpp"

namespace bookchain {

constexpr char bloockchainFilename[] = "theblock.chain";

class BlookchainView {
public:
    BlookchainView(std::string chainId = bloockchainFilename);
    Bloock latest();
    Bloock bloock(int height);
    int height();

    bool hasNext();
    Bloock next();
    void resetNext();  // TODO(Eric Mikulin): Find a way to do this RAII style kinda like mutexes

protected:
    int _nextIndex;
    std::string _chainId;
};

class Bloockchain : public BlookchainView {
public:
    Bloockchain(const std::string& chainId = bloockchainFilename);
    void append(Bloock& bloock);

    void purge();
};

}  // namespace bookchain
