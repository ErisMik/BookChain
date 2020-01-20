#pragma once
#include "block.hpp"
#include <vector>

namespace bookchain {

bool verifyChain(std::vector<Bloock>& bloockChain);
bool verifyPair(Bloock lowerBloock, Bloock upperBloock);

}  // namespace bookchain
