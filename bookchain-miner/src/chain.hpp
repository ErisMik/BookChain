#pragma once

#include "block.hpp"

namespace bookchain {

constexpr char bloockchainFilename[] = "theblock.chain";

class Bloockchain {
public:
    Bloockchain(const std::string& filename = bloockchainFilename);
    void append(Bloock bloock);
    Bloock latest();
    Bloock bloock(int height);
    int height();

    bool hasNext();
    Bloock next();
    void resetNext();  // TODO(Eric Mikulin): Find a way to do this RAII style kinda like mutexes

    void purge();

private:
    int _nextIndex;
    std::string _filename;
};

}  // namespace bookchain
