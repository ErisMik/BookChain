#include "chain.hpp"
#include "utils.hpp"
#include <iostream>

namespace bookchain {

bool verifyChain(std::vector<Bloock>& bloockChain) {
    Bloock prevBloock;

    bool isValid = true;

    for (auto& bloock : bloockChain) {
        if (prevBloock.nonce() != 0) {  // TODO: Eric Mikulin, 2020-01-14, Find a better way to skip the first block
            std::cout << utils::hexifystring(bloock.blockHash()) << " ";
            std::cout << utils::hexifystring(bloock.prevHash()) << " ";
            std::cout << utils::hexifystring(prevBloock.blockHash()) << std::endl;

            if (bloock.prevHash() != prevBloock.blockHash()) {
                isValid = false;
                break;
            }
        }
        prevBloock = bloock;
    }

    return isValid;
}

} // namespace bookchain
