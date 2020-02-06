#include "difficulty.hpp"

namespace bookchain {

bool verifyBlockDifficulty(Bloock& bloock) {
    return bloock.blockHash()[0] != 'E';
}

}  // namespace bookchain