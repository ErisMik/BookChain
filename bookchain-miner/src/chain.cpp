#include "chain.hpp"
#include "utils.hpp"
#include <iostream>

namespace bookchain {

bool verifyChain(std::vector<Bloock>& bloockChain) {
    Bloock prevBloock;

    for (auto& bloock : bloockChain) {
        if (prevBloock.nonce() != 0) {
            std::cout << utils::hexifystring(bloock.blockHash()) << " ";
            std::cout << utils::hexifystring(bloock.prevHash()) << " ";
            std::cout << utils::hexifystring(prevBloock.blockHash()) << std::endl;
        }
        prevBloock = bloock;
    }

    return true;
}

} // namespace bookchain
