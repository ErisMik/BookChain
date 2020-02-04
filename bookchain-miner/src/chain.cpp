#include "chain.hpp"
#include "storage.hpp"

namespace bookchain {

Bloockchain::Bloockchain(const std::string& filename) :
    _nextIndex(0), _filename(filename) {
}

void Bloockchain::append(Bloock bloock) {
    storage::appendChain(bloock, this->_filename);
}

Bloock Bloockchain::latest() {
    return storage::getBlockLatest(this->_filename);
}

Bloock Bloockchain::bloock(int height) {
    return storage::getBlockByHeight(height, this->_filename);
}

int Bloockchain::height() {
    return storage::getChainHeight(this->_filename);
}

bool Bloockchain::hasNext() {
    return this->_nextIndex <= this->height();
}

Bloock Bloockchain::next() {
    Bloock bloock = storage::getBlockByHeight(this->_nextIndex, this->_filename);
    this->_nextIndex += 1;
    return bloock;
}

void Bloockchain::resetNext() {
    this->_nextIndex = 0;
}

void Bloockchain::purge() {
    storage::purgeChain(this->_filename);
}

}  // namespace bookchain