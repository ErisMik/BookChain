#include "chain.hpp"
#include "storage.hpp"

namespace bookchain {

BlookchainView::BlookchainView(const std::string& filename) :
    _nextIndex(0), _filename(filename) {
}

Bloock BlookchainView::latest() {
    return storage::getBlockLatest(this->_filename);
}

Bloock BlookchainView::bloock(int height) {
    return storage::getBlockByHeight(height, this->_filename);
}

int BlookchainView::height() {
    return storage::getChainHeight(this->_filename);
}

bool BlookchainView::hasNext() {
    return this->_nextIndex <= this->height();
}

Bloock BlookchainView::next() {
    Bloock bloock = storage::getBlockByHeight(this->_nextIndex, this->_filename);
    this->_nextIndex += 1;
    return bloock;
}

void BlookchainView::resetNext() {
    this->_nextIndex = 0;
}

Bloockchain::Bloockchain(const std::string& filename) :
    BlookchainView(filename) {
}

void Bloockchain::append(Bloock bloock) {
    storage::appendChain(bloock, this->_filename);
}

void Bloockchain::purge() {
    storage::purgeChain(this->_filename);
}

}  // namespace bookchain
