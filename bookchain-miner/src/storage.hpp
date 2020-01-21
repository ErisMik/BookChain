#include <string>
#include <vector>

namespace bookchain {

constexpr char blockchainFilename[] = "theblock.chain";

void saveChain(std::vector<Bloock> bloockChain, std::string filename = blockchainFilename);

std::vector<Bloock> getFullChain(std::string filename = blockchainFilename);

Bloock getBlockByHeight(unsigned int blockHeight, std::string filename = blockchainFilename);

}  // namespace bookchain
