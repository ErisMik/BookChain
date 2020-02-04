#include "chaintools.hpp"
#include "utils.hpp"
#include <iostream>

namespace bookchain {

bool verifyChain(Bloockchain bloockchain) {
    Bloock prevBloock;

    bloockchain.resetNext();
    if (bloockchain.hasNext()) {
        prevBloock = bloockchain.next();
    }

    bool isValid = true;
    while (bloockchain.hasNext()) {
        Bloock bloock = bloockchain.next();

        if (!verifyPair(prevBloock, bloock)) {
            isValid = false;
            break;
        }

        prevBloock = bloock;
    }
    bloockchain.resetNext();

    return isValid;
}

bool verifyPair(Bloock& lowerBloock, Bloock& upperBloock) {
    bool isValid = true;

    // TODO(Eric Mikulin): Check difficulty

    // Check that heights are valid
    if (upperBloock.blockHeight() - lowerBloock.blockHeight() != 1) {
        isValid = false;
    }

    // Check that hashes are valid
    if (upperBloock.prevHash() != lowerBloock.blockHash()) {
        isValid = false;
    }

    return isValid;
}

}  // namespace bookchain
