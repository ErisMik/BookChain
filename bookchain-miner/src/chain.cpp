#include "chain.hpp"
#include "utils.hpp"
#include <iostream>

namespace bookchain {

bool verifyChain(std::vector<Bloock>& bloockChain) {
    Bloock prevBloock;

    bool isValid = true;

    for (auto& bloock : bloockChain) {
        if (prevBloock.nonce() != 0) {  // TODO: Eric Mikulin, 2020-01-14, Find a better way to skip the first block
            // std::cout << utils::hexifystring(bloock.blockHash()) << " ";
            // std::cout << utils::hexifystring(bloock.prevHash()) << " ";
            // std::cout << utils::hexifystring(prevBloock.blockHash()) << std::endl;

            if (!verifyPair(prevBloock, bloock)) {
                isValid = false;
                break;
            }
        }
        prevBloock = bloock;
    }

    return isValid;
}

bool verifyPair(Bloock lowerBloock, Bloock upperBloock) {
    bool isValid = true;

    // TODO: Check difficulty

    if (upperBloock.prevHash() != lowerBloock.blockHash()) {
        isValid = false;
    }

    return isValid;
}

}  // namespace bookchain
