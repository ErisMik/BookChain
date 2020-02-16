#include "difficulty.hpp"

namespace bookchain {

bool verifyBlockDifficulty(Bloock& bloock) {
    bool valid = true;

    // Condition 1: The hash should start with the character 'E'
    valid = valid && bloock.blockHash()[0] == 'E';

    return valid;
}

}  // namespace bookchain