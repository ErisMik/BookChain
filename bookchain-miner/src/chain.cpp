#include "chain.hpp"
#include "storage.hpp"

namespace bookchain {

BlookchainView::BlookchainView(std::string chainId) :
    _nextIndex(0), _chainId(std::move(chainId)) {
}

Bloock BlookchainView::latest() {
    return storage::getBlockLatest(this->_chainId);
}

Bloock BlookchainView::bloock(int height) {
    return storage::getBlockByHeight(height, this->_chainId);
}

int BlookchainView::height() {
    return storage::getChainHeight(this->_chainId);
}

bool BlookchainView::hasNext() {
    return this->_nextIndex <= this->height();
}

Bloock BlookchainView::next() {
    Bloock bloock = storage::getBlockByHeight(this->_nextIndex, this->_chainId);
    this->_nextIndex += 1;
    return bloock;
}

void BlookchainView::resetNext() {
    this->_nextIndex = 0;
}

Bloockchain::Bloockchain(const std::string& chainId) :
    BlookchainView(chainId) {
}

void Bloockchain::append(Bloock& bloock) {
    storage::appendChain(bloock, this->_chainId);
}

void Bloockchain::purge() {
    storage::purgeChain(this->_chainId);
}

}  // namespace bookchain
