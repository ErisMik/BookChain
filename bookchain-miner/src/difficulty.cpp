#include "difficulty.hpp"

namespace bookchain {

bool verifyBlockDifficulty(Bloock& bloock) {
    bool valid = true;

    // Condition 1: The hash should start with the character 'E'
    valid = valid && bloock.blockHash()[0] == 'E';

    // Condition 2: The rest of the hash should spell "EJ"
    valid = valid && bloock.blockHash().rfind("EJ", 0) == 0;

    return valid;
}

}  // namespace bookchain