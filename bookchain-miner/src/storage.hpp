#include <string>
#include <vector>

namespace bookchain {

constexpr char blockchainFilename[] = "theblock.chain";

void saveChain(std::vector<Bloock> bloockChain, const std::string& filename = blockchainFilename);

std::vector<Bloock> getFullChain(const std::string& filename = blockchainFilename);

Bloock getBlockByHeight(unsigned int blockHeight, const std::string& filename = blockchainFilename);

}  // namespace bookchain
