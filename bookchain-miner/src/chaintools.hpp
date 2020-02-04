#pragma once
#include "block.hpp"
#include "chain.hpp"
#include <vector>

namespace bookchain {

bool verifyChain(Bloockchain bloockchain);
bool verifyPair(Bloock& lowerBloock, Bloock& upperBloock);

}  // namespace bookchain
